#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include <string>

using namespace std;

class NB_Classifier {

   public:
      NB_Classifier(string , string , int , int);
      void fit();
      void predict(string);
      ~NB_Classifier();

   private:
      // Private Helper functions
      int class_count(int c);


      // Global class variables
      vector< vector<int> > Xtrain;
      vector<int> Ytrain;

};
#endif
