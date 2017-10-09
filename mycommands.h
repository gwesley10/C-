#ifndef MYCOMMANDS_H
#define MYCOMMANDS_H

#include <string>
#include <iostream>

#include <fstream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

class mycommands
{
public:
    void ls();
    void grep(std::string searchtext, std::string filenames);
    void cp(std::string oldfile, std::string newfile);
    void cat(std::string file);
    void mkdir(std::string dirName);
    void rmdir(std::string dirName);
    void stat(std::string filename);
    void sleep(int sleepTime);
    void killer(int signum, pid_t processId);
    void diff(std::string file1, std::string file2);
    void env();
    void timeout(int seconds, std::string command);
    void wait(int processId);
    void cd(std::string pattern);
};

#endif // MYCOMMANDS_H
