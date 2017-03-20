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

      getline(Y_file, Yval);

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

NB_Classifier::~NB_Classifier() { }


int NB_Classifier::class_count(int c)
{

   int count = 0;

   for(size_t i = 0; i < this->Ytrain.size();i++)
   {
      if(c == (int)this->Ytrain[i])
      {
         count++;
         // cout << this->Ytrain[i] << endl;
      }
   }



   return count;

}

int NB_Classifier::sum(vector<int>& vec)
{
   int sum = 0;
   for(size_t i = 0; i < vec.size(); i++)
      sum += vec[i];

   return sum;

}

void NB_Classifier::sum_vector(vector<double>& vec1, vector<int>& vec2)
{

   for(size_t i = 0; i < vec1.size(); i++)
      vec1[i] += vec2[i];

}


void NB_Classifier::fit()
{
   // training set size
   int train_size = this->Ytrain.size();

   // number of instances per class
   // cout << "The size of Y labels " << this->Ytrain.size() << endl;
   // cout << "The number of zero classes in Y: " << NB_Classifier::class_count(0) << endl;
   // cout << "The number of zero classes in Y: " << NB_Classifier::class_count(1) << endl;

   int class_0 = NB_Classifier::class_count(0);
   int class_1 = NB_Classifier::class_count(1);

   // log priors
   this->log_class_0_prior = log((float)class_0 / (float)train_size);
   this->log_class_1_prior = log((float)class_1 / (float)train_size);

   // cout << "Log prior of 0: " << this->log_class_1_prior << endl;


   // total vocabulary
   int V = this->Xtrain[0].size();


   // total tokens in each class (scalar)
   double class_0_wtot = 0 + V*0.5;
   double class_1_wtot = 0 + V*0.5;


   // cout << "weight initial of 0: " <<  class_0_wtot << endl;


   // total per token in each class (vector)
   vector<double> class_0_vectot(this->Xtrain[0].size(), 0.5);
   vector<double> class_1_vectot(this->Xtrain[0].size(), 0.5);

   // loglikelihood per word per class
   this->loglike_0_vec = vector<double>(this->Xtrain[0].size(), 0.0);
   this->loglike_1_vec = vector<double>(this->Xtrain[0].size(), 0.0);

   //   # sum of the total tokens
   //   for x, y in zip(X, y):
   //       if y == 0:
   //           self.class_0_wtot += np.sum(x)
   //           self.class_0_vectot += x
   //       else:
   //           self.class_1_wtot += np.sum(x)
   //           self.class_1_vectot += x

   for(size_t i = 0; i < this->Ytrain.size(); i++)
   {
      if(this->Ytrain[i] == 0)
      {
         class_0_wtot += NB_Classifier::sum(this->Xtrain[i]);
         NB_Classifier::sum_vector(class_0_vectot, this->Xtrain[i]);

      }
      else
      {
         class_1_wtot += NB_Classifier::sum(this->Xtrain[i]);
         NB_Classifier::sum_vector(class_1_vectot, this->Xtrain[i]);

         // cout << this->Xtrain[i][1] << endl;
         // cout << class_1_vectot[1] << endl;


      }


   }


   //   for i in range(self.V):
   //       self.loglike_0_vec[i] = math.log(self.class_0_vectot[i]/float(self.class_0_wtot))
   //       self.loglike_1_vec[i] = math.log(self.class_1_vectot[i]/float(self.class_1_wtot))

   for(int i = 0; i < V; i++)
   {
      this->loglike_0_vec[i] = log(class_0_vectot[i]/(float)class_0_wtot);
      this->loglike_1_vec[i] = log(class_1_vectot[i]/(float)class_1_wtot);

   }


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


vector<int> NB_Classifier::predict(string X_predict, int rows)
{

   // read in the test file
   // vector< vector<int> > X_test;

   ifstream X_file(X_predict.c_str());

   string Xline;


   // prediction vector
   vector<int> preds;
   double sum_0 = this->log_class_0_prior;
   double sum_1 = this->log_class_1_prior;



   for(int i = 0; i < rows; i++)
   {

      getline(X_file, Xline);

      stringstream lineStream(Xline);
      string value;
      // vector <int> row;

      for(size_t j = 0; j < this->Xtrain[0].size(); j++)
      {
         getline(lineStream, value,',');
         int val = stoi(value);

         if(val != 0)
         {
            sum_0 += this->loglike_0_vec[i]*(float)val;
            sum_1 += this->loglike_1_vec[i]*(float)val;
         }


         // row.push_back(stoi(value));
      }

      // cout << sum_0 << endl;
      if(sum_0 > sum_1)
      {
         preds.push_back(0);
      }
      else
      {

         preds.push_back(1);

      }

      sum_0 = this->log_class_0_prior;
      sum_1 = this->log_class_1_prior;


      // X_test.push_back(row);

   }

   // output the prediction accuracy
   int count = 0;

   for(size_t i = 0; i < preds.size(); i++)
      if(preds[i] == Ytrain[i])
         count++;

   cout << "Prediction accuracy is: " << (float)count/(float)Ytrain.size();
   cout << endl;


   return preds;




   // preds = []
   //  sum_0 = self.log_class_0_prior
   //  sum_1 = self.log_class_1_prior
   //
   //  for i, x in enumerate(X):
   //       for idx, val in enumerate(x):
   //           if val != 0:
   //               sum_0 += (self.loglike_0_vec[idx]*val)
   //               sum_1 += (self.loglike_1_vec[idx]*val)
   //
   //
   //       preds.append(np.argmax([sum_0, sum_1]))
   //       sum_0 = self.log_class_0_prior
   //       sum_1 = self.log_class_1_prior
   //
   //  return preds




}


// Private Helper Functions
