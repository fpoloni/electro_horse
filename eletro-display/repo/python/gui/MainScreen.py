import sys
import getopt

import tkinter as tk
from tkinter import *

from Settings import Settings
from MouseListener import MouseListener
from Run import Run
from Movie import LoadMovie
from DataBase import DataBase
from PIL import Image, ImageTk

from BorderConnection import BorderConnection
from ImagePath import ImagePath


class PrintImage:
    def __init__(self, container, image_path):
        render = ImageTk.PhotoImage(Image.open(image_path))
        img = Label(container, image=render)

        img.image = render
        img.place(x=0, y=0)


class Main(tk.Tk):
    def __init__(self, size, title, ip_address):
        super().__init__()

        self.border_connection = BorderConnection(ip_address)

        self.settings = None
        self.localfocus = True
        self.second_screen_value = False

        self.mouse = MouseListener(self, title)
        #
        self.mouse.register_callback(self.handle_mouse_click)

        self.attributes('-fullscreen', True)
        self.title(title)

        self.container = self
        self.image_path = ImagePath()

        self.data_base = DataBase()
        self.data_base.file_create()

        PrintImage(self, self.image_path.get("Menu.png"))

    def handle_mouse_click(self, x, y):
        print("Mouse click position: ", x, y)
        if self.get_localfocus():
            if x >= 0 and x <= 512 and y >= 200 and y <= 700:
                #self.set_localfocus(False)
                self.start_setting("CRIO")
            elif x > 512 and x <= 1024 and y >= 200 and y <= 700:
                #self.set_localfocus(False)
                self.start_setting("TERMO")
            else:
                print("out of range")
        else:
            if self.get_second_screen() == False:
                self.set_localfocus(True)

    def get_localfocus(self):
        return self.localfocus

    def get_second_screen(self):
        return self.second_screen_value

    def second_screen(self, value):
        #self.container.deiconify()
        self.second_screen_value = value

    def set_localfocus(self, value):
        self.localfocus = value

    def start_setting(self, type_of):
        self.setting = Settings(
            self, type_of, self.border_connection, self.data_base)
        self.setting.add_callback(self.second_screen, "__EVENT_CLOSE__")
        self.setting.add_callback(self.start_run,     "__EVENT_START__")
        self.setting.add_callback(self.minimize_main, "__EVENT_BG__")

        self.second_screen_value = True
        #self.set_localfocus(False)

    def start_run(self, field):
        run = Run(self, field, self.border_connection)
        run.add_callback(self.second_screen, "__EVENT_CLOSE__")

        self.second_screen_value = True
        #self.set_localfocus(False)

    def minimize_main(self):
        #self.container.iconify()
        pass

    def close_window(self):
        # self.mouse.stop()
        self.window.destroy()
        self.border_connection.stop()


def main(argv):
   ip_address = '127.0.0.1'
   try:
      opts, args = getopt.getopt(argv, "hi:", ["ip_address"])
   except getopt.GetoptError:
      print('test.py -i <inputfile> -o <outputfile>')
      sys.exit(2)
   for opt, arg in opts:
      if opt == '-h':
         print("Available commands")
         print('-i | --ipaddress = ip address for board app')
         sys.exit()
      elif opt in ("-i", "--ipaddress"):
         ip_address = arg
   print('Input IP address value "', ip_address)
   return ip_address

if __name__ == "__main__":
    ip_address = main(sys.argv[1:])
    # splash = LoadMovie("EletroHorse", ImagePath().get("Splash.mp4"))
    # if splash.status() == True:
    app = Main("1024x600+0+0", "EletroHorse", ip_address)
    app.mainloop()
    # else:
        # print("Rised problem during the program start.")
