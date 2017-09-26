#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

vector<bool> initPerm(vector<bool> inputVector)
{
  short initPerm[] = {58,50,42,34,26,18,10,2,
                 60,52,44,36,28,20,12,4,
                 62,54,46,38,30,22,14,6,
                 64,56,48,40,32,24,16,8,
                 57,49,41,33,25,17,9,1,
                 59,51,43,35,27,19,11,3,
                 61,53,45,37,29,21,13,5,
                 63,55,47,39,31,23,15,7};
  vector<bool> vec;
  for(short i=0; i < 64; i++)
  {
    vec.push_back(inputVector.at(initPerm[i]-1));
  }
  return vec;
}

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

void encrypt(vector<bool> L, vector<bool> R, vector<bool> keyL, vector<bool> keyR)
{
    const short roundCount = 8;

    // Take in PT, Key, four half vectors passed by reference
    //initialPermute()

    // TODO: append CT to a holder variable
    // return CT for each block
}

int main()
{
  const short charsInBlock = 8;
  const short bitsInChar = 8;

    cout << "Please enter \'e\' to encrypt or \'d\' to decrypt." << endl;
    char mode;
    cin >> mode;
    do {
        if (mode == 'e'){
            ifstream plainTextFileStream;
            plainTextFileStream.open("pt.txt");

            if (plainTextFileStream.is_open()) {
                char c;
                vector<char> plainText;
                while (plainTextFileStream.get(c)) {
                    plainText.push_back(c);
                }
                plainTextFileStream.close();

                vector<char> keyVector;
                ifstream keyFileStream;
                keyFileStream.open("key.txt");
                //TODO give else statement for failed key file opening
                if (keyFileStream.is_open()) {
                    while (keyFileStream.get(c)) {
                        keyVector.push_back(c);
                    }
                }

                vector<bool> keyBitsL;
                vector<bool> keyBitsR;
                for (short i = 0; i < charsInBlock / 2; i++) {
                    bitset<8> temp(keyVector.at(i));
                    for(short j = 0; j<bitsInChar; j++){
                      keyBitsL.push_back(temp[j]);
                    }
                }
                for (short i = charsInBlock / 2; i < charsInBlock; i++) {
                    bitset<8> temp(keyVector.at(i));
                    for(short j = 0; j<bitsInChar; j++){
                      keyBitsR.push_back(temp[j]);
                    }
                }

                // TODO: replace 8s?
                // Pad plaintext so you have full groups of 64 bits
                short charsToPad = 8 - (plainText.size() % 8);
                for(short i=0; i<charsToPad; i++){
                    plainText.push_back('x');
                }
                short charGroupCount = plainText.size()/8;

                for (short i = 0; i < charGroupCount; i++) {
                    vector<bool> Li;
                    for (short j = 0; j < 4; j++) {
                        bitset<8> temp(plainText.at((i*8)+j));
                        for(short k = 0; k<8; k++){
                            Li.push_back(temp[k]);
                        }
                    }
                    vector<bool> Ri;
                    for (int j = 4; j < 8; j++) {
                        bitset<8> temp(plainText.at((i*8)+j));
                        for(int k = 0; k<8; k++){
                            Ri.push_back(temp[k]);
                        }
                    }

                    encrypt(Li, Ri, keyBitsL, keyBitsR);
                }

                // output cipher text to ct.txt
                ofstream cipherTextFileStream;
                cipherTextFileStream.open("ct.txt", std::ofstream::out | std::ofstream::trunc);
                // TODO: If file is open
                for(unsigned short i=0; i < plainText.size(); i++){
                    cipherTextFileStream << plainText[i];
                }
                cipherTextFileStream.close();
                // End Encryption
            }
            else {
                cout << "The file was not able to be opened." << endl;
                plainTextFileStream.close();
            }
            return 0;
        }
        else if (mode == 'd'){
            // TODO: fill in
        }
        // Input not e or d. Try again
        cout << "Please enter \'e\' to encrypt or \'d\' to decrypt." << endl;
        cin >> mode;
    } while (mode != 'e' || mode != 'd');
    return 0;
}
