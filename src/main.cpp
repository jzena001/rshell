#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
using namespace std;
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
     
     if ((pid = fork()) < 0) {    
          printf("*** ERROR: forking child failed\n");
          exit(1);
     }
     //child process
     else if (pid == 0) { 
          if (execvp(*argv, argv) < 0) {     
               printf("*** ERROR: exec failed\n");
               exit(errno);
          }
     }
     //parent process
    waitpid(pid, &status, 0);
    if(WIFEXITED(status))
    {
        if(WEXITSTATUS(status) != 0)
        {
            success = 0;
        }
    }
}

int main() {
    char commandLine[256];              //Command line input by user
    char commandLineBackUp[256];        //Copy of command line to make tokenizing work
    char singleCommand[64];             //One executable and its arguments
    char *sinCommand[64];               //singleCommand but tokenized
    int success = 1;                    //used to flag whether the last command succeeded
    
//    char* executable;
    
    while(1) {
        cout << "$ ";
        std::cin.getline(commandLine, 256);
        strcpy(commandLine, strtok(commandLine, "#"));
        success = 1;
        
        while(commandLine[0] != '\0'){
            
            strcpy(commandLineBackUp, commandLine);
            
            strcpy(singleCommand, strtok(commandLineBackUp, ";|&\n"));
            
            memmove(commandLine, commandLine+strlen(commandLineBackUp), strlen(commandLine));
           
            parseCom(commandLineBackUp, sinCommand);
            
            if (strcmp(sinCommand[0], "exit") == 0)  
                   exit(0); 
                   
            if(success) 
                execute(sinCommand, success);
                
            if(commandLine[0] == ';') {
                memmove(commandLine, commandLine+2, strlen(commandLine));
                success = 1;
            }
            else if(commandLine[0] == '&' && commandLine[1] == '&') {
                memmove(commandLine, commandLine+3, strlen(commandLine));
            }
            else if(commandLine[0] == '|' && commandLine[1] == '|') {
                memmove(commandLine, commandLine+3, strlen(commandLine));
                if (success == 1) 
                    success = 0;
                else 
                    success = 1;
            }

        }
    }
}
