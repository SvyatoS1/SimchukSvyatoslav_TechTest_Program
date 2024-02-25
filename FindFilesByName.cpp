#include <iostream>
#include <filesystem>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

#include"FindFilesByName.h"

using namespace std::filesystem;

std::mutex mtx;
std::condition_variable cv;
static int activeThreads = 0;

std::string findFile(std::string & fileName)
{
  path rootDirectory = "/";
  path fileDirectory = "";
  std::stack <std::string> rootList;

  makeList(rootList, rootDirectory, fileDirectory, fileName);
 
  std::vector <std::thread> threads;

  for (; !rootList.empty() && fileDirectory.empty(); rootList.pop())
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]{ return activeThreads < 8; });
        threads.emplace_back(std::thread(findFileInDir, rootList.top(), std::ref(fileDirectory), std::ref(fileName)));
    }
  for (auto& thread : threads)
      thread.join();

  return fileDirectory.string();
}

void makeList(std::stack <std::string> & list, path currentPath, path & fileDirectory, std::string & fileName)
{
  try
  {
    for (const auto& entry : directory_iterator(currentPath))
    {
      path dir = entry.path();
      entry.is_directory() ? list.push(entry.path().string()) : (void)(
        entry.path().filename() == fileName ? (fileDirectory = entry.path(), void()) : void());
    }
  }
  catch (const filesystem_error& e) {std::cerr << "Error while accessing directory: "<< std::endl;}
}

void findFileInDir(path dirPath, path & fileDirectory, std::string & fileName)
{
  std::stack <std::string> dirList;
  makeList(dirList, dirPath, fileDirectory, fileName);
  for (; !dirList.empty() && fileDirectory.empty(); )
    {
        findFileInDir(dirList.top(), fileDirectory, fileName);
        dirList.pop();
    }
  activeThreads--;
  cv.notify_one();
}
