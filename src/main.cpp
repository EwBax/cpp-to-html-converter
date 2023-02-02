//
//  Author: Ewan Baxter
//

#include <iostream>
#include <regex>

#include "../inc/fileOps.h"


using namespace std;


// Windows max path is 260, -1 for the invisible null character at the end
//https://learn.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation?tabs=registry
int MAX_PATH = 259;


// Prototype declarations
bool validateFilepath(string* filePath, const string* extension);
void getFilePath(string* filePath, const string extension);
string convertToHTML(const string* toConvert);


// Custom exception for invalid Windows file path
struct BadWindowsPath : public exception
{
    public:
        const string what()
        {
            return "Invalid Windows file path.";
        }
};


int main()
{

    string cppPath;
    string htmlPath;
    string fileContents;

    //intro to program
    cout << "**************************************************" << endl;
    cout << "*************.CPP TO .HTML CONVERTER**************" << endl;
    cout << "**************************************************" << endl << endl;


    cout << "Your .cpp file will be reformatted and saved in a .html file to be read in a browser." << endl << endl;
    cout << "WARNING: The contents of the .html file will be overwritten." << endl << endl;


    // getting paths for files
    getFilePath(&cppPath, ".cpp");

    cout << endl;

    getFilePath(&htmlPath, ".html");


    // calling method to read contents of .cpp file
    fileOps::readFromFile(&cppPath, &fileContents);

    // Calling method to convert to html
    fileContents = convertToHTML(&fileContents);

    // Calling method to write to file
    fileOps::writeToFile(&htmlPath, &fileContents);

    return 0;
}   // end main method


// Method to get and validate a file path
void getFilePath(string* filePath, const string extension) {

    bool validPath = false;

    do {

        //prompt user to enter full path to file
        cout
                << "Enter full path to " + extension + " file (including drive and extension i.e. C:\\folder\\file.cpp):"
                << endl;

        getline(cin, *filePath);

        // blank line for spacing in terminal
        cout << endl;

        try {

            //call method to validate the file path and loop if not valid
            if (!validateFilepath(filePath, &extension)) {
                cout << "That is not a path to a " + extension + " file." << endl << endl;
            } else {
                validPath = true;
            }
        } catch (BadWindowsPath& e) {
            cout << e.what() << endl << endl;
        }

    } while (!validPath);

}   // end getFilePath method


// Method to validate that a filePath is a valid Windows file filePath, and ends in a given extension
bool validateFilepath(string* filePath, const string* extension)
{

    // Regex from https://www.oreilly.com/library/view/regular-expressions-cookbook/9781449327453/ch08s18.html
    string windowsPathRegex = "^([a-zA-Z]:\\\\(?:[^\\\\/:*?\"<>|\r\n]+\\\\)*[^\\\\/:*?\"<>|\r\n]*)$";
    string extensionRegex = ".*\\" + *extension;

    // Checking that filePath is a valid Windows file filePath using regex and testing length
    if (!regex_match(*filePath, regex(windowsPathRegex)) || filePath->length() > MAX_PATH) {
        throw BadWindowsPath();
    }

    // checking if file filePath has valid extension
    if (regex_match(*filePath, regex(extensionRegex))) {
        return true;
    }
    else {
        return false;
    }

}   // end validateFilePath method


// Method to format .cpp file for writing to .html
string convertToHTML(const string* toConvert)
{

    // Starting converted string with <PRE> tag
    string converted = "<PRE>\n";

    // Looping and checking every character in string toConvert
    for (char c: *toConvert) {

        // Checking for < and > and replacing if they occur
        switch (c) {

            case '<':
                converted += "&lt";
                break;
            case '>':
                converted += "&gt";
                break;
            default:
                converted += c;
                break;

        }   // end switch

    }   // end for looop

    // appending </PRE> to the end of the converted string
    converted += "</PRE>";

    return converted;

}   // end convertToHTML method
