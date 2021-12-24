import cv2
import time

from HandDetector import HandDetector as hdt
from Drawing import Drawing

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
detector = hdt()

# Drawing
drawing = Drawing(camWidth, camHeight)

# Main loop
while vcap.isOpened():
    # Read camere
    success, img = vcap.read()
    img = cv2.flip(img, 1)

    if not success:
        print("Ignoring empty camera frame.")
        continue

    # Detect hand
    img = detector.findHand(img)
    detector.findPosition(img)


    if detector.isGesturePointing():
        cv2.putText(img, 'Drawing', (10, 400), cv2.FONT_HERSHEY_PLAIN, 3, (255, 0, 255), 3)

        xCurr = detector.landmarkList[8][0]
        yCurr = detector.landmarkList[8][1]

        drawing.draw(xCurr, yCurr, xPrev, yPrev)
        
        xPrev = xCurr
        yPrev = yCurr

    elif detector.isGestureErase():
        cv2.putText(img, 'Erasing', (10, 400), cv2.FONT_HERSHEY_PLAIN, 3, (255, 0, 255), 3)
        xCurr = int((detector.landmarkList[8][0] + detector.landmarkList[12][0]) / 2)
        yCurr = int((detector.landmarkList[8][1] + detector.landmarkList[12][1]) / 2)

        drawing.erase(xCurr, yCurr, xPrev, yPrev)
        cv2.circle(img, (xCurr, yCurr), 11, (0, 0, 0))
        
        xPrev = xCurr
        yPrev = yCurr

    else:
        xPrev = -1
        yPrev = -1 

    if detector.isGestureThumbUp():
        cv2.putText(img, 'Save Picture', (10, 400), cv2.FONT_HERSHEY_PLAIN, 3, (255, 0, 255), 3)
        drawing.save()

    if detector.isGestureAllOpen():
        cv2.putText(img, 'Delete All', (10, 400), cv2.FONT_HERSHEY_PLAIN, 3, (255, 0, 255), 3)
        drawing.deleteAll()

    currTime = time.time()
    fps = 1 / (currTime - prevTime)
    prevTime = currTime

    img = drawing.overlayOnTopOf(img)

    cv2.putText(img, "FPS: %d" % fps, (10, 70), cv2.FONT_HERSHEY_PLAIN, 3, (255, 255, 0), 3)

    cv2.imshow("Image", img)
    cv2.waitKey(20)
    if cv2.getWindowProperty("Image", 4) < 1:
        break

vcap.release()
cv2.destroyAllWindows()
