#include "mycommands.h"
#include <iostream>

#include <fstream>

#include <sys/types.h>
#include <signal.h>

#include <tchar.h>
#include <sys/param.h>
#include <stdlib.h>
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
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>  
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include <iostream>
#include <windows.h>


using namespace std;


void mycommands::ls(){
    
    DIR*     dir;
    dirent*  pdir;
    
    char buff[FILENAME_MAX];
    GetCurrentDir( buff, FILENAME_MAX );
    std::string cwd(buff);
    dir = opendir(cwd.c_str());     

    vector<string> files = vector<string>();
    while (pdir = readdir(dir)) 
    {
        files.push_back(string(pdir->d_name));
    }
    closedir(dir);
    for (unsigned int i = 0;i < files.size();i++) {
        cout << files[i] << endl;
    }
}

void mycommands::grep(std::string searchtext, std::string filenames)
{
    if(filenames.substr(0,1) == "*"){
        DIR*     dir;
        dirent*  pdir;
        
        char buff[FILENAME_MAX];
        GetCurrentDir( buff, FILENAME_MAX );
        std::string cwd(buff);
        dir = opendir(cwd.c_str());     

        vector<string> filesInDir = vector<string>();
        while (pdir = readdir(dir)) 
        {
            filesInDir.push_back(string(pdir->d_name));             //grep Grant ready.txt same.txt  test.txt
        }
        closedir(dir);
        vector<string> textFilesInDir = vector<string>();
        for(int i = 0; i < filesInDir.size(); i++){
            if(filesInDir[i].find(".txt")){
                textFilesInDir.push_back(filesInDir[i]);
            }
        }
        for(int i = 0; i < textFilesInDir.size(); i++){
            string content;
            fstream tempfile;
            tempfile.open(textFilesInDir[i].c_str(),ios_base::out | ios_base::in);
            if(tempfile.is_open()){
                while(getline(tempfile, content)){
                    if(content.find(searchtext) != string::npos){
                        cout << textFilesInDir[i] << "   " << content << endl;
                    }
                }
                tempfile.close();
            }
        }
    }else{
        string spaces = " ";
        vector<string> filesholder; // holds all filenames entries including spaces
        vector<string> realvector;  // holds all filenames entries  without the spaces
        while(filenames.find(spaces) != string::npos ){   //seperates all entries by spaces
            string temp;
            size_t pos2 = filenames.find(spaces);
            temp = filenames.substr(0, pos2);
            filenames.erase(0, pos2 + spaces.length());
            filesholder.push_back(temp);
        }
        filesholder.push_back(filenames);
        for (unsigned int i = 0; i < filesholder.size(); i++) { //culls spaces from list
            if(filesholder[i] != ""){
                realvector.push_back(filesholder[i]);
            }
        }
        DIR*     dir;
        dirent*  pdir;
        
        char buff[FILENAME_MAX];
        GetCurrentDir( buff, FILENAME_MAX );
        std::string cwd(buff);
        dir = opendir(cwd.c_str());     

        vector<string> filesInDir = vector<string>();
        while (pdir = readdir(dir)) 
        {
            filesInDir.push_back(string(pdir->d_name));             //grep Grant ready.txt same.txt  test.txt
        }
        closedir(dir);
        vector<string> equivalent = vector<string>();
        for(int i = 0; i < realvector.size(); i++){             //checking that the files listed are in the directory   
            for(int j = 0; j < filesInDir.size(); j++){
                if(realvector[i] == filesInDir[j]){
                    equivalent.push_back(realvector[i]);
                }
            }
        }

        for (unsigned int i = 0; i < equivalent.size(); i++) {
            string content;
            fstream tempfile;
            tempfile.open(equivalent[i].c_str(),ios_base::out | ios_base::in);
            if(tempfile.is_open()){
                while(getline(tempfile, content)){
                    if(content.find(searchtext) != string::npos){
                        cout << equivalent[i] << "   " << content << endl;
                    }
                }
                tempfile.close();
            }
        }
    }
}


void mycommands::cat(std::string file){
    if(file.find(" ") != string::npos ){
        string outputFile;
        string spaces = " ";
        vector<string> filesholder; // holds all filenames entries including spaces
        vector<string> realvector;  // holds all filenames entries  without the spaces
        while(file.find(spaces) != string::npos ){   //seperates all entries by spaces
            string temp;
            size_t pos2 = file.find(spaces);
            temp = file.substr(0, pos2);
            file.erase(0, pos2 + spaces.length());
            filesholder.push_back(temp);
        }
        outputFile.append(file);
        for (unsigned int i = 0; i < filesholder.size(); i++) { //culls spaces from list
            if(filesholder[i] != ""){
                realvector.push_back(filesholder[i]);
            }
        }
        string filecheck;
        int check = 0;
        DIR*     dir;
        dirent*  pdir;
        
        char buff[FILENAME_MAX];
        GetCurrentDir( buff, FILENAME_MAX );
        std::string cwd(buff);
        dir = opendir(cwd.c_str());     

        vector<string> files = vector<string>();
        while (pdir = readdir(dir)) 
        {
            files.push_back(string(pdir->d_name));
        }
        closedir(dir);
        for (unsigned int i = 0;i < files.size();i++) {
            if(files[i] == outputFile){
                filecheck = files[i];
                check = 1;
                break;
            }
        }
        if(check == 1){
            remove(filecheck.c_str());
        }
        ofstream writeFile(outputFile.c_str());
        for(int i = 0; i < realvector.size(); i++){
            string content;
            
            ifstream readFile(realvector[i].c_str());
            if (writeFile.is_open() && readFile.is_open()){
                while(getline(readFile, content)){
                    writeFile << content << endl;
                }
                
                readFile.close();
            }    
        }
        writeFile.close();
        
    }else{
        string filecheck;
        int check = 0;
        DIR*     dir;
        dirent*  pdir;
        
        char buff[FILENAME_MAX];
        GetCurrentDir( buff, FILENAME_MAX );
        std::string cwd(buff);
        dir = opendir(cwd.c_str());     

        vector<string> files = vector<string>();
        while (pdir = readdir(dir)) 
        {
            files.push_back(string(pdir->d_name));
        }
        closedir(dir);
        
        for (unsigned int i = 0;i < files.size();i++) {
            if(files[i] == file){
                filecheck = files[i];
                check = 1;
                break;
            }
        }
        
        if(check == 0){
            cout << "cat: " << file <<" No such file or directory" << endl;
        }else{
            string content;
            fstream grantFile;
            grantFile.open(file.c_str(), ios_base::out | ios_base::in);
            if(grantFile.is_open()){
                while(getline(grantFile, content)){
                    cout << content << endl;
                }
                grantFile.close();
            }
        }
    }
}

void mycommands::cp(std::string oldfile, std::string newfile){
    
    string filecheck;
    int check = 0;
    DIR*     dir;
    dirent*  pdir;
    
    char buff[FILENAME_MAX];
    GetCurrentDir( buff, FILENAME_MAX );
    std::string cwd(buff);
    dir = opendir(cwd.c_str());     

    vector<string> files = vector<string>();
    while (pdir = readdir(dir)) 
    {
        files.push_back(string(pdir->d_name));
    }
    closedir(dir);
    for (unsigned int i = 0;i < files.size();i++) {
        if(files[i] == newfile){
            filecheck = files[i];
            check = 1;
            break;
        }
    }
    if(check == 1){
        remove(filecheck.c_str());
    }
    string content;
    ofstream writeFile(newfile.c_str());
    ifstream readFile(oldfile.c_str());
    if (writeFile.is_open() && readFile.is_open()){
        while(getline(readFile, content)){
            writeFile << content << endl;
        }
        writeFile.close();
        readFile.close();
    }    
}

void mycommands::mkdir(string dirName){
        _mkdir(dirName.c_str());
}

void mycommands::rmdir(string dirName){
    DIR* dir; 
    dirent*  pdir;
    char buff[FILENAME_MAX];
    GetCurrentDir( buff, FILENAME_MAX );
    std::string cwd(buff);
    cout << "Path cwd   " << cwd << endl; 
    string fullpath = cwd + "\\" + dirName;
    dir = opendir(dirName.c_str());
    vector<string> files = vector<string>();
    while (pdir = readdir(dir)) {
        files.push_back(string(pdir->d_name));
    }
    closedir(dir);
    cout << "Fullpath   " << fullpath << endl;
    remove(fullpath.c_str());
    bool status=DeleteFile(fullpath.c_str());
    if(status==true)
    {
        cout<<"file "<<dirName<<" deleted successfully..!!\n";
    }
    else
    {
        cout<<"Unable to delete file "<<dirName<<"\n";
        perror("Error Message ");
    }
    //getch();
}

void mycommands::stat(string filename){
    //struct stat buf;  
    //stat(filename, &buf);
    //int statchmod = buf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
    //printf("chmod: %o\n", statchmod);
}

void mycommands::sleep(int sleepTime){
    cout << sleepTime << " seconds" << endl;
    Sleep(sleepTime*1000);
}

void mycommands::killer(int signum, pid_t processId){
    int killed = kill(processId, signum);
}

void mycommands::diff(string file1, string file2){
    string content1;
    string content2;
    fstream readFile1;
    fstream readFile2;
    vector<string> listItems1 = vector<string>();
    vector<string> listItems2 = vector<string>();
    readFile1.open(file1.c_str(), ios_base::out | ios_base::in);
    if(readFile1.is_open()){
        while(getline(readFile1, content1)){
            listItems1.push_back(content1);
        }
        readFile1.close();
    }
    readFile2.open(file2.c_str(), ios_base::out | ios_base::in);
    if(readFile2.is_open()){
        while(getline(readFile2, content2)){
            listItems2.push_back(content2);
        }
        readFile2.close();
    }
    
        cout << "listitems1 " << listItems1.size() << endl;
    
        cout << "listitems2 " << listItems2.size() << endl;
    
    vector<int> booleanValues1 = vector<int>();
    vector<int> booleanValues2 = vector<int>();
    for(int i =0; i < listItems1.size(); i++){
        booleanValues1.push_back(-1);
    }
    for(int i =0; i < listItems2.size(); i++){
        booleanValues2.push_back(-1);
    }
    for(int i = 0; i < listItems1.size(); i++){
        for(int j = 0; j < listItems2.size(); j++){
            if(listItems1[i] == listItems2[j]){
                booleanValues1[i] = j;
                booleanValues2[j] = i;
            }
        }
    }
    vector<int> lineNums1 = vector<int>();
    vector<int> lineNums2 = vector<int>();
    
    for(int i = 0; i < booleanValues1.size(); i++){
        if(booleanValues1[i] == -1){
            lineNums1.push_back(i+1);
            cout << "< " << listItems1[i] << endl;         // diff file1.txt file2.txt
        }
    }
    cout << "---" << endl;
    for(int i = 0; i < booleanValues2.size(); i++){
        if(booleanValues2[i] == -1){
            lineNums2.push_back(i+1);
            cout << "> " << listItems2[i] << endl;
        }
    }
    for(int i = 0; i < lineNums1.size(); i++){
        if(i!=0){cout << ",";}
        cout << lineNums1[i];
    }
    cout << "c";
    for(int i = 0; i < lineNums2.size(); i++){
        if(i!=0){cout << ",";}
        cout << lineNums2[i];
    }
    cout << endl;
}

void mycommands::env(){
    
}

void mycommands::timeout(int seconds, string command){
    sleep(seconds);
    
        string spaces = " ";
        size_t pos = 0;
        string token;
        
        pos = command.find(spaces);
        token = command.substr(0, pos);
        command.erase(0, pos + spaces.length() );
        
        cout << token << endl;
        cout << command << endl;
        
        if(command == "exit"){
            exit(0);
        }
        if(command == "clear"){
            system("CLS");
        }
        if(token == "cp"){
            string oldfile, newfile;
            if(command.find(spaces ) >= 0){
                size_t pos2 = command.find(spaces);
                oldfile = command.substr(0, pos2);
                newfile = command.erase(0, pos2 + spaces.length());
            }
            cout << "Oldfile:  " << oldfile << endl;
            cout << "Newfile:  " << newfile << endl;
            mc.mycommands::cp(oldfile, newfile);
        }
        if(token == "cat"){
            cout << "Command Line: " << command << endl;
            mc.mycommands::cat(command);
        }
        if(token == "grep"){
            string searchtext, filenames;
            size_t pos2 = command.find(spaces);
            searchtext = command.substr(0, pos2);
            filenames = command.erase(0, pos2 + spaces.length());
            cout << "Searchtext:  " << searchtext << endl;
            cout << "Filenames:  " << filenames << endl;
            mc.mycommands::grep(searchtext, filenames);
        }
        if(command == "ls" || token == "ls"){
            mc.mycommands::ls();
        }
        if(token == "cd"){
            cout << "Command Line: " << command << endl;
            mc.mycommands::cd(command);
        }
        if(token == "mkdir"){
            cout << "Command Line: " << command << endl;
            mc.mycommands::mkdir(command);
        }
        if(token == "rmdir"){
            cout << "Command Line: " << command << endl;
            mc.mycommands::rmdir(command);
        }
        if(token == "sleep"){
            cout << "Sleep Time: " << command << endl;
            mc.mycommands::sleep(atoi(command.c_str()));
        }
        if(token == "kill"){
            cout << "Sleep Time: " << command << endl;
            //mc.mycommands::sleep(command_line,);
        }
        if(token == "diff"){
            string file1, file2;
            if(command.find(spaces ) >= 0){
                size_t pos2 = command.find(spaces);
                file1 = command.substr(0, pos2);
                file2 = command.erase(0, pos2 + spaces.length());
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
            
            cout << "Process ID:  " << command << endl;
            //mc.mycommands::wait(_getpid(command_line));
        }
}

void mycommands::wait(int processId){
    m_event =  CreateEvent(NULL, false, false, NULL);
    m_thread = _beginthread(StaticThreadEntry, 0, this);
    SetEvent(m_event);
    WaitForSingleObject(m_thread, INFINITE);
}

void mycommands::cd(string pattern){
    if(pattern == "/"){ // root dir '/'
        chdir(pattern.c_str());
        DIR* dir; 
        dirent*  pdir;
        char buff[FILENAME_MAX];
        GetCurrentDir( buff, FILENAME_MAX );
        std::string cwd(buff);
        cout << "Path cwd   " << cwd << endl;
        
    }else if(pattern == "~"){ //home dir /Users/<username> ///////////////////////////////
        const char *homedir;
        homedir = getenv("$HOME");
        cout << "Path cwd   " << homedir << endl;
    }else if(pattern == ".."){ //move to parent dir
        DIR* dir; 
        dirent*  pdir;
        char buff[FILENAME_MAX];
        GetCurrentDir( buff, FILENAME_MAX );
        std::string cwd(buff);
        cout << "Path cwd   " << cwd << endl;
        int location = cwd.rfind("\\");
        string newPath = cwd.erase(location, cwd.length());
        chdir(newPath.c_str());
        GetCurrentDir( buff, FILENAME_MAX );
        std::string newwd(buff);
        cout << "Path newwd   " << newwd << endl;
        
    }else if(pattern.substr(0,1) == "/"){ //change dir using absolute path
        chdir(pattern.c_str());
        DIR* dir; 
        dirent*  pdir;
        char buff[FILENAME_MAX];
        GetCurrentDir( buff, FILENAME_MAX );
        std::string cwd(buff);
        cout << "Path cwd   " << cwd << endl;
    }else if(pattern.substr(0,1) == "."){ //change dir using relative path ////////////////////
        chdir(pattern.c_str());
        DIR* dir; 
        dirent*  pdir;
        char buff[FILENAME_MAX];
        GetCurrentDir( buff, FILENAME_MAX );
        std::string cwd(buff);
        cout << "Path cwd   " << cwd << endl;
    }else{ //sub directory
        string newPath;
        DIR* dir; 
        dirent*  pdir;
        char buff[FILENAME_MAX];
        GetCurrentDir( buff, FILENAME_MAX );
        std::string cwd(buff);
        newPath=cwd+"\\"+pattern;
        chdir(newPath.c_str());
        GetCurrentDir( buff, FILENAME_MAX );
        std::string newwd(buff);
        cout << "Path newwd   " << newwd << endl;
    }
}

