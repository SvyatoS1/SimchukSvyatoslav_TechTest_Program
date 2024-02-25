#include <iostream>
#include "FindFilesByName.h"

int main()
{
    std::string fileName;
    std::cout << "Please, enter the file name: ";
    std::cin >> fileName;

    std::string pathToFile = findFile(fileName);
    
    std::cout << (!pathToFile.empty() ? "File found: " + pathToFile
        : "Error: File not found") << std::endl;
    return 0;
}
