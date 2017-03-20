#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include <string>

using namespace std;

class NB_Classifier {

   public:
      NB_Classifier(string , string , int , int);
      void fit();
      vector<int> predict(string, int);
      ~NB_Classifier();


   private:
      // Private Helper functions
      int class_count(int c);
      int sum(vector<int>&);
      void sum_vector(vector<double>&, vector<int>&);

      // Global class variables
      vector< vector<int> > Xtrain;
      vector<int> Ytrain;

      int ** Xtrain_arr;
      int *Ytrain_arr;

      vector<double> loglike_0_vec;
      vector<double> loglike_1_vec;

      double log_class_0_prior;
      double log_class_1_prior;

};
#endif
