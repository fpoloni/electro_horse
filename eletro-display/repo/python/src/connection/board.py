import socket
import time
import threading
import queue
import random

from enum import Enum, IntEnum, unique


@unique
class IdxParameterPDU(IntEnum):
    HEAD = 0
    OPERATION = 1
    LEN = 2
    PROGRAM = 3
    STATE = 4
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
    TIME = 10
    STATUS = 11


class BoardSim:
    def __init__(self):
        # take the server name and port name
        self.host = '127.0.0.1'
        self.port = 8080
        self.keep_loop = True

        # create a socket at server side
        # using TCP / IP protocol
        self.s = socket.socket(socket.AF_INET,
                               socket.SOCK_STREAM)

        # bind the socket with server and port number
        self.s.bind((self.host, self.port))
        # allow maximum 1 connection to
        self.s.listen(1)

        # wait till a client accept connection
        self.c, self.addr = self.s.accept()
        # fake package to test
        self.tx_package = [0x7e, 0x00, 0x00, 0x00, 0x00, 0x04,
                           0x50, 0x20, 0x30, 0x20, 0x00, 0x01, 0x00, 0x7e]

        self.tx_queue = queue.Queue()
        self.pause_thread = threading.Event()
        self.set_program = False
        self.thread_is_started = False
        self.thread_is_stopped = True
        self.counter = 0
        self.counter_program_finish = 0
        self.selected_program = ""
        self.received_data = None
        
        self.timeout = 0
        self.temp_max = 0
        self.temp_min = 0
        self.time = 0

    def handlepackage(self, package):
        self.received_data = bytes(package.encode())
        print("Received Package: program, time, tmin, tmax, pwm",
              self.received_data[IdxParameterPDU.PROGRAM],
              self.received_data[IdxParameterPayload.TIME],
              self.received_data[IdxParameterPayload.TEMP_MIN],
              self.received_data[IdxParameterPayload.TEMP_MAX],
              self.received_data[IdxParameterPayload.PWM])

        if self.received_data[IdxParameterPDU.PROGRAM] == 0x00 or self.received_data[IdxParameterPDU.PROGRAM] == 0x01:
            #just to print
            if self.received_data[IdxParameterPDU.PROGRAM] == 0x00:
                print("Program selected: CRIO")
                self.selected_program = "CRIO"

            elif self.received_data[IdxParameterPDU.PROGRAM] == 0x01:
                print("Program selected: TERMO")
                self.selected_program = "TERMO"

            if self.received_data[IdxParameterPayload.STATUS] == 0x00:  # run
                self.run_status(self.received_data[IdxParameterPDU.STATE])

            if self.received_data[IdxParameterPayload.STATUS] == 0x01:  # preparation
                self.timeout = 0
                self.time = self.received_data[IdxParameterPayload.TIME]
                self.temp_max = self.received_data[IdxParameterPayload.TEMP_MAX]
                self.temp_min = self.received_data[IdxParameterPayload.TEMP_MIN]
                
                self.preparation_status(
                    self.received_data[IdxParameterPDU.STATE])
        else:
            print("Unknown program ID")
            self.thread_is_stopped = True

    def preparation_status(self, data):
        print("Preparation Status")

        if data == 0x00:  # start
            print("Start process")
            self.tx_package[IdxParameterPayload.STATUS] = 1
            self.thread_is_stopped = False
            if not self.thread_tx.is_alive():
                self.thread_tx.start()
            self.thread_is_started = True

        elif data == 0x01:  # stop
            print("Stop process")
            self.thread_is_stopped = True
            self.tx_package[IdxParameterPayload.STATUS] = 2
            self.counter = 0
            
        elif data == 0x02:  # cancel
            print("Cancel process")
            self.thread_is_stopped = True
            self.tx_package[IdxParameterPayload.STATUS] = 2
            self.counter = 0
        else:
            print("Invalid state process")

    def run_status(self, data):
        print("Run Status: data: ", data)

        if data == 0x00:  # start
            print("Start process")
            self.tx_package[IdxParameterPayload.STATUS] = 0
            self.thread_is_stopped = False
            if not self.thread_tx.is_alive():
                self.thread_tx.start()
            self.thread_is_started = True

        elif data == 0x01:  # stop
            print("Stop process")
            self.thread_is_stopped = True
            self.tx_package[IdxParameterPayload.STATUS] = 2
            self.counter = 0
        else:
            print("Invalid state process")

    def tx(self):
        print("TX thread to send fake packages")
        flag_paused_thread = False

        while self.keep_loop:
            time.sleep(1)
            if self.thread_is_stopped:
                if flag_paused_thread == False:
                    print("The thread was paused")
                    flag_paused_thread = True

            elif self.thread_is_started:
                flag_paused_thread = False
                self.tx_package[IdxParameterPayload.TEMP_CUR] = random.randint(
                    0, 60)
                # when the status is set to RUN
                if self.tx_package[IdxParameterPayload.STATUS] == 0:
                    self.tx_package[IdxParameterPDU.STATE] = 0 # put state to START
                    
                    if self.time == 0:
                        self.thread_is_stopped = True
                    else:
                        self.time = self.time - 1
                # when the status is set to PREPARATION
                elif self.tx_package[IdxParameterPayload.STATUS] == 1:
                    if self.timeout < 20:
                        self.timeout = self.timeout + 1
                    else:
                        self.tx_package[IdxParameterPDU.STATE] = 2

                self.tx_package[IdxParameterPayload.TIME] = self.time
                self.c.send(bytes(self.tx_package))

    def get_status_connection(self):
        # display client address
        print("CONNECTION FROM:", str(self.addr))
        self.c.send("board_connected".encode())

    def start(self):
        self.thread_tx = threading.Thread(
            name='thread to send package', daemon=True, target=self.tx)

        print("Wait for application commands")
        #loop to listen all packages sent from clients
        while self.keep_loop:
            time.sleep(1)
            #listening packages received from GUI
            message = self.c.recv(1024).decode()
            print("received message from client: ", message)
            if message.lower().strip() != 'close':
                if message:
                    self.handlepackage(message)
            else:
                print("Received cmd to close connection")
                self.keep_loop = False


if __name__ == "__main__":
    startboard = BoardSim()
    startboard.start()
