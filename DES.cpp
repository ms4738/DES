#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main()
{

    cout << "Please enter \'e\' to encrypt or \'d\' to decrypt." << endl;
    char mode;
    cin >> mode;
    do {
        if (mode == 'e'){
            // string plainTextFileName = "pt.txt";
            // cout << "trying to open " << plainTextFileName << endl;
            ifstream plainTextFileStream;
            plainTextFileStream.open("pt.txt");

            string output;
            if (plainTextFileStream.is_open()) {
                // cout << plainTextFileName << "File is open" << endl;
                while (!plainTextFileStream.eof()) {
                    plainTextFileStream >> output;
                    cout << output;
                    // TODO: Open Output File
                }
            }
            else {
                cout << "The file was not able to be opened." << endl;
            }
            plainTextFileStream.close();
            break;
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
