import socket
import threading
import queue
import time
from PackageId import*


class BorderConnection:
    def __init__(self):

        # init socket connection
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        #self.socket.connect(('10.42.0.69', 8080))
        self.socket.connect(('127.0.0.1', 8080))
        # flag to put the thread's loop condition
        self.loop_active = True

        # init queue
        self.rx_queue = queue.Queue(100)
        self.tx_queue = queue.Queue(100)

        # create threads
        self.thread_tx = threading.Thread(
            name='thread to send package', daemon=True, target=self.tx)
        self.thread_rx = threading.Thread(
            name='thread to receive package', daemon=True, target=self.rx)

        # # init threads
        self.thread_rx.start()
        self.thread_tx.start()

        self.data_to_preparation = None
        self.data_to_run = None
        self.finish_to_run = None
        self.finish_to_preparation = None
        self.isrunning = False

    # " Build data package where:
    #     -message is the configuration content(time, temp(max and min), pwm level, program)
    #     -status program(preparation, run or none)
    #     -state(start, stop, cancel and note)
    # "
    def add(self, message, state, status, pwm):
        package = self.build_package(message, 0, state, 3, status, pwm)
        print("Message to board: ", package)
        self.tx_queue.put(package)

    def get(self):
        data_out = None
        if not self.rx_queue.empty():
            data_out = self.rx_queue.get()
        return data_out, self.rx_queue.qsize()

    def tx(self):
        print("TX thread started")
        while self.loop_active:
            time.sleep(0.2)
            if not self.tx_queue.empty():
                message = self.tx_queue.get()
                print("TX-Debug BorderConnection: ", message)
                self.socket.send(bytes(message))

    def rx(self):
        print("RX thread started")
        while self.loop_active:
            data = bytes(self.socket.recv(1024))
            time.sleep(0.2)
            if data:
                print("RX-Debug BorderConnection: ", data.hex())
                self.handle_received_package(data)

    def stop(self):
        print("STOPPED...!!!!")
        self.loop_active = False

    def handle_received_package(self, data):
        if data[IdxParameterPayload.STATUS] == 0:
            print("RUN MODE")
            if data[IdxParameterPDU.STATE] == 0:  # start state
                print("START")
                if not self.data_to_run == None:
                    print("Receiving temperature value to Run Mode.")
                    self.data_to_run(
                        data[IdxParameterPayload.TEMP_CUR],
                        data[IdxParameterPayload.TIME],
                        data[IdxParameterPayload.PWM])

                    if data[IdxParameterPayload.TIME] == 0:
                        print("Finish process to run...")
                        self.finish_to_run()
                else:
                    print("Data To Run is None.")
            elif data[IdxParameterPDU.STATE] == 1:  # stop state
                print("Received stop command")
            else:
                print("Invalid state")
        elif data[IdxParameterPayload.STATUS] == 1:
            print("PREPARATION MODE")
            if data[IdxParameterPDU.STATE] == 0:  # start state
                print("Received start commnad")
                if self.data_to_preparation != None:
                    print("Receiving temperature value to Preparation Mode.")
                    self.data_to_preparation(
                        data[IdxParameterPayload.TEMP_CUR])
            elif data[IdxParameterPDU.STATE] == 1:  # stop state
                print("Received stop command")
            elif data[IdxParameterPDU.STATE] == 2:  # cancel state
                print("Received cancel command")
                if not self.finish_to_preparation == None:
                    self.finish_to_preparation()
                else:
                    print("Received unknown command")

    def register_callback(self, callback, type_of):
        print("Debug: Register callback", type_of)
        if type_of == "__PREPARATION__":
            self.data_to_preparation = callback
        elif type_of == "__RUN__":
            print("Register RUN")
            self.data_to_run = callback
        elif type_of == "__FINISH_RUN__":
            self.finish_to_run = callback
        elif type_of == "__FINISH_PREPARATION__":
            self.finish_to_preparation = callback

    def unregister_callback(self, type_of):
        if type_of == "__PREPARATION__":
            self.data_to_preparation = None
        elif type_of == "__RUN__":
            self.data_to_run = None
        elif type_of == "__FINISH_RUN__":
            self.finish_to_run = None
        elif type_of == "__FINISH_PREPARATION__":
            self.finish_to_preparation = None

    def build_package(self, package, operation, state, device, program_status, pwm_level):
        tx_package = []
        print("package data len: ", len(package))
        program_id = self.parse_program_to_int(package[4])

        print("Data package: temperature min", package[0])
        print("Data package: temperature max", package[1])
        print("Data package: time", package[2])
        print("Data package: program", package[3])

        tx_package.append(0x7e)  # HEAD . to indicates the begin of package
        tx_package.append(operation)
        tx_package.append(0x00)  # LEN -  defined but is not being used
        tx_package.append(program_id)
        tx_package.append(state)  # start, stop , cancel or none
        tx_package.append(device)  # always 3
        tx_package.append(pwm_level)  # level of massage motors
        tx_package.append(package[1])  # temperature min
        tx_package.append(package[0])  # temperature max
        tx_package.append(0)  # temperature current
        tx_package.append(package[2])
        tx_package.append(program_status)  # run, preparation or none
        tx_package.append(0x00)  # CRC - definied but is not being used
        tx_package.append(0x7e)  # TAIL - to indicates the end of package

        return tx_package

    def parse_program_to_int(self, program_name):
        program_id = 0
        if program_name == "CRIO":
            program_id = 0
        elif program_name == "TERMO":
            program_id = 1
        else:
            program_id = 2
        return program_id
