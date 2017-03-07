#!/usr/bin/env python
import numpy as np
import math
import csv
# import the required packages here

class VP_Classifier:
    """ Voted Perceptron Classifier """

    def fit(self, X, labels):
        """ Train Voted Perceptron  """
        # Init variables
        self.c = np.zeros(1)
        self.w = np.zeros((1, len(X[0])))

        e = 10 # epochs
        y_hat = 0
        k = 0

        for _ in range(e):
            for idx, (x, y) in enumerate(zip(X, labels)):
                y_hat = int(np.sign(np.dot(self.w[k], x)))

                if y_hat == y:
                    self.c[k] += 1
                else:
                    self.w = np.append(self.w, [self.w[k] + y*x], axis=0)
                    self.c = np.append(self.c, [1])
                    k += 1


    def predict(self, X):
        """ Takes vector of samples and returns predictions """
        preds = []
        y_hat = 0

        for x_test in X:
            for i in range(len(self.c)):
                y_hat += self.c[i] * np.sign(np.dot(self.w[i], x_test))

            if int(np.sign(y_hat)) == -1:
                preds.append(0)
            else:
                preds.append(1)
            y_hat = 0

        return preds



def run(Xtrain_file, Ytrain_file, test_data_file=None, pred_file=None):
    '''The function to run your ML algorithm on given datasets, generate the predictions and save them into the provided file path

    Parameters
    ----------
    Xtrain_file: string
        the path to Xtrain csv file
    Ytrain_file: string
        the path to Ytrain csv file
    test_data_file: string
        the path to test data csv file
    pred_file: string
        the prediction file to be saved by your code. You have to save your predictions into this file path following the same format of Ytrain_file
    '''

    ## your implementation here
    # read data from Xtrain_file, Ytrain_file and test_data_file
    X_train = np.genfromtxt(Xtrain_file, delimiter=',').astype(int)
    Y_train = np.genfromtxt(Ytrain_file, delimiter=',').astype(int)
    Y_train[Y_train == 0] = -1
    if test_data_file != None:
        test = np.genfromtxt(test_data_file, delimiter=',').astype(int)

    model = VP_Classifier()
    model.fit(X_train, Y_train)
    results = model.predict(test)


    with open(pred_file, 'w') as f:
        writer = csv.writer(f)
        for val in results:
            writer.writerow([val])
    # your algorithm

    # save your predictions into the file pred_file


# define other functions here
if __name__ == '__main__':
    run('../data/Xtrain.csv', '../data/Ytrain.csv', '../data/Xtrain.csv', '../data/pred_file.csv')
