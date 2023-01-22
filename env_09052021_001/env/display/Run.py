import time
import tkinter as tk

from tkinter import ttk
from tkinter import *
from MouseListener import MouseListener
from RunInt import RunInt
from RunEnd import RunEnd
from ImagePath import ImagePath
from PIL import Image, ImageTk, ImageSequence


class PrintImage:
    def __init__(self, container, image_path):

        render = ImageTk.PhotoImage(Image.open(image_path))
        img = Label(container, image=render)
        img.image = render
        img.place(x=0, y=0)


class LableValues:
    def __init__(self, container, input_, x, y):
        self.txt = Label(container, height=1, width=5, font=(
            "Arial", 30), background="white", text=input_)
        self.txt.place(x=x, y=y)

    def set_value(self, value):
        self.txt['text'] = value

    def get_value(self):
        return self.txt['text']


class Run(tk.Toplevel):
    def __init__(self, parent, fields, border_connection):
        super().__init__(parent)

        # self.geometry('1024x600+0+0')
        self.attributes('-fullscreen', True)
        self.mouse = MouseListener(self, "Run menu")
         
        self.mouse.register_callback(self.handle_mouse_click)

        self.fields = fields
        self.type_of = fields[4]
        
        self.border_connection = border_connection
        self.border_connection.register_callback(self.set_current_data_program, "__RUN__")
        self.border_connection.register_callback(self.run_end, "__FINISH_RUN__")

        self.temp = None
        self.time = None
        self.second_screen_value = True
        self.run_end_already_open = False
        self.image_path = ImagePath()

        if self.type_of == "CRIO":
            PrintImage(self, self.image_path.get("CrioExe.png"))
            self.temp = LableValues(self, "--", 680, 170)
            self.time = LableValues(self, "--", 680, 340)
            
            # configuration data, state and status
            self.border_connection.add(fields, 0, 0, 0)

        elif self.type_of == "TERMO":
            PrintImage(self, self.image_path.get("TermoExeLeve.png"))
            self.temp = LableValues(self, "--", 652, 350)
            self.time = LableValues(self, "--", 652, 460)
            
            # configuration data, state and status
            self.border_connection.add(fields, 0, 0, 1)

        self.protocol("WM_DELETE_WINDOW", self.close)
        self.add_extern_event = None
        self.localfocus = True
               

    def close(self):
        # configuration data, state and status
        self.border_connection.add((0, 0, 0, 0, 2), 1, 0, 0)
        self.border_connection.unregister_callback("__RUN__")
        self.border_connection.unregister_callback("__FINISH_RUN__")

        self.add_extern_event(False)
        # self.mouse.stop()
        self.destroy()

    def set_localfocus(self, value):
        self.localfocus = value

    def get_localfocus(self):
        return self.localfocus

    def get_second_screen(self):
        return self.second_screen_value

    def second_screen(self, value):
        self.second_screen_value = value

    def add_callback(self, callback, event):
        if event == "__EVENT_CLOSE__":
            self.add_extern_event = callback

    def load_values(self, temp, time):
        if not temp == self.temp.get_value():
            self.temp.set_value(temp)
        self.time.set_value(time)

    def set_current_data_program(self, temperature, time, pwm):
        self.temp.set_value(temperature)
        self.time.set_value(time)

    def handle_mouse_click(self, x, y):
        print("DEBUG: Mouse click position: ", x, y)
        if self.get_localfocus():
            if self.type_of == "CRIO" or self.type_of == "TERMO":
                if x >= 830 and x <= 980 and y >=  480 and y <=  600:
                    #self.set_localfocus(False)
                    self.run_int()                    
            if self.type_of == "TERMO":
                if x >= 574 and x <= 890 and y >=  147 and y <=  216:
                    PrintImage(self, self.image_path.get("TermoExeLeve.png"))
                    self.temp = LableValues(self, str(self.temp.get_value()), 652, 350)
                    self.time = LableValues(self, str(self.time.get_value()), 652, 460)
                    self.border_connection.add(self.fields, 0, 0, 1)                    
                elif x >= 574 and x <= 890 and y >=  33 and y <=  257:
                    PrintImage(self, self.image_path.get("TermoExeModerado.png"))
                    self.temp = LableValues(self, str(self.temp.get_value()), 652, 350)
                    self.time = LableValues(self, str(self.time.get_value()), 652, 460)
                    self.border_connection.add(self.fields, 0, 0, 2)                    
                elif x >= 574 and x <= 890 and y >=  298 and y <=  335:
                    PrintImage(self, self.image_path.get("TermoExeIntenso.png"))
                    self.temp = LableValues(self, str(self.temp.get_value()), 652, 350)
                    self.time = LableValues(self, str(self.time.get_value()), 652, 460)
                    self.border_connection.add(self.fields, 0, 0, 3)
        else:
            if self.get_second_screen() == False:
                self.set_localfocus(True)

    def run_end(self):
        if self.run_end_already_open == False:
            self.border_connection.add((0, 0, 0, 0, 2), 1, 0, 0)
            runEnd = RunEnd(self, self.type_of)
            runEnd.add_callback(self.close, "__EVENT_CLOSE__")
            #self.set_localfocus(False)
            self.run_end_already_open = True

    def run_int(self):
        runInt = RunInt(self, self.type_of)
        runInt.add_callback(self.close, "__EVENT_CLOSE__")
        runInt.add_callback(self.second_screen, "__EVENT_CANCEL__")

        #self.set_localfocus(False)
        self.second_screen(True)
