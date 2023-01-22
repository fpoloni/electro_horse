import time
import tkinter as tk

from tkinter import ttk
from tkinter import *
from MouseListener import MouseListener
from ImagePath import ImagePath
from PIL import Image, ImageTk

class PrintImage:
    def __init__(self, container, image_path):

        render = ImageTk.PhotoImage(Image.open(image_path))
        img = Label(container, image=render)
        img.image = render
        img.place(x=0, y=0)

class LableValues:
    def __init__(self, container, input_, x, y):
        self.txt = Label(container, height=1, width=5, font=("Arial", 30), background="white", text=input_)
        self.txt.place(x=x, y=y)

    def set_value(self, value):
        self.txt['text'] = value
    def get_value(self):
        return self.txt['text']

class PreparationInt(tk.Toplevel):
    def __init__(self, parent, type_of, value):
        super().__init__(parent)

        # self.geometry('1024x600+0+0')
        self.attributes('-fullscreen', True)

        self.value = value
        self.type_of = type_of
        self.operation = False
        self.localfocus = True
        self.add_event_close = None
        self.add_event_start = None
        self.add_event_cancel = None

        self.mouse = MouseListener(self, "PreparationInt Menu")
         
        self.mouse.register_callback(self.handle_mouse_click)
        
        self.image_path = ImagePath()
        PrintImage(self, self.image_path.get("Menu.png"))

        # Windows path
        if self.type_of == "CRIO":
            if self.value == "INT":
                PrintImage(self, self.image_path.get("CrioPrepInt.png"))
            elif self.value == "END":
                PrintImage(self, self.image_path.get("CrioPrepEnd.png"))
            else:
                pass
        elif self.type_of == "TERMO":
            if self.value == "INT":
                PrintImage(self, self.image_path.get("TermoPrepInt.png"))
            elif self.value == "END":
                PrintImage(self, self.image_path.get("TermoPrepEnd.png"))
            else:
                pass

        self.protocol("WM_DELETE_WINDOW", self.close)

    def close(self):
        # self.mouse.stop()
        self.destroy()

    def set_localfocus(self, value):
        self.localfocus = value

    def get_localfocus(self):
        return self.localfocus

    def add_callback(self, callback, event):
        if event == "__EVENT_CLOSE__":
            self.add_event_close = callback
        elif event == "__EVENT_START__":
            self.add_event_start= callback
        elif event == "__EVENT_CANCEL__":
            self.add_event_cancel= callback

    def handle_mouse_click(self, x, y):
        print("DEBUG: Mouse click position: ", x, y)
        #confirm button
        if x >= 357 and x <= 478 and y >=  519 and y <=  608:
            if self.value == "INT":
                self.add_event_close()
                self.close()
            elif self.value == "END":
                self.add_event_start()
                self.close()
                
        #cancel button
        elif x >= 563 and x <= 658 and y >=  519 and y <=  608:
            if self.value == "INT":
                self.add_event_cancel(False)
                self.close()
            elif self.value == "END":
                self.add_event_close()
                self.close()
        else:
            print("out of range")
