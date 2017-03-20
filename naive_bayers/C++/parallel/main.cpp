#include "model.h"
#include <iostream>
#include <string>

using namespace std;


int main(int argc, char * argv[]) {

   string Xtrain ("../../data/Xtrain.csv");
   string Ytrain ("../../data/Ytrain.csv");

   // initialize model with training file
   NB_Classifier model = NB_Classifier(Xtrain, Ytrain, 500, 41567);
   model.fit();

   // return predictions
   vector<int> x = model.predict(Xtrain, 500);


   // output predictions
   // for(int i = 0; i < x.size(); i++)
   //    cout << x[i] << endl;


   return 0;
}
