import cv2
import time

from HandDetector import HandDetector
from Drawing import Drawing
from DoodleDetector import DoodleDetector

# For calculate FPS
prevTime = 0
currTime = 0

# Camera
camWidth = 480
camHeight = 640

vcap = cv2.VideoCapture(0)
vcap.set(3, camWidth)
vcap.set(4, camHeight)

# Hand detector
handDetector = HandDetector()

# Drawing
drawing = Drawing(camWidth, camHeight)

# Doodle detector
doodleDetector = DoodleDetector()
doodleDetector.loadModel()

thumbUpFlag = False
labelText = ""

# Main loop
while vcap.isOpened():
    # Read camera
    success, img = vcap.read()
    img = cv2.flip(img, 1)

    if not success:
        print("Ignoring empty camera frame.")
        continue

    # Detect hand
    img = handDetector.findHand(img)
    handDetector.findPosition(img)


    if handDetector.isGesturePointing():
        cv2.putText(img, 'Drawing', (10, 400), cv2.FONT_HERSHEY_PLAIN, 3, (255, 0, 255), 3)

        xCurr = handDetector.landmarkList[8][0]
        yCurr = handDetector.landmarkList[8][1]

        drawing.draw(xCurr, yCurr, xPrev, yPrev)
        
        xPrev = xCurr
        yPrev = yCurr

        thumbUpFlag = False

    elif handDetector.isGestureErase():
        cv2.putText(img, 'Erasing', (10, 400), cv2.FONT_HERSHEY_PLAIN, 3, (255, 0, 255), 3)
        
        xCurr = int((handDetector.landmarkList[8][0] + handDetector.landmarkList[12][0]) / 2)
        yCurr = int((handDetector.landmarkList[8][1] + handDetector.landmarkList[12][1]) / 2)

        eraserRadius = handDetector.getEraserRadius()
        drawing.erase(xCurr, yCurr, xPrev, yPrev, eraserRadius)
        cv2.circle(img, (xCurr, yCurr), eraserRadius, (0, 0, 0))
        
        xPrev = xCurr
        yPrev = yCurr

        thumbUpFlag = False

    else:
        xPrev = -1
        yPrev = -1


    if handDetector.isGestureThumbUp():
        cv2.putText(img, 'Save Picture', (10, 400), cv2.FONT_HERSHEY_PLAIN, 3, (255, 0, 255), 3)

        if not thumbUpFlag:
            labelText = doodleDetector.classify(drawing.imgCanvas)

            drawing.save()

            thumbUpFlag = True


    if handDetector.isGestureAllOpen():
        cv2.putText(img, 'Delete All', (10, 400), cv2.FONT_HERSHEY_PLAIN, 3, (255, 0, 255), 3)
        labelText = ""

        drawing.deleteAll()

        thumbUpFlag = False

    
    currTime = time.time()
    fps = 1 / (currTime - prevTime)
    prevTime = currTime

    img = cv2.bitwise_or(img, drawing.imgCanvas)

    cv2.putText(img, labelText, (10, 200), cv2.FONT_HERSHEY_PLAIN, 3, (0, 255, 255), 3)
    cv2.putText(img, "FPS: %d" % fps, (10, 70), cv2.FONT_HERSHEY_PLAIN, 3, (255, 255, 0), 3)

    cv2.imshow("Draw something", img)
    cv2.waitKey(20)
    if cv2.getWindowProperty("Draw something", 4) < 1:
        break

vcap.release()
cv2.destroyAllWindows()