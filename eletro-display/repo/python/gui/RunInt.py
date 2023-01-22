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

class RunInt(tk.Toplevel):
    def __init__(self, parent, type_of):
        super().__init__(parent)

        # self.geometry('1024x600+0+0')
        self.attributes('-fullscreen', True)
        self.mouse = MouseListener(self, "Run Int Menu")
         
        self.mouse.register_callback(self.handle_mouse_click)
        self.temp = None
        self.time = None

        self.image_path = ImagePath()
        self.type_of = type_of
        
        if self.type_of == "CRIO":
            PrintImage(self, self.image_path.get("CrioExeInt.png"))
        elif self.type_of == "TERMO":
            PrintImage(self, self.image_path.get("TermoExeInt.png"))

        self.protocol("WM_DELETE_WINDOW", self.close)
        self.add_extern_event = None
        self.add_event_cancel = None
        self.localfocus = True

    def close(self):
        # self.mouse.stop()
        self.destroy()

    def set_localfocus(self, value):
        self.localfocus = value

    def get_localfocus(self):
        return self.localfocus

    def add_callback(self, callback, event):
        if event == "__EVENT_CLOSE__":
            self.add_extern_event = callback
        elif event == "__EVENT_CANCEL__":
            self.add_event_cancel= callback

    def handle_mouse_click(self, x, y):
        print("DEBUG: Mouse click position: ", x, y)
        if x >= 357 and x <= 478 and y >= 519 and y <= 608:
            if not self.add_extern_event == None:
                self.add_extern_event()
            self.close()
        elif x >= 563 and x <= 658 and y >= 519 and y <= 608:
            if not self.add_event_cancel == None:
                self.add_event_cancel(False)
            self.close()
        else:
            print("out of range")

    def get_setValues(self):
        return self.tempMax, self.tempMin, self.time

