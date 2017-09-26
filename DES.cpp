#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

const short CHARS_IN_BLOCK = 8;
const short BITS_IN_CHAR = 8;
const short ROUND_COUNT = 8;

//IP Table, takes in vector of size 64, permutes it, and modifies
//left and right vectors passed by reference to give plaintext halves
void initPerm(vector<bool> inputVector, vector<bool>& leftText,
  vector<bool>& rightText)
{
  short initPerm[] = {58,50,42,34,26,18,10,2,
                      60,52,44,36,28,20,12,4,
                 62,54,46,38,30,22,14,6,
                 64,56,48,40,32,24,16,8,
                 57,49,41,33,25,17,9,1,
                 59,51,43,35,27,19,11,3,
                 61,53,45,37,29,21,13,5,
                 63,55,47,39,31,23,15,7};
  vector<bool> permVec;
  for(short i=0; i < 64; i++)
  {
    permVec.push_back(inputVector.at(initPerm[i]-1));
  }
  for (unsigned short i = 0; i < permVec.size() / 2; i++)
  {
    leftText.push_back(permVec.at(i));
  }
  for (unsigned short i = permVec.size() / 2; i < permVec.size(); i++)
  {
    rightText.push_back(permVec.at(i));
  }

}

//Inverse IP table, takes in vector of booleans of size 64 and returns
//its permutation
vector<bool> invInitPerm(vector<bool> inputVector)
{
  short invInitPerm[] = {40,8,48,16,56,24,64,32,
                       39,7,47,15,55,23,63,31,
                       38,6,46,14,54,22,62,30,
                       37,5,45,13,53,21,61,29,
                       36,4,44,12,52,20,60,28,
                       35,3,43,11,51,19,59,27,
                       34,2,42,10,50,18,58,26,
                       33,1,41,9,49,17,57,25};
  vector<bool> vec;
  for(short i=0; i < 64; i++)
  {
    vec.push_back(inputVector.at(invInitPerm[i]-1));
  }
  return vec;
}

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

//PC1 Table, takes in vector of size 64, permutes it to size 56, and modifies
//halves passed by reference to give initial key halves
void pc1Perm(vector<bool> keyBits, vector<bool>& leftKey, vector<bool>& rightKey)
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
  for(int i=0; i<pcOneSize / 2; i++)
  {
    leftKey.push_back(keyBits.at(pcOne[i]-1));
  }
  for(int i=pcOneSize / 2; i<pcOneSize; i++)
  {
    rightKey.push_back(keyBits.at(pcOne[i]-1));
  }
}

//PC2 Table, takes in key halves vectors of size 28 each, permutes them,
//and returns a combined permuted key vector
vector<bool> pc2Perm(vector<bool> leftKey, vector<bool> rightKey)
{
  vector<bool> combinedKey = leftKey;
  combinedKey.insert(combinedKey.end(), rightKey.begin(), rightKey.end());
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
    outputvector.push_back(combinedKey.at(pcTwo[i]-1));
  }
  return outputvector;
}

//S Boxes, takes in vector of the right half of the plaintext of size 48
//and returns a permuted and substituted vector of length 32
vector<bool> sBoxSub(vector<bool> rightTextI)
{
  short s1[4][16] = {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
                     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
                     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
                     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}};

  short s2[4][16] = {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
                     {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
                     {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
                     {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}};

  short s3[4][16] = {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                     {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                     {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                     {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}};

  short s4[4][16] = {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
                     {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
                     {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
                     {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}};

  short s5[4][16] = {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
                     {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
                     {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
                     {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}};

  short s6[4][16] = {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
                     {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
                     {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
                     {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}};

  short s7[4][16] = {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
                     {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
                     {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
                     {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}};

  short s8[4][16] = {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
                     {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
                     {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
                     {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};
  vector<vector<bool>> sboxes;
  vector<bool> outputvector;
  for(int i=0; i < 48;)
  {
    vector<bool> temp;
    for(int j=0; j<6; j++)
    {
      temp.push_back(rightTextI.at(i));
      i++;
    }
    sboxes.push_back(temp);
  }

  for(int j=0; j <8; j++)
  {
    string rowstring;
    string colstring;
    rowstring.append(sboxes.at(j).at(0) ? "1" : "0");
    rowstring.append(sboxes.at(j).at(5) ? "1" : "0");
    for(int i = 1; i <5; i++)
    {
      colstring.append(sboxes.at(j).at(i) ? "1" : "0");
    }
    bitset<2> row (rowstring);
    bitset<4> col (colstring);
    bitset<4> newbinary;
    if (j == 0)
    {
      newbinary= (s1[row.to_ulong()][col.to_ulong()]);
    }
    if (j == 1)
    {
      newbinary= (s2[row.to_ulong()][col.to_ulong()]);
    }
    if (j == 2)
    {
      newbinary= (s3[row.to_ulong()][col.to_ulong()]);
    }
    if (j == 3)
    {
      newbinary= (s4[row.to_ulong()][col.to_ulong()]);
    }
    if (j == 4)
    {
      newbinary= (s5[row.to_ulong()][col.to_ulong()]);
    }
    if (j == 5)
    {
      newbinary= (s6[row.to_ulong()][col.to_ulong()]);
    }
    if (j == 6)
    {
      newbinary= (s7[row.to_ulong()][col.to_ulong()]);
    }
    if (j == 7)
    {
     newbinary= (s8[row.to_ulong()][col.to_ulong()]);
    }

    for(int i=0; i<4; i++)
    {
      outputvector.push_back(newbinary[i]);
    }

  }

  return outputvector;
}

//Key shift scheduler, takes in key halves and shifts them by a specified
//number of bits based on the current round of encryption
vector<bool> leftShiftSched(vector<bool> inputVector, short round)
{
   short schedule[] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
   vector<bool> outputvector;
   for (unsigned int i= schedule[round]; i < inputVector.size(); i++ )
   {
     outputvector.push_back(inputVector.at(i));
   }
   for(int i=0; i < schedule[round]; i++)
   {
     outputvector.push_back(inputVector.at(i));
   }
   return outputvector;
}

//Takes in a size 64 vector of booleans for both plaintext and the key
//and performs DES encryption on them. Returns string of ciphertext for the
//input block of plaintext
string encrypt(vector<bool> plainTextBits, vector<bool> keyBits)
{
  string cryptText;

  vector<bool> leftTextI;
  vector<bool> rightTextI;
  vector<bool> leftKey;
  vector<bool> rightKey;
  vector<bool> leftTextIPlus1;
  vector<bool> permKey;
  initPerm(plainTextBits, leftTextI, rightTextI);
  pc1Perm(keyBits, leftKey, rightKey);

  for (short i = 0; i < ROUND_COUNT; i++)
  {
    leftTextIPlus1 = rightTextI;
    //Right text is permuted and expanded to 48 bits
    rightTextI = eTablePerm(rightTextI);
    //PC-2 Table permutation for keys, also now 48 bits
    leftKey = leftShiftSched(leftKey, i);
    rightKey = leftShiftSched(rightKey, i);
    permKey = pc2Perm(leftKey, rightKey);
    for (unsigned short j = 0; j < rightTextI.size(); j++)
    {
      //XOR each bit of the right text with the key
      rightTextI.at(j) = rightTextI.at(j)^permKey.at(j);
    }
    rightTextI = sBoxSub(rightTextI);
    rightTextI = pTablePerm(rightTextI);
    for (unsigned short j = 0; j < rightTextI.size(); j++)
    {
      //XOR each bit of the right text with the key
      rightTextI.at(j) = rightTextI.at(j)^leftTextI.at(j);
    }
    leftTextI = leftTextIPlus1;
  }
  //32-bit swap
  rightTextI.insert(rightTextI.end(), leftTextI.begin(), leftTextI.end());
  //Inverse IP Table
  rightTextI = invInitPerm(rightTextI);

  //Converting binary back into chars
  for (int i = 0; i < CHARS_IN_BLOCK; i++)
  {
    string tempString = "";
    for (int j = 0; j < BITS_IN_CHAR; j++)
    {
      tempString += (rightTextI.at((i * CHARS_IN_BLOCK) + j) ? "1" : "0");
    }
    bitset<BITS_IN_CHAR> temp(tempString);
    cryptText += static_cast<char>(bitset<BITS_IN_CHAR>(temp.to_string()).to_ulong());
  }
  cout << cryptText;
  return cryptText;
}

string decrypt(vector<bool> cipherTextBits, vector<bool> keyBits)
{
  string plainText;

  vector<bool> leftTextI;
  vector<bool> rightTextI;
  vector<bool> leftKey;
  vector<bool> rightKey;
  vector<bool> leftTextIPlus1;
  vector<bool> permKey;
  initPerm(cipherTextBits, leftTextI, rightTextI);
  pc1Perm(keyBits, leftKey, rightKey);

  for (short i = ROUND_COUNT - 1; i >= 0; i--)
  {
    vector<bool> shiftedLeftKey = leftKey;
    vector<bool> shiftedRightKey = rightKey;
    leftTextIPlus1 = rightTextI;
    //Right text is permuted and expanded to 48 bits
    rightTextI = eTablePerm(rightTextI);

    for (short j = 0; j <= i; j++)
    {
      shiftedLeftKey = leftShiftSched(shiftedLeftKey, j);
      shiftedRightKey = leftShiftSched(shiftedRightKey, j);
    }
    //PC-2 Table permutation for keys, also now 48 bits
    permKey = pc2Perm(shiftedLeftKey, shiftedRightKey);
    for (unsigned short j = 0; j < rightTextI.size(); j++)
    {
      //XOR each bit of the right text with the key
      rightTextI.at(j) = rightTextI.at(j)^permKey.at(j);
    }
    rightTextI = sBoxSub(rightTextI);
    rightTextI = pTablePerm(rightTextI);
    for (unsigned short j = 0; j < rightTextI.size(); j++)
    {
      //XOR each bit of the right text with the key
      rightTextI.at(j) = rightTextI.at(j)^leftTextI.at(j);
    }
    leftTextI = leftTextIPlus1;
  }
  //32-bit swap
  rightTextI.insert(rightTextI.end(), leftTextI.begin(), leftTextI.end());
  //Inverse IP Table
  rightTextI = invInitPerm(rightTextI);


  //Converting binary back into chars
  for (int i = 0; i < CHARS_IN_BLOCK; i++)
  {
    string tempString = "";
    for (int j = 0; j < BITS_IN_CHAR; j++)
    {
      tempString += (rightTextI.at((i * CHARS_IN_BLOCK) + j) ? "1" : "0");
    }
    bitset<BITS_IN_CHAR> temp(tempString);
    plainText += static_cast<char>(bitset<BITS_IN_CHAR>(temp.to_string()).to_ulong());
  }

  return plainText;
}

int main()
{
  cout << "Please enter \'e\' to encrypt or \'d\' to decrypt." << endl;
  char mode;
  cin >> mode;
  do
  {
    if (mode == 'e')
    {
      ifstream plainTextFileStream;
      plainTextFileStream.open("pt.txt");

      if (plainTextFileStream.is_open())
      {
        char c;
        vector<char> plainText;
        while (plainTextFileStream.get(c))
        {
          plainText.push_back(c);
        }
        plainTextFileStream.close();

        vector<char> keyVector;
        ifstream keyFileStream;
        keyFileStream.open("key.txt");
        //TODO give else statement for failed key file opening
        if (keyFileStream.is_open())
        {
          while (keyFileStream.get(c))
          {
            keyVector.push_back(c);
          }
        }

        vector<bool> keyBits;
        for (short i = 0; i < CHARS_IN_BLOCK; i++)
        {
          bitset<BITS_IN_CHAR> temp(keyVector.at(i));
          for(short j = 0; j<BITS_IN_CHAR; j++)
          {
            keyBits.push_back(temp[j]);
          }
        }

        // Pad plaintext so you have full groups of 64 bits
        short charsToPad = CHARS_IN_BLOCK - (plainText.size() % CHARS_IN_BLOCK);
        for(short i=0; i<charsToPad; i++)
        {
          plainText.push_back('x');
        }
        short charGroupCount = plainText.size()/CHARS_IN_BLOCK;
        string cipherText = "";
        for (short i = 0; i < charGroupCount; i++)
        {
          vector<bool> curCharGroup;
          for (short j = 0; j < CHARS_IN_BLOCK; j++)
          {
            bitset<BITS_IN_CHAR> temp(plainText.at((i*CHARS_IN_BLOCK)+j));
            for(short k = 0; k<BITS_IN_CHAR; k++)
            {
              curCharGroup.push_back(temp[k]);
            }
          }
          cipherText += encrypt(curCharGroup, keyBits);
        }
        // output cipher text to encryptResults.txt
        ofstream cipherTextFileStream;
        cipherTextFileStream.open("encryptResults.txt", std::ofstream::out | std::ofstream::trunc);
        // TODO: If file is open
        for(unsigned short i=0; i < cipherText.size(); i++)
        {
          cipherTextFileStream << cipherText[i];
        }
        cipherTextFileStream.close();
        // End Encryption
      }
      else
      {
        cout << "The file was not able to be opened." << endl;
        plainTextFileStream.close();
      }
      return 0;
    }
    else if (mode == 'd')
    {
      ifstream cipherTextFileStream;
      cipherTextFileStream.open("encryptResults.txt");

      if (cipherTextFileStream.is_open())
      {
        char c;
        vector<char> cipherText;
        while (cipherTextFileStream.get(c))
        {
          cipherText.push_back(c);
        }
        cipherTextFileStream.close();

        vector<char> keyVector;
        ifstream keyFileStream;
        keyFileStream.open("key.txt");
        //TODO give else statement for failed key file opening
        if (keyFileStream.is_open())
        {
          while (keyFileStream.get(c))
          {
            keyVector.push_back(c);
          }
        }

        vector<bool> keyBits;
        for (short i = 0; i < CHARS_IN_BLOCK; i++)
        {
          bitset<BITS_IN_CHAR> temp(keyVector.at(i));
          for(short j = 0; j<BITS_IN_CHAR; j++)
          {
            keyBits.push_back(temp[j]);
          }
        }

        short charGroupCount = cipherText.size()/CHARS_IN_BLOCK;
        string plainText = "";
        for (short i = 0; i < charGroupCount; i++)
        {
          vector<bool> curCharGroup;
          for (short j = 0; j < CHARS_IN_BLOCK; j++)
          {
            bitset<BITS_IN_CHAR> temp(cipherText.at((i*CHARS_IN_BLOCK)+j));
            for(short k = 0; k<BITS_IN_CHAR; k++)
            {
              curCharGroup.push_back(temp[k]);
            }
          }
          plainText += decrypt(curCharGroup, keyBits);
        }

        // output plaintext to decryptResults.txt
        ofstream plainTextFileStream;
        plainTextFileStream.open("decryptResults.txt", std::ofstream::out | std::ofstream::trunc);
        // TODO: If file is open
        for(unsigned short i=0; i < plainText.size(); i++)
        {
          plainTextFileStream << plainText[i];
        }
        plainTextFileStream.close();
        // End Encryption
      }
      else
      {
        cout << "The file was not able to be opened." << endl;
        cipherTextFileStream.close();
      }
      return 0;
    }
    // Input not e or d. Try again
    cout << "Please enter \'e\' to encrypt or \'d\' to decrypt." << endl;
    cin >> mode;
  }
  while (mode != 'e' || mode != 'd');
  return 0;
}
