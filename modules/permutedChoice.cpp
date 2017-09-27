#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

vector<bool> permutedChoiceOne(vector<bool> inputVector)
{
  short pcOneSize = 56;
  short pcOne[]= {57,49,41,33,25,17,9,
              1,58,50,42,34,26,18,
              10,2,59,51,43,35,27,
              19,11,3,60,52,44,36,
              63,55,47,39,31,23,15,
              7,62,54,46,38,30,22,
              14,6,61,53,45,37,29,
              21,13,5,28,20,12,4};
   vector<bool> outputvector;
   for(int i=0; i<pcOneSize; i++)
   {
     outputvector.push_back(inputVector.at(pcOne[i]-1));
   }
   return outputvector;
}

vector<bool> permutedChoiceTwo(vector<bool> inputVector)
{
  short pcTwoSize = 48;
  short pcTwo[]= {14,17,11,24,1,5,3,28,
                  15,6,21,10,23,19,12,4,
                  26,8,16,7,27,20,13,2,
                  41,52,31,37,47,55,30,40,
                  51,45,33,48,44,49,39,56,
                  34,53,46,42,50,36,29,32};
   vector<bool> outputvector;
   for(int i=0; i<pcTwoSize; i++)
   {
     outputvector.push_back(inputVector.at(pcTwo[i]-1));
   }
   return outputvector;
}

int main()
{
 cout << "Hello, world!" << endl;
 bitset<64> bs (15);
 cout << bs << endl;
 vector<bool> bitsetvec;
 for(int i=0; i < 64; i++)
 {
   bitsetvec.push_back(bs[i]);
 }

 vector<bool> pcOneVector = permutedChoiceOne(bitsetvec);
  cout << "Permuted Choice One: " << endl;
  for(int i=0; i < pcOneVector.size(); i++){
   cout << pcOneVector.at(i);
  }
  cout << endl;
  vector<bool> pcTwoVector = permutedChoiceTwo(bitsetvec);
   cout << "Permuted Choice Two: " << endl;
   for(int i=0; i < pcTwoVector.size(); i++){
    cout << pcTwoVector.at(i);
   }


 return 0;
}
