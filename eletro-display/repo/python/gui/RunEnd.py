import time
import tkinter as tk

from tkinter import ttk
from tkinter import *
from MouseListener import MouseListener
from ImagePath import ImagePath
from PIL import Image, ImageTk, ImageSequence


class PrintImage:
    def __init__(self, container, image_path):

        render = ImageTk.PhotoImage(Image.open(image_path))
        img = Label(container, image=render)
        img.image = render
        img.place(x=0, y=0)


class RunEnd(tk.Toplevel):
    def __init__(self, parent, type_of):
        super().__init__(parent)

        # self.geometry('1024x600+0+0')
        self.attributes('-fullscreen', True)
        self.mouse = MouseListener(self, "Run End Menu")
         
        self.mouse.register_callback(self.handle_mouse_click)
        self.temp = None
        self.time = None

        self.image_path = ImagePath()
        self.type_of = type_of

        if self.type_of == "CRIO":
            PrintImage(self, self.image_path.get("CrioEnd.png"))
        elif self.type_of == "TERMO":
            PrintImage(self, self.image_path.get("TermoEnd.png"))

        self.protocol("WM_DELETE_WINDOW", self.close)
        self.add_extern_event = None
        self.add_event_cancel = None
        self.localfocus = True
        self.second_screen_value = True

    def close(self):
        if not self.add_extern_event == None:
            self.add_extern_event()
            
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
        elif event == "__EVENT_CANCEL__":
            self.add_event_cancel = callback

    def handle_mouse_click(self, x, y):
        print("DEBUG: Mouse click position: ", x, y)
        if self.get_localfocus():
            if x >= 830 and x <= 980 and y >=  480 and y <=  600:
                #self.set_localfocus(False)
                self.close()
            else:
                print("out of range")
        else:
            if self.get_second_screen() == False:
                self.set_localfocus(True)
