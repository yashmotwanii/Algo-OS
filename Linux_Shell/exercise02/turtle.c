#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <time.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64



void exec(char **token)
{
    int i = 0;
    int fork_val = fork();
    if (fork_val != 0) {
        int i;
        waitpid(fork_val, &i, WUNTRACED);
    } else {
        execvp(token[0], token);
        printf("Incorrect command format \n");
        exit(0);
    }
}
 



void cd(char** token)
{	
        if (token[1] == NULL)
    {
        printf("Pass one argument\n");
        return;
    }
    
    if (token[2] != NULL)
    {
        printf("Incorrect number of Arguments passed\n");
        return;
    }

    char si[MAX_INPUT_SIZE];
   //If there exist no directory
    if (chdir(token[1]) < 0)
        printf("Directory  does not exist\n");
    getcwd(si,MAX_INPUT_SIZE);printf("%s\n", si);
}


void sigintHandler(int sig_num)
{
    signal(SIGINT, sigintHandler);
    printf("\n Program can't be terminated by SIGINT \n");
    fflush(stdout);        
}


char **tokenize(char *line)
{
    char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
    char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
    int i, tokenIndex = 0, tokenNo = 0;

    for (i = 0; i < strlen(line); i++) {

        char readChar = line[i];

        if (readChar == ' ' || readChar == '\n' || readChar == '\t') {
            token[tokenIndex] = '\0';
            if (tokenIndex != 0) {
                tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE * sizeof(char));
                strcpy(tokens[tokenNo++], token);
                tokenIndex = 0;
            }
        }
        else {
            token[tokenIndex++] = readChar;
        }
    }

    free(token);
    tokens[tokenNo] = NULL ;
    return tokens;
}





void main(void)
{
    char  line[MAX_INPUT_SIZE];
    char  **tokens;
    int i;
    char buffer[1024];
    while (1) {

        printf("Hello>");
        bzero(line, MAX_INPUT_SIZE);
        gets(line);
        printf("Got command %s\n", line);
        line[strlen(line)] = '\n'; //terminate with new line
        
        
        
        char* next_line = strtok (line, ";");
        while (1)
        {
            int i = 0;
            int STDIN = dup(0), STDOUT = dup(1);
            bool output = 0, done = 0;
            strcpy(buffer, next_line);
            tokens = tokenize(buffer);
            while (tokens[i++] != NULL)
            {
                if (strcmp(tokens[i - 1], ">") == 0)
                {
                    done = 1;
                    output = 1;
                }
                else if (output)
                {
  
                    done = 1;
                    output = 1;
                    int output1;
                    if (done)
                        output1 = open(tokens[i - 1], O_CREAT | O_WRONLY | O_TRUNC,0644);
                    if (tokens[i - 1] == NULL) {
                        printf("Incorrect file Specified");
                        break;
                    tokens[i - 1] = NULL;
                    tokens[i - 2] = NULL;
                    dup2(output1, 1);
                    output = 0;
                    
                    
                }
            }
            
            
            
            //do whatever you want with the commands, here we just print them
            if (strcmp(tokens[0], "cd") == 0)
            {
                cd(tokens);
            } else {
                exec(tokens);
            }
            dup2(STDIN, 0);
            dup2(STDOUT, 1);
            // Freeing the allocated memory
            for (i = 0; tokens[i] != NULL; i++) {
                free(tokens[i]);
            }
            free(tokens);
            next_line = strtok (next_line + strlen (next_line) + 1, ";");
            if (next_line == NULL)
                break;

        }
    }
}

