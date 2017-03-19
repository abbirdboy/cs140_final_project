#!/usr/bin/env python
import numpy as np
import csv
from model import NB_Classifier
import time
# import the required packages here

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
    start = time.time()
   
    X_train = np.genfromtxt(Xtrain_file, delimiter=',').astype(int)
    Y_train = np.genfromtxt(Ytrain_file, delimiter=',').astype(int)
    
    print "It took {} seconds to load files".format(time.time()-start)
    if test_data_file != None:
        test = np.genfromtxt(test_data_file, delimiter=',').astype(int)

    start = time.time()
   
    model = NB_Classifier()
    model.fit(X_train, Y_train)
    print "It took {} seconds to train model".format(time.time()-start)
    
    start = time.time()
    
    results = model.predict(test)
    
    print "It took {} seconds to predict".format(time.time()-start)
    
    # for x in results:
    #     print(x)

    # with open(pred_file, 'w') as f:
#         writer = csv.writer(f)
#         for val in results:
#             writer.writerow([val])
    # your algorithm

    # save your predictions into the file pred_file


# define other functions here
if __name__ == '__main__':
    run('../../data/Xtrain.csv', '../../data/Ytrain.csv', '../../data/Xtrain.csv', '../../data/pred_file.csv')
