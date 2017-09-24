#include <iostream>
#include <bitset>
#include<vector>
using namespace std;

vector<bool> eTablePerm(vector<bool> inputVector)
{
  short outputVectorSize = 48;
  short eTable[outputVectorSize] = {32, 1,  2,  3,  4,  5,
                                    4,  5,  6,  7,  8,  9,
                                    12, 13, 14, 15, 16, 17,
                                    16, 17, 18, 19, 20, 21,
                                    20, 21, 22, 23, 24, 25,
                                    24, 25, 26, 27, 28, 29,
                                    28, 29, 30, 31, 32, 1};
  vector<bool> outputVector;

  for (short i = 0; i < outputVectorSize; i++)
  {
    outputVector.push_back(inputVector.at(eTable[i]));
  }
  return outputVector;
}

vector<bool> pTablePerm(vector<bool> inputVector)
{
  short outputVectorSize = 32;
  short pTable[outputVectorSize] = {16, 7,  20, 21, 29, 12, 28, 17,
                                    1,  15, 23, 26, 5,  18, 31, 10,
                                    2,  8,  24, 14, 32, 27, 3,  9,
                                    19, 13, 30, 6,  22, 11, 4,  25};
  vector<bool> outputVector;
  for (short i = 0; i < outputVectorSize; i++)
  {
    outputVector.push_back(inputVector.at(pTable[i]));
  }
  return outputVector;
}


int main()
{
  cout << "Hello, world!" << endl;
  return 0;
}
