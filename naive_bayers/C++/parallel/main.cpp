#include "model.h"
#include <iostream>
#include <string>
#include <ctime>



using namespace std;


int main(int argc, char * argv[]) {

   int rows = 500;
   string Xtrain = "../../../data/Xtrain.csv";
   string Ytrain = "../../../data/Ytrain.csv";


   if(argc > 1)
   {
      cout << argc << endl;
      rows = stoi(argv[3]);
      Xtrain = argv[1];
      Ytrain = argv[2];
   }

   clock_t begin = clock();


   // initialize model with training file
   NB_Classifier model = NB_Classifier(Xtrain, Ytrain, rows, 41567);

   clock_t end = clock();
   double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

   cout << "Time to read data: " << elapsed_secs << endl;


   begin = clock();

   model.fit();

   end = clock();
   elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

   cout << "Time to train model: " << elapsed_secs << endl;

   // begin = clock();
   // // return predictions
   // vector<int> x = model.predict(Xtrain, rows);
   //
   // end = clock();
   // elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
   //
   // cout << "Time to train predict: " << elapsed_secs << endl;


   // output predictions
   // for(int i = 0; i < x.size(); i++)
   //    cout << x[i] << endl;


   return 0;
}
