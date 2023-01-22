from sys import platform

class ImagePath:
    def __init__(self):
        self.out_string = ""

        if platform == "linux" or platform == "linux2":
            self.out_string = "/etc/eletro-image/"
        elif platform == "win32":
            self.out_string = "C:\\Users\\fpsantos\\Downloads\\"

    def get(self, name):
        return self.out_string + name