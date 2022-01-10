from DoodleDetector import DoodleDetector

dd = DoodleDetector()
dd.buildFeatures(0.1)
dd.train(10)
dd.test()
dd.saveModel()