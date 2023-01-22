import tkinter as tk
from tkinter import *

from Configuration import Configuration
from Preparation import Preparation
from MouseListener import MouseListener
from ImagePath import ImagePath
from PIL import Image, ImageTk


class PrintImage:
    def __init__(self, container, image_path):

        render = ImageTk.PhotoImage(Image.open(image_path))
        img = Label(container, image=render)

        img.image = render
        img.place(x=0, y=0)


class Settings(tk.Toplevel):
    def __init__(self, parent, type_of, border_connection, data_base):
        super().__init__(parent)

        # self.geometry('1024x600+0+0')
        self.attributes('-fullscreen', True)
        self.title('EletroHorse-Settings')

        self.mouse = MouseListener(self, 'Settings Menu')
        # 
        self.mouse.register_callback(self.handle_mouse_click)

        self.type_of = type_of
        self.localfocus = True
        self.border_connection = border_connection
        self.event_close = None
        self.event_run_process = None
        self.event_background_previous_one = None

        self.configuration = None
        self.preparation = None
        self.second_screen_value = True
        self.container = self

        self.fields_to_start = None
        self.image_path = ImagePath()
        
        self.data_base = data_base

        # Windows path
        if self.type_of == "CRIO":
            PrintImage(self, self.image_path.get("CrioMenu.png"))
        elif self.type_of == "TERMO":
            PrintImage(self, self.image_path.get("TermoMenu.png"))
        else:
            print("INVALID PROGRAM TYPE")

        self.protocol("WM_DELETE_WINDOW", self.close)

    def close(self):
        if not self.event_close == None:
            self.event_close(False)
        else:
            print("close callback is not registered")
        
        # self.mouse.stop()
        self.destroy()

    def close_previous_start(self):
        if not self.event_run_process == None:
            self.event_run_process(self.fields_to_start)

        # self.mouse.stop()
        self.destroy()

    def get_localfocus(self):
        return self.localfocus

    def get_second_screen(self):
        return self.second_screen_value

    def second_screen(self, value):
        self.second_screen_value = value

    def set_localfocus(self, value):
        self.localfocus = value

    def configuration_out(self):
        self.second_screen_value = False
        self.set_localfocus(True)


    def add_callback(self, callback, event_type):
        if event_type == "__EVENT_CLOSE__":
            self.event_close = callback
        elif event_type == "__EVENT_START__":
            self.event_run_process = callback
        elif event_type == "__EVENT_BG__":
            self.event_background_previous_one = callback

    def handle_mouse_click(self, x, y):
        if self.get_localfocus():
            print("Mouse click position: ", x, y)
            if x >= 0 and x <= 512 and y >=  200 and y <=  700:
                #self.set_localfocus(False)
                self.start_preparation()
            elif x >= 904 and x <= 986 and y >=  13 and y <=  90:
                #self.set_localfocus(False)
                self.close()
            elif x >= 524 and x <= 990 and y >=  180 and y <=  560:
                #self.set_localfocus(False)
                self.start_configuration()

            else:
                print("out of range")
        else:
            if self.get_second_screen() == False:
                self.set_localfocus(True)

    def start_configuration(self):
        self.configuration = Configuration(self, self.type_of, self.data_base)
        self.configuration.add_callback(self.configuration_out)
        self.event_background_previous_one()

        #self.set_localfocus(False)
        self.second_screen(True)

    def start_preparation(self):
        self.fields_to_start = self.data_base.file_read(self.type_of)
        self.preparation = Preparation(
            self, self.type_of, self.fields_to_start, self.border_connection)
        # call this event only after to run screen transition
        self.preparation.add_callback(self.close, "__EVENT_CLOSE__")
        # call this event only after to run screen transition
        self.preparation.add_callback(
            self.close_previous_start, "__EVENT_START__")
        self.event_background_previous_one()
        self.container.iconify()

        #self.set_localfocus(False)
        self.second_screen(True)

    def get_values(self):
        if not self.configuration == None:
            return self.configuration.get_time()
