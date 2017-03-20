#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include <string>

using namespace std;

class VP_Classifier {

   public:
      VP_Classifier(string , string , int , int);
      void fit(int);
      vector<int> predict(string, int);
      ~VP_Classifier();


   private:
      // Private Helper functions
      int sum(vector<int>&);
      int dot(vector<int>&, vector<int>&);
      int sign(int);

      // Global class variables
      vector< vector<int> > Xtrain;
      vector<int> Ytrain;

      vector<int> c;
      vector< vector<int> > w;

};
#endif
