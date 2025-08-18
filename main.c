#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUF_INCREMENT 3

char* get_input(void){
    int bufsize = BUF_INCREMENT;
    char c;
    char* buffer = (char*)malloc(sizeof(char)*bufsize);
    int position = 0;
    
    while (1) {
        // Read a character from the stdin buffer
        c = getchar();

        // If we hit EOF or a new-line character, replace it with a '\0' character and return
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        }else {
            buffer[position] = c;  // otherwise we just add c to the buffer
        }
        position++;

        // If we have exceeded the buffer (position >= bufsize), we try reallocating memory
        if (position >= bufsize){
            bufsize += BUF_INCREMENT;             // incrementing bufsize 
            char *temp_buffer = realloc(buffer, bufsize);           // safely reallicating using a temporary buffer
            if (temp_buffer == NULL) {
                free(buffer);                   // we are able to free memory now
                printf("reallocation error occured\n");
                exit(EXIT_FAILURE); 
            }
            buffer = temp_buffer;     // realloc worked!
        }
    }
}

char* parser(void){
    
}

int main(void){
    char* buffer = get_input();
    
    char arg1[20];
    char arg2[20];

    char* token1 = strtok(buffer, " ");
    char* token2 = strtok(NULL, " ");

    if(token1 != NULL){
        strcpy(arg1, token1);
    }else arg1[0] = '\0';
    if(token2 != NULL){
        strcpy(arg2, token2);
    }else arg2[0] = '\0';
    
}