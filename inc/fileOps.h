//
//  Author: Ewan Baxter
//

#ifndef PROG2100_ASSIGNMENT_1_FILEOPS_H
#define PROG2100_ASSIGNMENT_1_FILEOPS_H

#include <string>

namespace fileOps
{

    void readFromFile(const std::string* filePath, std::string* fileContents);

    void writeToFile(const std::string* filePath, const std::string* outMessage);

};


#endif //PROG2100_ASSIGNMENT_1_FILEOPS_H
