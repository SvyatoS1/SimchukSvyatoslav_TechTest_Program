#ifndef FIND_FILE_BY_NAME
#define FIND_FILE_BY_NAME

#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>
#include <stack>

using namespace std::filesystem;

void makeList(std::stack <std::string> & list,
 path currentPath,
 path & fileDirectory,
 std::string & fileName);

void findFileInDir(path dirPath, path & fileDirectory,
 std::string & fileName);
 
std::string findFile(std::string & fileName);

#endif