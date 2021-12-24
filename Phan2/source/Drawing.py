import numpy as np
import cv2

class Drawing():
    def __init__(self, width, height):
        self.width = width
        self.height = height

        self.imgCanvas = np.zeros((width, height, 3), np.uint8)
        self.drawColor = (255, 255, 255)
        self.drawThickness = 7

    def overlayOnTopOf(self, img):
        imgInv = cv2.bitwise_not(self.imgCanvas)
        img = cv2.bitwise_and(img, imgInv)
        img = cv2.bitwise_or(img, self.imgCanvas)
        return img

    def draw(self, xCurr, yCurr, xPrev, yPrev):
        if xCurr > 0 and yCurr > 0 and xPrev > 0 and yPrev > 0:
            cv2.line(self.imgCanvas, (xPrev, yPrev), (xCurr, yCurr), self.drawColor, self.drawThickness)

    def erase(self, xCurr, yCurr, xPrev, yPrev):
        if xCurr > 0 and yCurr > 0 and xPrev > 0 and yPrev > 0:
            cv2.line(self.imgCanvas, (xPrev, yPrev), (xCurr, yCurr), (0, 0, 0), 3 * self.drawThickness)

    def deleteAll(self):
        self.imgCanvas = np.zeros((self.width, self.height, 3), np.uint8)

    def save(self):
        imgInv = cv2.bitwise_not(self.imgCanvas)
        cv2.imwrite("output.jpg", imgInv)
        


        




    








# from tkinter import *
# root = Tk()
# root.title("Paint Application")
# root.geometry("500x350")
# def paint(event):
#     # get x1, y1, x2, y2 co-ordinates
#     x1, y1 = (event.x-3), (event.y-3)
#     x2, y2 = (event.x+3), (event.y+3)
#     color = "black"
#     # display the mouse movement inside canvas
#     wn.create_oval(x1, y1, x2, y2, fill=color, outline=color)
# # create canvas
# wn=Canvas(root, width=500, height=350, bg='white')
# # bind mouse event with canvas(wn)
# wn.bind('<B1-Motion>', paint)
# wn.pack()
# root.mainloop()