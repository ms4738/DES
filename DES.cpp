#include<iostream>
#include<fstream>
#include <string>
using namespace std;


int main()
{
    // TODO: make if statement for Encryption/Decryption
    cout << "Please enter a file containing plain text: " << endl;
    string input;
    cin >> input;
    cout << "Your file name was:" << endl << input << endl;

    ifstream plainTextFileStream;
    plainTextFileStream.open (input);
    string output;
    cout << "trying to open " << input << endl;
    if (plainTextFileStream.is_open()) {
        cout << input << "  File is open" << endl;
        while (!plainTextFileStream.eof()) {
            plainTextFileStream >> output;
            cout<<output;
            ofstream output ("ciphertext.txt");
            if (myfile.is_open()){
                myfile << "This is a line.\n";
                myfile << "This is another line.\n";
                myfile.close();
            }
            else cout << "Unable to open file";
        }
    }
    plainTextFileStream.close();
    return 0;
}
