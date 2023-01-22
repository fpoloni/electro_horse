import tkinter as tk
from tkinter import *

from ImagePath import ImagePath
from MouseListener import MouseListener

from PIL import Image, ImageTk


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


class Configuration(tk.Toplevel):
    def __init__(self, parent, type_of, data_base):
        super().__init__(parent)

        # self.geometry('1024x600+0+0')
        self.attributes('-fullscreen', True)
        self.title('CRIO')

        self.mouse = MouseListener(self, "Configuration Menu")
         
        self.mouse.register_callback(self.handle_mouse_click)
        self.type_of = type_of
        self.image_path = ImagePath()

        self.InitTempMax = 0
        self.InitTempMin = 0
        self.InitTime = 0
        self.InitPwm = 0
        
        self.LimitTimeMax = 50
        self.LimitTimeMin = 10

        self.data_base = data_base
        data = self.data_base.file_read(type_of)

        if type_of == "CRIO":
            PrintImage(self, self.image_path.get("CrioConfig.png"))
            self.LimitTempMax = 20
            self.LimitTempMin = -5
        elif type_of == "TERMO":
            PrintImage(self, self.image_path.get("TermoConfig.png"))
            self.LimitTempMax = 60
            self.LimitTempMin = 30

        if not len(data) == 0:
            self.InitTempMax = data[0]
            self.InitTempMin = data[1]
            self.InitTime = data[2]
            self.InitPwm = data[3]

        self.tempMin = LableValues(self, str(self.InitTempMin), 680, 160)
        self.tempMax = LableValues(self, str(self.InitTempMax), 680, 250)
        self.time = LableValues(self, str(self.InitTime),       680, 340)

        self.protocol("WM_DELETE_WINDOW", self.close)
        self.add_extern_event = None
        self.localfocus = True
        self.loaded_fields = None

    def close(self):
        self.add_extern_event()
        # self.mouse.stop()
        self.destroy()

    def set_localfocus(self, value):
        self.localfocus = value

    def get_localfocus(self):
        return self.localfocus

    def add_callback(self, callback):
        self.add_extern_event = callback

    def handle_mouse_click(self, x, y):
        print("DEBUG: Mouse click position: ", x, y)
        if self.get_localfocus():
            if x >= 300 and x <= 480 and y >= 490 and y <= 610:
                # #self.set_localfocus(False)
                self.record_file()
                self.close()
            elif x >= 590 and x <= 720 and y >= 490 and y <= 610:
                # #self.set_localfocus(False)
                self.close()
                
            elif x >= 840 and x <= 920 and y >= 187 and y <= 253:
                value = int(self.tempMin.get_value())
                if value < self.LimitTempMax:
                    self.tempMin.set_value(str(value+1))
                else:
                    self.tempMin.set_value(str(self.LimitTempMin))
            elif x >= 935 and x <= 1016 and y >= 187 and y <= 253:
                value = int(self.tempMin.get_value())
                if value > self.LimitTempMin:
                    self.tempMin.set_value(str(value-1))
                else:
                    self.tempMin.set_value(str(self.LimitTempMax))
                    
            elif x >= 840 and x <= 920 and y >= 273 and y <= 340:
                value = int(self.tempMax.get_value())
                if value < self.LimitTempMax:
                    self.tempMax.set_value(str(value+1))
                else:
                    self.tempMax.set_value(str(self.LimitTempMin))
            elif x >= 935 and x <= 1016 and y >= 273 and y <= 340:
                value = int(self.tempMax.get_value())
                if value > self.LimitTempMin:
                    self.tempMax.set_value(str(value-1))
                else:
                    self.tempMax.set_value(str(self.LimitTimeMax))
                    
            elif x >= 840 and x <= 920 and y >= 360 and y <= 430:
                value = int(self.time.get_value())
                if value < self.LimitTimeMax:
                    self.time.set_value(str(value+1))
                else:
                    self.time.set_value(str(self.LimitTimeMin))
            elif x >= 935 and x <= 1016 and y >= 360 and y <= 430:
                value = int(self.time.get_value())
                if value > self.LimitTimeMin:
                    self.time.set_value(str(value-1))
                else:
                    self.time.set_value(str(self.LimitTimeMax))
            else:
                print("out of range")
          
    def record_file(self):
        self.data_base.file_update(self.type_of,
                                    int(self.tempMax.get_value()),
                                    int(self.tempMin.get_value()),
                                    int(self.time.get_value()),
                                    1)

    def get_time(self):
        return self.time.get_value()
