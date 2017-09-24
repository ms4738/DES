#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

vector<bool> initperm(vector<bool> inputVector)
{
  int initperm[] = {58,50,42,34,26,18,10,2,
                 60,52,44,36,28,20,12,4,
                 62,54,46,38,30,22,14,6,
                 64,56,48,40,32,24,16,8,
                 57,49,41,33,25,17,9,1,
                 59,51,43,35,27,19,11,3,
                 61,53,45,37,29,21,13,5,
                 63,55,47,39,31,23,15,7};
  vector<bool> vec;
  for(int i=0; i < 64; i++)
  {
    vec.push_back(inputVector.at(initperm[i]-1));
  }
  return vec;
}

vector<bool> invinitperm(vector<bool> inputVector)
{
  int invinitperm[] = {40,8,48,16,56,24,64,32,
                 39,7,47,15,55,23,63,31,
                 38,6,46,14,54,22,62,30,
                 37,5,45,13,53,21,61,29,
                 36,4,44,12,52,20,60,28,
                 35,3,43,11,51,19,59,27,
                 34,2,42,10,50,18,58,26,
                 33,1,41,9,49,17,57,25};
  vector<bool> vec;
  for(int i=0; i < 64; i++)
  {
    vec.push_back(inputVector.at(invinitperm[i]-1));
  }
  return vec;
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
 vector<bool> initialPermutaion = initperm(bitsetvec);
 vector<bool> inverseInitPermutaion = invinitperm(bitsetvec);
 cout << "InitPermutaion" << endl;
 for(int i=0; i < 64; i++){
   cout << initialPermutaion.at(i);
  }
 cout << endl << "inverseInitPermutaion" << endl;
 for(int i=0; i<64; i++){
   cout << inverseInitPermutaion.at(i);
 }

 return 0;
}
