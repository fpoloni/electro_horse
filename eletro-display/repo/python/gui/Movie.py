# importing libraries
import cv2
import numpy as np

class LoadMovie:
  def __init__(self, title, path):
        self.success = False
        cv2.namedWindow(title, cv2.WND_PROP_FULLSCREEN)
        cv2.setWindowProperty(title, cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)

        movie = cv2.VideoCapture(path)

        # Check if camera opened successfully
        if (movie.isOpened()== False):
          print("Error opening video  file")
        else:
          self.showInMovedWindow(title, movie, 0, 0)
          self.success = True

  def showInMovedWindow(self, title, movie, x, y):
        cv2.namedWindow(title)        # Create a named window
        cv2.moveWindow(title, x, y)   # Move it to (x,y)

        # Read until video is completed
        while(movie.isOpened()):
          # Capture frame-by-frame
          ret, frame = movie.read()
          if ret == True:
            # Display the resulting frame
            cv2.imshow(title, frame)
            # Press Q on keyboard to  exit
            if cv2.waitKey(25) & 0xFF == ord('q'):
              break
          # Break the loop
          else:
            break
        movie.release()
        # Closes all the frames
        cv2.destroyAllWindows()

  def status(self):
        return self.success
