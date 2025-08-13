#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define buffsize 100

void safe_gets(char* buffer, int size) {
    char c;
    if(fgets(buffer, size, stdin) != NULL){
        if(buffer[strlen(buffer)-1] != '\n'){
            while( (c = getchar()) != '\n'){
                // svuota input buffer
            }
        }
        else{
            buffer[strlen(buffer)-1] = '\0';
        }
    }
}

int main(void){
    char buffer[buffsize];
    safe_gets(buffer, buffsize);
    char command1[20];
    char command2[20];

    char* token1 = strtok(buffer, " ");
    char* token2 = strtok(NULL, " ");

    if(token1 != NULL){
        strcpy(command1, token1);
    }else command1[0] = '\0';
    if(token2 != NULL){
        strcpy(command2, token2);
    }else command2[0] = '\0';
    
}