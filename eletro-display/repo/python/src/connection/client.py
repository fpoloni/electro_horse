import socket
import time
import threading
import queue
from enum import Enum, IntEnum, unique

@unique
class IdxParameterPDU(IntEnum):
    HEAD = 0
    OPERATION = 1
    LEN = 2
    PROGRAM = 3
    STATE  = 4
    DEVICE = 5
    PAYLOAD = 6
    CRC = 7
    TAIL = 8

@unique
class IdxParameterPayload(IntEnum):
    PWM = 6
    TEMP_MIN = 7
    TEMP_MAX = 8
    TEMP_CUR = 9
    TIME     = 10
    STATUS   = 11

class Client:
    def __init__(self, socket, address, port):
        self.thread_tx = threading.Thread(
            name='thread to send package', daemon=True, target=self.tx)
        self.thread_rx = threading.Thread(
            name='thread to receive package', daemon=True, target=self.rx)

        self.address = address
        self.port = port
        self.socket = socket
        self.expected_message = "board_connected"

        self.rx_queue  = queue.Queue(100)
        self.tx_queue  = queue.Queue(100)

        self.keep_loop = True
        self.isconnected = False
        self.is_callback_register = False
        self.callback_to_program_run = None
        self.callback_to_stop_preparation = None
        self.callback_to_program_preparation = None
        self.callback_to_stop_program = None
        self.callback_to_start_run = None

        self.isrunning = False
        print("Client initialized")

    def reset(self):
        self.isrunning = False


    def tx(self):
        print("TX thread started")
        while self.keep_loop:
            time.sleep(1)
            if not self.tx_queue.empty():
                message = self.tx_queue.get()
                print(message)
                self.socket.send(bytes(message))
                # self.socket.send(bytes.fromhex(message))
            # else:
            #     self.tx_update.wait()

    def rx(self):
        print("RX thread started")
        while self.keep_loop:
            data = bytes(self.socket.recv(1024))
            time.sleep(1)
            if data:
                print('received data:', data.hex())
                if data[IdxParameterPDU.STATE] == 0: #start state
                    if data[IdxParameterPayload.STATUS] == 0 and self.isrunning == False:
                        self.isrunning = True
                        if self.callback_to_start_run != None:
                            self.callback_to_start_run()

                        if self.callback_to_program_run != None and self.isrunning == True:
                            print("Calling application for temperature control")
                            self.callback_to_program_run(
                                data[IdxParameterPayload.TEMP_CUR], data[IdxParameterPayload.TIME], data[IdxParameterPayload.PWM])
                    else:
                        if self.callback_to_program_preparation != None:
                            self.callback_to_program_preparation(
                                data[IdxParameterPayload.TEMP_CUR])

                if data[IdxParameterPDU.STATE] == 1: #stop state
                    print("Received stop commnad")
                    self.callback_to_stop_program()

    def set_package_tx(self, data):
        self.tx_queue.put(data)
        # self.tx_update.set()

    def get_package(self):
        data_out = None
        if not self.rx_queue.empty():
            data_out = self.rx_queue.get()
        return data_out, self.rx_queue.qsize()

    def start(self):
        self.socket.connect((self.address, self.port))
        self.thread_rx.start()
        self.thread_tx.start()
        self.isconnected = True

    def stop(self):
        if self.isconnected:
            self.socket.send("close".encode())
            self.socket.close()

        self.keep_loop = False

    def callback_register(self, callback, kindof):
        print("Registering callback method")
        self.is_callback_register = True

        if kindof == "RUN" and self.callback_to_program_run == None:
            self.callback_to_program_run = callback
        elif kindof == "PREPARE" and self.callback_to_program_preparation == None:
            self.callback_to_program_preparation = callback
        elif kindof == "STOP_PREPARATION" and self.callback_to_stop_preparation == None:
            self.callback_to_stop_preparation = callback
        elif kindof == "STOP_RUN" and self.callback_to_stop_program == None:
            self.callback_to_stop_program = callback
        elif kindof == "START_RUN" and self.callback_to_start_run == None:
            self.callback_to_start_run = callback
        else:
            print("Failed during callback registration", kindof)
            self.is_callback_register = False
