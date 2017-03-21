#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fstream>
using namespace std;

void printComArray(char* arr[]) {
    for(int i = 0; arr[i] != '\0'; i++) {
        printf( "%s\n", arr[i]);
    }
}

/* This function parses the command line delineated by white space.
First it replaces white space with null characters then it saves 
the address to **sinCommand */
void  parseCom(char *comline, char **sinCommand)
{
    while (*comline != '\0') {                                    
          while (*comline == ' ' ||  *comline == '\n')
               *comline++ = '\0';     
               
          *sinCommand++ = comline;
          
          
          while (*comline != '\0' && *comline != ' ' &&  *comline != '\n') 
               comline++;             
     }
     *sinCommand = '\0';                 
}
/* Recieves a command line and integer. Forks the process into a parent and child.
Parent is told to wait while execvp() is called in the child process 
If the process fails, the integer is assigned 0*/
void  execute(char **argv, int& success)
{
     pid_t  pid;
     int status;
     int fd[2];
     
     pipe(fd);
     
     if ((pid = fork()) < 0) {    
          printf("*** ERROR: forking child failed\n");
          exit(1);
     }
     //child process
     else if (pid == 0) { 
          close(0);
          dup(fd[0]);
          if (execvp(*argv, argv) < 0) {     
               printf("*** ERROR: exec failed\n");
               exit(errno);
          }
     }
     //parent process
    waitpid(pid, &status, 0);
    if(WIFEXITED(status))
    {
        close(fd[1]);
        dup2(0, fd[0]);
        if(WEXITSTATUS(status) != 0)
        {
            success = 0;
        }
    }
}

int test(char* flag, char* path) {
    char bracket[] = "]";
    struct stat sb;
    
    if(strpbrk(path, bracket)){
        //fix: pop the bracket from path
    }
    
    // cout << "flag: " << flag << endl;
    // cout << "path: " << path << endl;
    
    if (stat(path, &sb) == -1) {
        cout << "(False)" << endl;
        return 0;
    }
    else if(!strcmp(flag, "-e")) {
        cout << "(True)" << endl;
        return 1;
    }
    else if(!strcmp(flag, "-f")){
        if(S_ISREG(sb.st_mode)){
            cout << "(True)" << endl;
            return 1;
        }
        else {
            cout << "(False)" << endl;
            return 0;
        }
    }
    else {
        if(S_ISDIR(sb.st_mode)){
            cout << "(True)" << endl;
            return 1;
        }
        else {
            cout << "(False)" << endl;
            return 0;
        }
    }
}

void printCommands(char* commandLine, char* commandLineB){
    printf("Command Line A: %s \n", commandLine);
    printf("Command Line B: %s \n", commandLineB);
    // printf("Single Command Line: %s \n\n", singleCommand);
}



int main() {
    char commandLine[1024];              //Command line input by user
    char commandLineB[1024];        //Copy of command line to make tokenizing work
    char commandLineC[1024];
    // char singleCommand[64];             //One executable and its arguments
    char *sinCommand[256];               //singleCommand but tokenized
    int success = 1;                    //used to flag whether the last command succeeded
    int dontskip = 1;
    
    //variables added for assn4
//    int i = 0;
    char paran[] = "(";
    char endparan[] = ")";
    char c;
    char* p;
    char* p2;
    char* p3;
    ofstream outFS;
    ifstream inFS;
    
    
    while(1) {
        cout << "$ ";
        std::cin.getline(commandLine, 1024);
        strcpy(commandLine, strtok(commandLine, "#"));
        success = 1;  
        dontskip = 1;
        
        while(commandLine[0] != '\0'){
            strcpy(commandLineB, commandLine);
            
            strcpy(commandLineB, strtok(commandLineB, ";|&\n"));
            
            memmove(commandLine, commandLine+strlen(commandLineB), strlen(commandLine));
            
            //***********changes for assn4********************
            
            p2 = strchr(commandLineB, '>'); 
            p3 = strchr(commandLineB, '<');
            
            if(*commandLine == '|' && commandLine[1] != '|' && !p2 && !p3)
                success = 0;
                
            if(p2){
                p2++;
                //if string contains '>>'
                if(*p2 == '>'){
                    strcpy(commandLineC, commandLineB);
                    strcpy(commandLineC, strtok(commandLineC, ">"));
                    memmove(commandLineB, commandLineB+strlen(commandLineC)+3, strlen(commandLineB));
                    outFS.open(commandLineB, ios::app);
                    if(*commandLineC == 'e'){
                        memmove(commandLineC, commandLineC+5, strlen(commandLineC));
                        strcat(commandLineC, "\n");
                        outFS << commandLineC;
                    }
                    else {
                        parseCom(commandLineC, sinCommand);
                        if(success && dontskip) 
                            execute(sinCommand, success);
                    }
                    outFS.close();
                }
                //else string contains '>'
                else {
                    strcpy(commandLineC, commandLineB);
                    strcpy(commandLineC, strtok(commandLineC, ">"));
                    memmove(commandLineB, commandLineB+strlen(commandLineC)+2, strlen(commandLineB));
                    outFS.open(commandLineB);
                    if(*commandLineC == 'e'){
                        memmove(commandLineC, commandLineC+5, strlen(commandLineC));
                        strcat(commandLineC, "\n");
                        outFS << commandLineC;
                    }
                    else {
                        parseCom(commandLineC, sinCommand);
                        if(success && dontskip) 
                            execute(sinCommand, success);
                    }
                    outFS.close();
                }
            }
            //if string contains '<'
            else if(p3) {
                strcpy(commandLineC, commandLineB);
                strcpy(commandLineC, strtok(commandLineC, "<"));
                memmove(commandLineB, commandLineB+strlen(commandLineC)+2, strlen(commandLineB));
                if(*commandLineC == 'c') {
                    inFS.open(commandLineB);
                    c = inFS.get();
                    
                    while(inFS.good()) {
                        cout << c;
                        c = inFS.get();
                    }
                    
                    inFS.close();
                }
                else {
                    parseCom(commandLineC, sinCommand);
                    if(success && dontskip) 
                        execute(sinCommand, success);
                }
            }
            
            //************end changes for assn4*********************
            //make sure you add this next else block
            
            else {
                parseCom(commandLineB, sinCommand);
                
                if(strpbrk(sinCommand[0], paran)) {
                    memmove(sinCommand[0], sinCommand[0]+1, strlen(sinCommand[0]));
                }
                
                for(int i = 0; sinCommand[i] != '\0'; i++) {
                    p = strpbrk(sinCommand[i], endparan);
                    if(p){
                        *p = '\0';
                    }
                }
                if (strcmp(sinCommand[0], "exit") == 0)  
                       exit(0); 
                      
                // if test go to our function, else execute normally
                if (strcmp(sinCommand[0], "test") == 0 || strcmp(sinCommand[0], "[") == 0)  { 
                    char flag[64];
                    char e[] = "-e";
                    strcpy(flag, sinCommand[1]); 
                    // cout << "gottem\n";
                    
                    if(strcmp(flag, "-e") == 0 || strcmp(flag, "-f") == 0|| strcmp(flag, "-d") == 0) {
                        success = test(sinCommand[1], sinCommand[2]);
                    }
                    else {
                        success = test(e, sinCommand[1]);
                    }
                    
                }
                else {
                    if(success && dontskip) 
                        execute(sinCommand, success);
                }
            }
                
            if(commandLine[0] == ';' || (commandLine[0] == '|' && commandLine[1] != '|')) {
                memmove(commandLine, commandLine+1, strlen(commandLine));
                success = 1;
                dontskip = 1;
            }
            else if(commandLine[0] == '&' && commandLine[1] == '&') {
                memmove(commandLine, commandLine+2, strlen(commandLine));
                if(!dontskip)
                    dontskip = 1;
            }
            else if(commandLine[0] == '|' && commandLine[1] == '|') {
                memmove(commandLine, commandLine+2, strlen(commandLine));
                if (success == 0){
                    success = 1;
                }
                else {
                    dontskip = 0;
                }
            }

        }
    }
}
