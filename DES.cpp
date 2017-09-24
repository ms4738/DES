#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


void encrypt(vector<bool> L, vector<bool> R, vector<bool> keyL, vector<bool> keyR)
{
    const int roundCount = 8;

    // Take in PT, Key, four half vectors passed by reference
    initialPermute()

    // TODO: append CT to a holder variable
    // return CT for each block
}

int main()
{

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
                if (keyFileStream.is_open()) {
                    while (keyFileStream.get(c)) {
                        keyVector.push_back(c);
                    }
                }

                vector<bool> keyBitsL;
                vector<bool> keyBitsR;
                for (int i = 0; i < 4; i++) {
                    bitset<8> temp(keyVector.at(i));
                    for(int j = 0; j<8; j++){
                      keyBitsL.push_back(temp[j]);
                    }
                }
                for (int i = 4; i < 8; i++) {
                    bitset<8> temp(keyVector.at(i));
                    for(int j = 0; j<8; j++){
                      keyBitsR.push_back(temp[j]);
                    }
                }

                // TODO: replace 8s?
                // Pad plaintext so you have full groups of 64 bits
                int charsToPad = 8 - (plainText.size() % 8);
                for(int i=0; i<charsToPad; i++){
                    plainText.push_back('x');
                }
                int charGroupCount = plainText.size()/8;

                for (int i = 0; i < charGroupCount; i++) {
                    vector<bool> Li;
                    for (int j = 0; j < 4; j++) {
                        bitset<8> temp(plainText.at((i*8)+j));
                        for(int k = 0; k<8; k++){
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
                for(int i=0; i < plainText.size(); i++){
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
