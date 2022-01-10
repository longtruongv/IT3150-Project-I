import cv2
import numpy as np

class Drawing():
    def __init__(self, width, height):
        self.width = width
        self.height = height

        self.imgCanvas = np.zeros((width, height, 3), np.uint8)
        self.drawColor = (255, 255, 255)
        self.drawThickness = 7

    def draw(self, xCurr, yCurr, xPrev, yPrev):
        if (xCurr > 0 or xCurr < self.width) and (yCurr > 0 or yCurr < self.height) and xPrev > 0 and yPrev > 0:
            cv2.line(self.imgCanvas, (xPrev, yPrev), (xCurr, yCurr), self.drawColor, self.drawThickness)

    def erase(self, xCurr, yCurr, xPrev, yPrev, radius=21):
        if (xCurr > 0 or xCurr < self.width) and (yCurr > 0 or yCurr < self.height) and xPrev > 0 and yPrev > 0:        
            cv2.line(self.imgCanvas, (xPrev, yPrev), (xCurr, yCurr), (0, 0, 0), radius*2)

    def deleteAll(self):
        self.imgCanvas = np.zeros((self.width, self.height, 3), np.uint8)

    def save(self):
        cv2.imwrite("..\\data\\output\\output.jpg", self.imgCanvas)
        


    