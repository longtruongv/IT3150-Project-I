import cv2
import numpy as np
from DoodleDetector import DoodleDetector
import threading
from threading import Thread

class Drawing():
    def __init__(self, width, height):
        self.width = width
        self.height = height

        self.imgCanvas = np.zeros((width, height, 3), np.uint8)
        self.drawColor = (255, 255, 255)
        self.drawThickness = 7

        self.dd = DoodleDetector()
        self.dd.loadData()

        self.saveFlag = False
        self.Text = ""

    def overlayOnTopOf(self, img):
        imgInv = cv2.bitwise_not(self.imgCanvas)
        img = cv2.bitwise_and(img, imgInv)
        img = cv2.bitwise_or(img, self.imgCanvas)

        cv2.putText(img, self.Text, (10, 200), cv2.FONT_HERSHEY_PLAIN, 3, (255, 0, 255), 3)
        return img

    def draw(self, xCurr, yCurr, xPrev, yPrev):
        if xCurr > 0 and yCurr > 0 and xPrev > 0 and yPrev > 0:
            cv2.line(self.imgCanvas, (xPrev, yPrev), (xCurr, yCurr), self.drawColor, self.drawThickness)
            self.saveFlag = False
            self.Text = ""

    def erase(self, xCurr, yCurr, xPrev, yPrev):
        if xCurr > 0 and yCurr > 0 and xPrev > 0 and yPrev > 0:
            cv2.line(self.imgCanvas, (xPrev, yPrev), (xCurr, yCurr), (0, 0, 0), 3 * self.drawThickness)
            self.saveFlag = False
            self.Text = ""

    def deleteAll(self):
        self.imgCanvas = np.zeros((self.width, self.height, 3), np.uint8)
        self.saveFlag = False
        self.Text = ""

    def save(self):
        if self.saveFlag:
            return

        cv2.imwrite("..\\data\\output\\output.jpg", self.imgCanvas)
        self.Text = self.dd.classify(self.imgCanvas)
        print(self.Text)
        self.saveFlag = True
        


    