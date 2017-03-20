#include "model.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>


// Constructor: Loads Xtrain and Ytrain files
VP_Classifier::VP_Classifier(string Xtrain_file, string Ytrain_file, int rows, int cols)
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

VP_Classifier::~VP_Classifier() { }


void VP_Classifier::fit(int e = 10)
{
   int k = 0;
   int y_hat = 0;

   this->c = vector<int>(1, 0);
   this->w.push_back(vector<int>(this->Xtrain[0].size(), 0));

   for(int i = 0; i < e; i++)
   {
      for(int j = 0; j < this->Xtrain.size(); j++)
      {

         y_hat = VP_Classifier::sign(VP_Classifier::dot(this->Xtrain[j], this->w[k]));

         if(y_hat == this->Ytrain[j])
         {
            this->c[k] += 1;
         }
         else
         {
            // this->w.push_back()


         }

      }



   }



}


vector<int> VP_Classifier::predict(string X_predict, int rows)
{


   // preds = []
   //   y_hat = 0
   //
   //   for x_test in X:
   //       for i in range(len(self.c)):
   //           y_hat += self.c[i] * np.sign(np.dot(self.w[i], x_test))
   //
   //       if int(np.sign(y_hat)) == -1:
   //           preds.append(0)
   //       else:
   //           preds.append(1)
   //       y_hat = 0
   //
   //   return preds

   // read in the test file
   // vector< vector<int> > X_test;

   ifstream X_file(X_predict.c_str());

   string Xline;


   // prediction vector
   vector<int> preds;
   // double sum_0 = this->log_class_0_prior;
   // double sum_1 = this->log_class_1_prior;
   //
   //
   //
   // for(int i = 0; i < rows; i++)
   // {
   //
   //    getline(X_file, Xline);
   //
   //    stringstream lineStream(Xline);
   //    string value;
   //    // vector <int> row;
   //
   //    for(int j = 0; j < this->Xtrain[0].size(); j++)
   //    {
   //       getline(lineStream, value,',');
   //       int val = stoi(value);
   //
   //       if(val != 0)
   //       {
   //          sum_0 += this->loglike_0_vec[i]*(float)val;
   //          sum_1 += this->loglike_1_vec[i]*(float)val;
   //       }
   //
   //
   //       // row.push_back(stoi(value));
   //    }
   //
   //    // cout << sum_0 << endl;
   //    if(sum_0 > sum_1)
   //    {
   //       preds.push_back(0);
   //    }
   //    else
   //    {
   //
   //       preds.push_back(1);
   //
   //    }
   //
   //    sum_0 = this->log_class_0_prior;
   //    sum_1 = this->log_class_1_prior;
   //
   //
   //    // X_test.push_back(row);
   //
   // }
   //



   return preds;





}














int VP_Classifier::sum(vector<int>& vec)
{
   int sum = 0;
   for(int i = 0; i < vec.size(); i++)
      sum += vec[i];

   return sum;

}

int VP_Classifier::sign(int v)
{

   if(v > 0)
   {
      return 1;

   }
   else if(v == 0)
   {

      return 0;

   }
   else
   {
      return -1;

   }



}


int VP_Classifier::dot(vector<int>& vec1, vector<int>& vec2)
{
   int value = 0;
   for(int i = 0; i < vec1.size(); i++)
      value += vec1[i] * vec2[i];

   return value;
}




// Private Helper Functions
