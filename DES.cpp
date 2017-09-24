#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


int main()
{

    cout << "Please enter \'e\' to encrypt or \'d\' to decrypt." << endl;
    char mode;
    cin >> mode;
    do {
        if (mode == 'e'){
            ifstream plainTextFileStream;
            plainTextFileStream.open("pt.txt");

            string output;
            if (plainTextFileStream.is_open()) {
                char c;
                vector<char> plainText;
                while (plainTextFileStream.get(c)) {
                    plainText.push_back(c);
                    ofstream cipherTextFileStream;
                    cipherTextFileStream.open("ct.txt", std::ofstream::out | std::ofstream::trunc);
                    for(int i=0; i < plainText.size(); i++){
                        cipherTextFileStream << plainText[i];
                    }
                    cipherTextFileStream.close();
                }
                plainTextFileStream.close();
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
