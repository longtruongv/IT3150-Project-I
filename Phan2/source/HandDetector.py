import cv2
import mediapipe as mp
import math 

class HandDetector():
    FINGER_THUMB = 0
    FINGER_INDEX = 1
    FINGER_MIDDLE = 2
    FINGER_RING = 3
    FINGER_PINKY = 4
    FINGERS = [FINGER_THUMB, FINGER_INDEX, FINGER_MIDDLE, FINGER_RING, FINGER_PINKY]

    def __init__(self):
        self.mpHands = mp.solutions.hands
        self.hands = self.mpHands.Hands()
        
        self.mpDraw = mp.solutions.drawing_utils
        self.mpDrawStyles = mp.solutions.drawing_styles

        self.isOpeningFinger = {
            self.FINGER_THUMB: False, 
            self.FINGER_INDEX: False, 
            self.FINGER_MIDDLE: False,
            self.FINGER_RING: False, 
            self.FINGER_PINKY: False
        }

    # Tìm bàn tay trong ảnh và vẽ landmark
    def findHand(self, img, drawLandmarks=True):
        imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        self.results = self.hands.process(imgRGB)

        if self.results.multi_hand_landmarks:
            if drawLandmarks:
                for handLandmarks in self.results.multi_hand_landmarks:      
                    self.mpDraw.draw_landmarks(img, handLandmarks, self.mpHands.HAND_CONNECTIONS,
                        self.mpDrawStyles.get_default_hand_landmarks_style(),
                        self.mpDrawStyles.get_default_hand_connections_style())
        
        return img

    # Lấy các tọa độ landmark của bàn tay
    def findPosition(self, img, handIndex=0):
        self.landmarkList  = []

        if self.results.multi_hand_landmarks:
            # lấy bàn tay index = 0
            thisHand = self.results.multi_hand_landmarks[handIndex]

            for id, lm in enumerate(thisHand.landmark):
                h, w, c = img.shape
                cx, cy = int(lm.x * w), int(lm.y * h)
                self.landmarkList.append((cx, cy))

    # Tính khoảng cách (bình phương) 1 điểm landmark tới điểm id = 0 (cổ tay)
    def getSqrDistTo0(self, lmID):
        distX = self.landmarkList[lmID][0] - self.landmarkList[0][0]
        distY = self.landmarkList[lmID][1] - self.landmarkList[0][1]
        return distX**2 + distY**2

    def calcuOpeningFingers(self):
        if self.landmarkList:
            self.isOpeningFinger[self.FINGER_THUMB] = self.getSqrDistTo0(4) > 1.3 * self.getSqrDistTo0(3)
            self.isOpeningFinger[self.FINGER_INDEX] = self.getSqrDistTo0(8) > self.getSqrDistTo0(6)
            self.isOpeningFinger[self.FINGER_MIDDLE] = self.getSqrDistTo0(12) > self.getSqrDistTo0(10)
            self.isOpeningFinger[self.FINGER_RING] = self.getSqrDistTo0(16) > self.getSqrDistTo0(14)
            self.isOpeningFinger[self.FINGER_PINKY] = self.getSqrDistTo0(20) > self.getSqrDistTo0(18)
        else:
            self.isOpeningFinger[self.FINGER_THUMB] = False
            self.isOpeningFinger[self.FINGER_INDEX] = False
            self.isOpeningFinger[self.FINGER_MIDDLE] = False
            self.isOpeningFinger[self.FINGER_RING] = False
            self.isOpeningFinger[self.FINGER_PINKY] = False


    def isGesturePointing(self):
        return self.isOpeningFinger[self.FINGER_INDEX] \
            and not self.isOpeningFinger[self.FINGER_MIDDLE] \
            and not self.isOpeningFinger[self.FINGER_RING] \
            and not self.isOpeningFinger[self.FINGER_PINKY]

    def isGestureErase(self):
        return self.isOpeningFinger[self.FINGER_INDEX] \
            and self.isOpeningFinger[self.FINGER_MIDDLE] \
            and not self.isOpeningFinger[self.FINGER_RING] \
            and not self.isOpeningFinger[self.FINGER_PINKY]

    def isGestureThumbUp(self):
        return self.isOpeningFinger[self.FINGER_THUMB] \
            and not self.isOpeningFinger[self.FINGER_INDEX] \
            and not self.isOpeningFinger[self.FINGER_MIDDLE] \
            and not self.isOpeningFinger[self.FINGER_RING] \
            and not self.isOpeningFinger[self.FINGER_PINKY]

    def isGestureAllOpen(self):
        return self.isOpeningFinger[self.FINGER_THUMB] \
            and self.isOpeningFinger[self.FINGER_INDEX] \
            and self.isOpeningFinger[self.FINGER_MIDDLE] \
            and self.isOpeningFinger[self.FINGER_RING] \
            and self.isOpeningFinger[self.FINGER_PINKY]

    # Tính bán kính khi tẩy
    # -> khoảng cách đỉnh ngón trỏ và ngón giữa chia đôi
    def getEraserRadius(self):
        xDist = self.landmarkList[8][0] - self.landmarkList[12][0]
        yDist = self.landmarkList[8][1] - self.landmarkList[12][1]
        return int(math.sqrt(xDist**2 + yDist**2) / 2)