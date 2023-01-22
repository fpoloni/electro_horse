import tkinter as tk

from tkinter import *
from MouseListener import MouseListener
from PreparationInt import PreparationInt
from ImagePath import ImagePath
from PIL import Image, ImageTk


class PrintImage:
    def __init__(self, container, image_path):

        render = ImageTk.PhotoImage(Image.open(image_path))
        img = Label(container, image=render)
        img.image = render
        img.place(x=0, y=0)


class GifAnimation:
    def __init__(self, container, image_path):
        self.frameCnt = 41
        self.frames = [PhotoImage(
            file=image_path, format='gif -index %i' % (i)) for i in range(self.frameCnt)]
        self.container = container
        self.container.after(0, self.show, 0)

    def show(self, ind):
        frame = self.frames[ind]
        ind += 1
        if ind == self.frameCnt:
            ind = 0
        img = Label(self.container, image=frame)
        img.image = frame
        img.place(x=287, y=0)
        self.container.after(50, self.show, ind)


class LableValues:
    def __init__(self, container, input_, x, y):
        self.txt = Label(container, height=1, width=5, font=(
            "Arial", 30), background="white", text=input_)
        self.txt.place(x=x, y=y)

    def set_value(self, value):
        self.txt['text'] = value

    def get_value(self):
        return self.txt['text']


class Preparation(tk.Toplevel):
    def __init__(self, parent, type_of, fields, border_connection):
        super().__init__(parent)

        # # self.geometry('1024x600+0+0')
        self.attributes('-fullscreen', True)
        self.type_of = type_of
        self.set_fields = fields
        self.operation = False
        self.border_connection = border_connection

        self.mouse = MouseListener(self, "Preparation Menu")
         
        self.mouse.register_callback(self.handle_mouse_click)
        self.image_path = ImagePath()

        # Windows path
        if self.type_of == "CRIO":
            PrintImage(self, self.image_path.get("CrioPrep.png"))
        elif self.type_of == "TERMO":
            PrintImage(self, self.image_path.get("TermoPrep.png"))

        self.temp = LableValues(self, "--", 600, 485)

        self.protocol("WM_DELETE_WINDOW", self.close)
        
        self.add_event_close = None
        self.add_event_start = None
        self.add_event_field = None

        self.localfocus = True
        self.run_active = False
        
        self.second_screen_value = True
        self.flag_close_to_start = False
        self.preparation_int_once = False
        
        # configuration data, state and status
        self.border_connection.add(self.set_fields, 0, 1, 0)
        
        self.border_connection.register_callback(
            self.set_temperature_value, "__PREPARATION__")
        
        self.border_connection.register_callback(
            self.finish_preparation, "__FINISH_PREPARATION__")
        
    def close(self):
        if self.flag_close_to_start == False:
            #send message with stop
            self.border_connection.add((0, 0, 0, 0, 2), 1, 0, 0)
            
        self.border_connection.unregister_callback("__PREPARATION__")
        self.border_connection.unregister_callback("__FINISH_PREPARATION__")
        
        if self.run_active == False:
            self.add_event_close()

        #FIXME: Verify close
        #self.border_connection.stop()
        # self.mouse.stop()
        self.destroy()

    def set_temperature_value(self, value):
        print("Setting temperature")
        self.temp.set_value(value)

    def get_second_screen(self):
        return self.second_screen_value

    def second_screen(self, value):
        self.second_screen_value = value

    def set_localfocus(self, value):
        self.localfocus = value

    def get_localfocus(self):
        return self.localfocus

    def add_callback(self, callback, event):
        if event == "__EVENT_CLOSE__":
            self.add_event_close = callback
        elif event == "__EVENT_START__":
            self.add_event_start = callback
        elif event == "__EVENT_FIELD__":
            self.add_event_field = callback

    def handle_mouse_click(self, x, y):
        print("DEBUG: Mouse click position: ", x, y)
        if self.get_localfocus():
            #close button
            if x >= 835 and x <= 970 and y >=  475 and y <=  575:
                self.pre_start_process(self.type_of, "INT")
            # # fake button to test
            # elif x >= 68 and x <= 170 and y >=  500 and y <=  580:
            #     self.pre_start_process(self.type_of, "END")
            else:
                print("out of range")
        else:
            if self.get_second_screen() == False:
                self.set_localfocus(True)
    
    def finish_preparation(self):
        if self.preparation_int_once == False:
            self.pre_start_process(self.type_of, "END")
            self.preparation_int_once = True

    # method to start the teraph process
    def close_to_start(self):
        self.flag_close_to_start = True
        self.run_active = True
        self.close()
        self.add_event_start()

    def pre_start_process(self, type_of, value):
        question = PreparationInt(self, type_of, value)
        # event when confirm button is pushed
        question.add_callback(self.close, "__EVENT_CLOSE__")
        # event when cancel button is pushed
        question.add_callback(self.second_screen, "__EVENT_CANCEL__")
        # event when cancel button is pushed
        question.add_callback(self.close_to_start, "__EVENT_START__")

        # #self.set_localfocus(False)
        self.second_screen(True)
