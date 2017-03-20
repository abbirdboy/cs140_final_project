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
      if(stoi(Yval) == 0)
      {
         this->Ytrain.push_back(-1);

      }
      else
      {

         this->Ytrain.push_back(1);

      }


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
            vector<int> r = VP_Classifier::add(this->w[k], VP_Classifier::scalar_mult(this->Xtrain[j], this->Ytrain[j]));
            // this->w.push_back()
            this->w.push_back(r);
            this->c.push_back(1);
            k += 1;

         }

      }



   }



}


vector<int> VP_Classifier::predict(string X_predict, int rows)
{


   int y_hat = 0;
   // read in the test file
   // vector< vector<int> > X_test;

   ifstream X_file(X_predict.c_str());
   string Xline;


   // prediction vector
   vector<int> preds;


   for(int i = 0; i < rows; i++)
   {

      getline(X_file, Xline);

      stringstream lineStream(Xline);
      string value;
      vector <int> row;

      for(int j = 0; j < this->Xtrain[0].size(); j++)
      {
         getline(lineStream, value,',');
         row.push_back(stoi(value));
      }

      for(int i = 0; i < this->c.size(); i++)
      {
         y_hat += this->c[i] * VP_Classifier::sign(VP_Classifier::dot(this->w[i], row));

         if(VP_Classifier::sign(y_hat) == -1)
         {
            preds.push_back(0);

         }
         else
         {
            preds.push_back(1);

         }

         y_hat = 0;

      }


      // X_test.push_back(row);

   }




   return preds;





}










vector<int> VP_Classifier::scalar_mult(vector<int>vec, int s)
{
   for(int i = 0; i < vec.size(); i++)
      vec[i] *= s;

   return vec;

}


vector<int> VP_Classifier::add(vector<int> vec1, vector<int> vec2)
{

   vector<int> resultVec = vector<int>(vec1.size(), 0);


   for(int i = 0; i < vec1.size(); i++)
      resultVec[i] = vec1[i] + vec2[i];


   return resultVec;

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
