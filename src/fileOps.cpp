//
//  Author: Ewan Baxter
//

#include <iostream>
#include <fstream>

#include "../inc/fileOps.h"


namespace fileOps
{

    using namespace std;


    // Method to read from a file and store to string
    void readFromFile(const string* filePath, string* fileContents)
    {

        ifstream fin;
        string line;

        try {

            fin.open(*filePath);

            // Checking if file opened successfully
            if (!fin.fail()) {
                cout << *filePath << " was opened successfully. Reading contents..." << endl
                     << endl;

                // Looping each line in file and appending to string to save
                while (!fin.eof()) {
                    getline(fin, line);
                    *fileContents += line + "\n";
                }

                cout << "Finished reading from file." << endl << endl;

            } else {
                cout << *filePath << " was not opened successfully." << endl;
            }


        } catch (const ios_base::failure& e) {
            cout << "Something went wrong opening/reading file." << endl;
            cout << e.what() << endl;
        } catch (...) {
            cout << "There was an unknown issue opening/reading the file." << endl;
        }   // end try/catch

        fin.close();

        cout << *filePath << " was closed." << endl << endl;

    } // End readFromFile method


    // Method to write string to file
    void writeToFile(const string* filePath, const string* outMessage)
    {

        ofstream fout;

        try {

            fout.open(*filePath);

            // Checking if file opened successfully
            if (!fout.fail()) {
                cout << *filePath << " was opened successfully. Writing to file." << endl
                     << endl;

                // writing string to file
                fout << *outMessage;

                cout << "Finished writing to file." << endl << endl;

            } else {
                cout << *filePath << " was not opened successfully." << endl;
            }

        } catch (const ios_base::failure& e) {
            cout << "Something went wrong opening/writing file." << endl;
            cout << e.what() << endl;
        } catch (...) {
            cout << "There was an unknown issue opening/writing the file." << endl;
        }   // end try/catch

        fout.close();

        cout << *filePath << " was closed." << endl << endl;

    }   // end writeToFile method

};  // end namespace fileOps