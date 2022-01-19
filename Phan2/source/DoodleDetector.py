from cProfile import label
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3' 
import tensorflow as tf
from tensorflow import keras
import numpy as np
from sklearn.model_selection import train_test_split
import pickle

class DoodleDetector():
    def __init__(self):
        print("Doodle Detector")
    
    ####################
    ## BUILD FEATURES ##
    ####################
    
    # Đọc dữ liệu từ dataset và biến đổi để có thể đưa vào train và test 
    def buildFeatures(self, testRatio=0.1):
        X_data = []
        Y_data = []

        self.labelNames = []

        folderPath = "..\\data\\dataset\\doodleImages"
        datasetList = os.listdir(folderPath)

        for i in range(len(datasetList)):
            fileName = datasetList[i] 
            self.labelNames.append(os.path.splitext(fileName)[0])
            
            dataset = np.load(f"{folderPath}/{fileName}")
            for data in dataset:
                data = data / 255.0
                X_data.append(data)
                Y_data.append(i)

        X_data = np.array(X_data)
        Y_data = np.array(Y_data)
        (self.X_train, self.X_test, self.Y_train, self.Y_test) = train_test_split(X_data, Y_data, test_size=testRatio)
    # End BUILD FEATURES


    ###########
    ## TRAIN ##
    ###########

    def train(self, epochs=5):
        self.model = keras.Sequential([
            keras.layers.Dense(256, activation=tf.nn.relu, input_dim=784),
            keras.layers.Dense(128, activation=tf.nn.relu),
            keras.layers.Dense(len(self.labelNames), activation=tf.nn.softmax)
        ])

        self.model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
        self.model.fit(self.X_train, self.Y_train, epochs=epochs)
        self.model.summary()
    # End TRAIN


    ##########
    ## TEST ##
    ##########

    def test(self):
        self.model.evaluate(self.X_test, self.Y_test)
    # End TEST


    ##############
    ## CLASSIFY ##
    ##############

    def classify(self, numpyImg, confidence=0.7):
        numpyImg = cropImage(numpyImg)
        prediction = self.model.predict(np.array([numpyImg]))[0]
        
        if (np.max(prediction) > confidence):
            return self.labelNames[np.argmax(prediction)]
        else:
            return "Can't Detect"
    # End CLASSIFY


    def saveModel(self):
        self.model.save("..\\data\\model")
        with open("..\\data\\model\\data.pkl", "wb") as output:
            # pickle.dump([self.X_train, self.X_test, self.Y_train, self.Y_test, self.labelNames], output)
            pickle.dump(self.labelNames, output)

    def loadModel(self):
        self.model = keras.models.load_model("..\\data\\model")
        with open("..\\data\\model\\data.pkl", "rb") as input:
            # self.X_train, self.X_test, self.Y_train, self.Y_test, self.labelNames = pickle.load(input)
            self.labelNames = pickle.load(input)

# End DOODLE DETECTOR


import cv2 

# Crop ảnh dạng numpy array lấy vùng có hình vẽ và resize về kích thước 28x28
def cropImage(numpyImg):
    # Mở rộng ảnh ban đầu --> Tránh vùng được chọn nằm ngoài phạm vi ảnh
    height, width, _ = numpyImg.shape
    if width < height:
        borderHori = int((height - width)/2)
        borderVert = 0
    else:
        borderHori = 0
        borderVert = int((width - height)/2)

    numpyImg = cv2.copyMakeBorder(numpyImg, borderVert, borderVert, \
        borderHori, borderHori, cv2.BORDER_CONSTANT, value=(0, 0, 0))

    # Chuyển về dạng đen trắng
    gray = cv2.cvtColor(numpyImg, cv2.COLOR_BGR2GRAY)
    _, thresh_gray = cv2.threshold(gray, thresh=100, maxval=255, type=cv2.THRESH_BINARY)

    # Tìm vị trí hình vẽ có contour lớn nhất
    contours, _ = cv2.findContours(thresh_gray, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

    max = (0, 0, 0, 0)
    max_area = 0
    for cont in contours:
        x, y, w, h = cv2.boundingRect(cont)
        area = w*h
        if area > max_area:
            max = x, y, w, h
            max_area = area

    x, y, w, h, = max
    if not (w > 0 and h > 0):
        return np.zeros(784)

    # Crop vùng có hình vẽ về 28x28
    sqrCenter = (x + w/2, y + h/2) 
    if w < h:
        sqrSide = h
    else:
        sqrSide = w

    x = int(sqrCenter[0] - sqrSide/2)
    y = int(sqrCenter[1] - sqrSide/2)

    roi = numpyImg[y: y + sqrSide, x: x + sqrSide, 0]
    roi = cv2.resize(roi, (28, 28), interpolation=cv2.INTER_AREA)

    visualizeNumpyImg(roi)

    roi = roi / 255.0
    return roi.flatten()


import matplotlib.pyplot as plt

# Biểu diễn ảnh dạng numpy array
def visualizeNumpyImg(croppedNumpyImg):
    plt.figure()
    plt.imshow(croppedNumpyImg)
    plt.colorbar()
    plt.grid(False)
    plt.savefig("..\\data\\output\\visualize.png")

