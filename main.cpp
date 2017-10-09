
#include <iostream>
#include <mycommands.h>

#include <fstream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <vector>

#include <stdio.h>   
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include<iostream>

using namespace std;
mycommands mc;

// Main program entry point
int main(int argc, char *argv[], char** envp) {
    string command_line;
    while ( true ) {
        getline(cin, command_line);
        
        string spaces = " ";
        size_t pos = 0;
        string token;
        
        pos = command_line.find(spaces);
        token = command_line.substr(0, pos);
        command_line.erase(0, pos + spaces.length() );
        
        cout << token << endl;
        cout << command_line << endl;
        
        if(command_line == "exit"){
            exit(0);
        }
        if(command_line == "clear"){
            system("CLS");
        }
        if(token == "cp"){
            string oldfile, newfile;
            if(command_line.find(spaces ) >= 0){
                size_t pos2 = command_line.find(spaces);
                oldfile = command_line.substr(0, pos2);
                newfile = command_line.erase(0, pos2 + spaces.length());
            }
            cout << "Oldfile:  " << oldfile << endl;
            cout << "Newfile:  " << newfile << endl;
            mc.mycommands::cp(oldfile, newfile);
        }
        if(token == "cat"){
            cout << "Command Line: " << command_line << endl;
            mc.mycommands::cat(command_line);
        }
        if(token == "grep"){
            string searchtext, filenames;
            size_t pos2 = command_line.find(spaces);
            searchtext = command_line.substr(0, pos2);
            filenames = command_line.erase(0, pos2 + spaces.length());
            cout << "Searchtext:  " << searchtext << endl;
            cout << "Filenames:  " << filenames << endl;
            mc.mycommands::grep(searchtext, filenames);
        }
        if(command_line == "ls" || token == "ls"){
            mc.mycommands::ls();
        }
        if(token == "cd"){
            cout << "Command Line: " << command_line << endl;
            mc.mycommands::cd(command_line);
        }
        if(token == "mkdir"){
            cout << "Command Line: " << command_line << endl;
            mc.mycommands::mkdir(command_line);
        }
        if(token == "rmdir"){
            cout << "Command Line: " << command_line << endl;
            mc.mycommands::rmdir(command_line);
        }
        if(token == "sleep"){
            cout << "Sleep Time: " << command_line << endl;
            mc.mycommands::sleep(atoi(command_line.c_str()));
        }
        if(token == "kill"){
            int signum = atoi(command_line.c_str());
            pid_t pidt = GetCurrentProcessId();
            cout << "Signal number: " << signum << endl;
            mc.mycommands::killer(signum, pidt);
        }
        if(token == "diff"){
            string file1, file2;
            if(command_line.find(spaces ) >= 0){
                size_t pos2 = command_line.find(spaces);
                file1 = command_line.substr(0, pos2);
                file2 = command_line.erase(0, pos2 + spaces.length());
            }
            cout << "File1:  " << file1 << endl;
            cout << "File2:  " << file2 << endl;
            mc.mycommands::diff(file1, file2);
        }
        if(token == "env"){
            char** env;
            for (env = envp; *env != 0; env++){
                char* thisEnv = *env;
                printf("%s\n", thisEnv);    
            }
            mc.mycommands::env();
        }
        if(token == "wait"){
            
            cout << "Process ID:  " << command_line << endl;
            mc.mycommands::wait(GetCurrentProcessId(command_line));
        }
        if(token == "timeout"){
            int seconds;
            string command;
            if(command_line.find(spaces ) >= 0){
                size_t pos2 = command_line.find(spaces);
                seconds = atoi(command_line.substr(0, pos2).c_str());
                command = command_line.erase(0, pos2 + spaces.length());
            }
            cout << "Seconds: " << seconds << endl;
            cout << "Command: " << command << endl;  
            mc.mycommands::timeout(seconds, command);
            
        }
    }
}
