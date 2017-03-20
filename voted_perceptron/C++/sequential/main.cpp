#include "model.h"
#include <iostream>
#include <string>

using namespace std;


int main(int argc, char * argv[]) {

   string Xtrain ("../../../data/Xtrain.csv");
   string Ytrain ("../../../data/Ytrain.csv");

   // initialize model with training file
   VP_Classifier model = VP_Classifier(Xtrain, Ytrain, 500, 41567);
   model.fit(10);

   // return predictions
   // vector<int> x = model.predict(Xtrain, 500);


   // output predictions
   // for(int i = 0; i < x.size(); i++)
   //    cout << x[i] << endl;


   return 0;
}
