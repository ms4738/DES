#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>
using namespace std;

//Takes in 28 bit vecotor and returns 28 bit vector
vector<bool> leftShiftSched(short round, vector<bool> inputVector)
{
   short schedule[] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
   vector<bool> outputvector;
   for (int i= schedule[round-1]; i < inputVector.size(); i++ )
   {
     outputvector.push_back(inputVector.at(i));
   }
   for(int i=0; i < schedule[round-1]; i++)
   {
     outputvector.push_back(inputVector.at(i));
   }
   return outputvector;
}

int main()
{
 cout << "Hello, world!" << endl;
 bitset<28> bs (15);
 vector<bool> bitsetvec;
 for(int i=0; i < 28; i++)
 {
   bitsetvec.push_back(bs[i]);
   cout << bitsetvec.at(i);
 }
 cout << endl;
 int n =1;
 vector<bool> shiftedVec = leftShiftSched(n, bitsetvec);
 cout << "Shifted Vector Round " << n << endl;
 for(int i=0; i < shiftedVec.size(); i++)
 {
   cout << shiftedVec.at(i);
 }

 /*vector<bool> pcOneVector = permutedChoiceOne(bitsetvec);
  cout << "Permuted Choice One: " << endl;
  for(int i=0; i < pcOneVector.size(); i++){
   cout << pcOneVector.at(i);
  }
  cout << endl;
  vector<bool> pcTwoVector = permutedChoiceTwo(bitsetvec);
   cout << "Permuted Choice Two: " << endl;
   for(int i=0; i < pcTwoVector.size(); i++){
    cout << pcTwoVector.at(i);
   }*/


 return 0;
}
