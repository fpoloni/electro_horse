class MouseListener:
    def __init__(self, selt_root, name):
        self.callback_onclickevent = None
        self.counter = 0
        self.listener = None
        self.name = name
        
        selt_root.bind('<Motion>', self.motion)
        selt_root.bind('<Button-1>', self.click)
    
    def motion(self, event):
        x, y = event.x, event.y
        print('Move: {}, {}'.format(x, y))
    
    def click(self, event):
        x, y = event.x, event.y
        print('Name: ', self.name)
        print('Click: {}, {}'.format(x, y))
        
        self.callback_onclickevent(x, y)

    def register_callback(self, callback):
        self.counter = self.counter + 1
        self.callback_onclickevent = callback
        print("calling callback register function", self.counter)

