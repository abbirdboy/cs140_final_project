import numpy as np
import math

class NB_Classifier:
    """ Simple Naive Bayes Classifier """

    def fit(self, X, y):
        """ Train NB classifier  """
        # train set size
        self.train_size = float(len(y))

        # number of instances per class
        self.class_0, self.class_1 = np.bincount(y)

        # log priors
        self.log_class_0_prior = math.log(self.class_0 / self.train_size)
        self.log_class_1_prior = math.log(self.class_1 / self.train_size)

        # total vocabulary
        self.V = len(X[0])

        # total tokens in each class (scalar)
        self.class_0_wtot = 0 + self.V*0.5 # add one-smoothing of 0.5
        self.class_1_wtot = 0 + self.V*0.5 # add one-smoothing

        # total per token in each class (vector)
        self.class_0_vectot = np.full(len(X[0]), 0.5) # ones == add one-smoothing
        self.class_1_vectot = np.full(len(X[0]), 0.5)

        self.loglike_0_vec = np.zeros(len(X[0]), dtype=np.int)
        self.loglike_1_vec = np.zeros(len(X[0]), dtype=np.int)

        # sum of the total tokens
        for x, y in zip(X, y):
            if y == 0:
                self.class_0_wtot += np.sum(x)
                self.class_0_vectot += x
            else:
                self.class_1_wtot += np.sum(x)
                self.class_1_vectot += x

        for i in range(self.V):
            self.loglike_0_vec[i] = math.log(self.class_0_vectot[i]/float(self.class_0_wtot))
            self.loglike_1_vec[i] = math.log(self.class_1_vectot[i]/float(self.class_1_wtot))

    def predict(self, X):
        """ Takes vector of samples and returns predictions """
        preds = []
        sum_0 = self.log_class_0_prior
        sum_1 = self.log_class_1_prior

        for i, x in enumerate(X):
            for idx, val in enumerate(x):
                if val != 0:
                    sum_0 += (self.loglike_0_vec[idx]*val)
                    sum_1 += (self.loglike_1_vec[idx]*val)


            preds.append(np.argmax([sum_0, sum_1]))
            sum_0 = self.log_class_0_prior
            sum_1 = self.log_class_1_prior

        return preds
