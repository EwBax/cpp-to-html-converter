#include <iostream>
#include <regex>

#include "fileOps.h"

using namespace std;


// Windows max path is 260, -1 for the invisible null character at the end
//https://learn.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation?tabs=registry
int MAX_PATH = 259;

bool validateFilepath(string path, const string* extension);

void getFilePath(string* cppPath, const string extension);

int main()
{

    string cppPath;
    string htmlPath;

    //intro to program
    cout << "**************************************************" << endl;
    cout << "**************.CPP TO HTML CONVERTER**************" << endl;
    cout << "**************************************************" << endl << endl << endl;


    // getting paths for files
    getFilePath(&cppPath, ".cpp");

    cout << endl;

    getFilePath(&htmlPath, ".html");


    //TODO call method to open .cpp file

    //TODO call method to read contents of file and save to String

    //TODO call method to search and replace in String < to &lt > to &gt

    //TODO call method to write String to file, appending <PRE> to start and </PRE> to end


    //REGEX FOR LATER ^(?=([a-z]:\\(?:[^\\\/:*?"<>|\r\n]+\\)*[^\\\/:*?"<>|\r\n]*)).{1,254}\.html$ (OR .cpp)
    https://www.oreilly.com/library/view/regular-expressions-cookbook/9781449327453/ch08s18.html

    return 0;
}


// Method to get and validate a file path
void getFilePath(string* cppPath, const string extension) {

    bool validPath = false;

    do {

        //prompt user to enter full path to file
        cout
                << "Enter full path to " + extension + " file (including drive and extension i.e. C:\\folder\\file.cpp):"
                << endl;
        cin >> *cppPath;

        //call method to validate the file path and loop if not valid
        if (!validateFilepath(*cppPath, &extension)) {
            cout << "That is not a valid path to a " + extension + " file." << endl << endl;
        } else {
            validPath = true;
        }

    } while (!validPath);
}


// Method to validate that a path is a valid Windows file path, and ends in a given extension
bool validateFilepath(string path, const string* extension)
{

    const int maxPath = MAX_PATH - extension->length();


    std::string pathRegex = "^(?=([a-zA-Z]:\\\\(?:[^\\\\/:*?\"<>|\r\n]+\\\\)*[^\\\\/:*?\"<>|\r\n]*)).{1," + std::to_string(maxPath) + "}\\" + *extension + "$";

    // checking if file path matches regex for valid path
    if (regex_match(path, regex(pathRegex))) {
        return true;
    }
    else {
        return false;
    }


}
