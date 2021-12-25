import cv2
import mediapipe as mp

class HandDetector():
    FINGER_THUMB = 0
    FINGER_INDEX = 1
    FINGER_MIDDLE = 2
    FINGER_RING = 3
    FINGER_PINKY = 4

    def __init__(self):
        self.mpHands = mp.solutions.hands
        self.hands = self.mpHands.Hands()
        
        self.mpDraw = mp.solutions.drawing_utils
        self.mpDrawStyles = mp.solutions.drawing_styles

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

    def findPosition(self, img, handIndex=0):
        self.landmarkList  = []

        if self.results.multi_hand_landmarks:
            thisHand = self.results.multi_hand_landmarks[handIndex]
            for id, lm in enumerate(thisHand.landmark):
                h, w, c = img.shape
                cx, cy = int(lm.x * w), int(lm.y * h)
                self.landmarkList.append((cx, cy))

    def getSqrDistTo0(self, lmID):
        distX = self.landmarkList[lmID][0] - self.landmarkList[0][0]
        distY = self.landmarkList[lmID][1] - self.landmarkList[0][1]
        return distX**2 + distY**2

    def isOpeningFinger(self, finger):
        if self.landmarkList:
            return {
                self.FINGER_THUMB: self.getSqrDistTo0(4) > 1.3 * self.getSqrDistTo0(3),
                self.FINGER_INDEX: self.getSqrDistTo0(8) > self.getSqrDistTo0(6),
                self.FINGER_MIDDLE: self.getSqrDistTo0(12) > self.getSqrDistTo0(10),
                self.FINGER_RING: self.getSqrDistTo0(16) > self.getSqrDistTo0(14),
                self.FINGER_PINKY: self.getSqrDistTo0(20) > self.getSqrDistTo0(18),
            }.get(finger, False)
        else:
            return False

    def isGesturePointing(self):
        return self.isOpeningFinger(self.FINGER_INDEX) \
            and not self.isOpeningFinger(self.FINGER_MIDDLE) \
            and not self.isOpeningFinger(self.FINGER_RING) \
            and not self.isOpeningFinger(self.FINGER_PINKY)

    def isGestureErase(self):
        return self.isOpeningFinger(self.FINGER_INDEX) \
            and self.isOpeningFinger(self.FINGER_MIDDLE) \
            and not self.isOpeningFinger(self.FINGER_RING) \
            and not self.isOpeningFinger(self.FINGER_PINKY)

    def isGestureThumbUp(self):
        return self.isOpeningFinger(self.FINGER_THUMB) \
            and not self.isOpeningFinger(self.FINGER_INDEX) \
            and not self.isOpeningFinger(self.FINGER_MIDDLE) \
            and not self.isOpeningFinger(self.FINGER_RING) \
            and not self.isOpeningFinger(self.FINGER_PINKY)

    def isGestureAllOpen(self):
        return self.isOpeningFinger(self.FINGER_THUMB) \
            and self.isOpeningFinger(self.FINGER_INDEX) \
            and self.isOpeningFinger(self.FINGER_MIDDLE) \
            and self.isOpeningFinger(self.FINGER_RING) \
            and self.isOpeningFinger(self.FINGER_PINKY)