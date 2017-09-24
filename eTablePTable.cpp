#include <iostream>
#include <bitset>
#include<vector>
using namespace std;

//Takes in a vector of size 32, expands and permutes it with a hard-coded table,
//and returns a vector of size 48
vector<bool> eTablePerm(vector<bool> inputVector)
{
  short outputVectorSize = 48;
  short eTable[outputVectorSize] = {32, 1,  2,  3,  4,  5,
                                    4,  5,  6,  7,  8,  9,
                                    8,  9,  10, 11, 12, 13,
                                    12, 13, 14, 15, 16, 17,
                                    16, 17, 18, 19, 20, 21,
                                    20, 21, 22, 23, 24, 25,
                                    24, 25, 26, 27, 28, 29,
                                    28, 29, 30, 31, 32, 1};
  vector<bool> outputVector;

  for (short i = 0; i < outputVectorSize; i++)
  {
    outputVector.push_back(inputVector.at(eTable[i] - 1));
  }
  return outputVector;
}

//Takes in vector of size 32, permutes it using a hard-coded table,
//and returns another vector of size 32
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
    outputVector.push_back(inputVector.at(pTable[i] - 1));
  }
  return outputVector;
}


int main()
{
  //Vector for testing
  vector<bool> testVect;
  for (int i = 0; i < 32; i++)
  {
    if (i < 16)
    {
      testVect.push_back(0);
    }
    else
    {
      testVect.push_back(1);
    }
    //testVect.push_back(i % 2);
  }

  vector<bool> test2 = eTablePerm(testVect);
  vector<bool> test3 = pTablePerm(test2);
  cout << "Hello, world!" << endl;
  return 0;
}
