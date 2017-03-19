#include "model.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>


// Constructor: Loads Xtrain and Ytrain files
NB_Classifier::NB_Classifier(string Xtrain_file, string Ytrain_file, int rows, int cols)
{
   ifstream X_file(Xtrain_file.c_str());
   ifstream Y_file(Ytrain_file.c_str());

   string Xline;
   string Yval;

   for(int i = 0; i < rows; i++)
   {

      getline(X_file, Xline);

      getline(Y_file, Yval, ',');

      stringstream lineStream(Xline);
      string value;
      vector <int> row;

      for(int j = 0; j < cols; j++)
      {
         getline(lineStream, value,',');
         row.push_back(stoi(value));
      }

      this->Xtrain.push_back(row);
      this->Ytrain.push_back(stoi(Yval));

   }


   // cout << this->Xtrain[0].size() << endl;
   // cout << this->Xtrain.size() << endl;
   // cout << this->Ytrain.size() << endl;

}

NB_Classifier::~NB_Classifier()
{


}


void NB_Classifier::fit()
{
   // training set size
   int train_size = this->Ytrain.size();

   // number of instances per class
   int class_0 = class_count(0);
   int class_1 = class_count(1);

   // log priors
   double log_class_0_prior = log((float)class_0 / (float)train_size);
   double log_class_1_prior = log((float)class_0 / (float)train_size);

   // total vocabulary
   // int V = this->
   //   # train set size
   //   self.train_size = float(len(y))
     //
   //   # number of instances per class
   //   self.class_0, self.class_1 = np.bincount(y)
     //
   //   # log priors
   //   self.log_class_0_prior = math.log(self.class_0 / self.train_size)
   //   self.log_class_1_prior = math.log(self.class_1 / self.train_size)
     //
   //   # total vocabulary
   //   self.V = len(X[0])
     //
   //   # total tokens in each class (scalar)
   //   self.class_0_wtot = 0 + self.V*0.5 # add one-smoothing of 0.5
   //   self.class_1_wtot = 0 + self.V*0.5 # add one-smoothing
     //
   //   # total per token in each class (vector)
   //   self.class_0_vectot = np.full(len(X[0]), 0.5) # ones == add one-smoothing
   //   self.class_1_vectot = np.full(len(X[0]), 0.5)
     //
   //   self.loglike_0_vec = np.zeros(len(X[0]), dtype=np.int)
   //   self.loglike_1_vec = np.zeros(len(X[0]), dtype=np.int)
     //
   //   # sum of the total tokens
   //   for x, y in zip(X, y):
   //       if y == 0:
   //           self.class_0_wtot += np.sum(x)
   //           self.class_0_vectot += x
   //       else:
   //           self.class_1_wtot += np.sum(x)
   //           self.class_1_vectot += x
     //
   //   for i in range(self.V):
   //       self.loglike_0_vec[i] = math.log(self.class_0_vectot[i]/float(self.class_0_wtot))
   //       self.loglike_1_vec[i] = math.log(self.class_1_vectot[i]/float(self.class_1_wtot))






}



// Private Helper Functions


int NB_Classifier::class_count(int c)()
{

   int count = 0;

   for(int i = 0; i < this->Ytrain.size();i++)
      if(c ==  this->Ytrain[i])
         count++;


   return count;

}
