#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUF_INCREMENT 3

int countWords(char* string){
    int counter = 0;
    char s[strlen(string) + 1];
    strcpy(s, string);
    
    char* token = strtok(s, " ");
    while(token!=NULL){
        counter++;
        token = strtok(NULL, " ");
    }
    return counter;
}

char** safeMalloc(int size){
    char** tmp_buff = malloc(size * sizeof(char *));
    if(tmp_buff == NULL){
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return tmp_buff;
}

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

        // If we have exceeded the buffer (position >= bufsize), we try reallocating
        if (position >= bufsize){
            bufsize += BUF_INCREMENT; // incrementing bufsize 
            char *temp_buffer = realloc(buffer, bufsize); // using e temporary buffer so that we dont lose reference to the previously allocated memory pointed by buffer, in case reallocation doesnt go well and NULL is returned
            if (!temp_buffer) {
                free(buffer); // we can free memory because we used a temp buffer to try reallicating
                printf("reallocation error\n");
                return NULL; 
            }
            // If realloc works, we write temp_buffer onto buffer
            buffer = temp_buffer;
        }
    }
}

/* parses user input and stores it in a dinamically allocated array of strings terminating with a NULL value */
char** inputParser(char* input){ 
    char str[strlen(input)+1];
    strcpy(str, input);
    int words = countWords(str);
    
    if(words == 0){   // no input, function only returns NULL
        return NULL;
    }

    char** buffer = safeMalloc(words + 1);  // calling safeMalloc() to allocate enough memory to store the whole array
    char* token = strtok(str, " ");

    int index = 0; 
    while(token!=NULL){             // actual parsing cycle using strtok() and allocating the string using the index var
        buffer[index] = strdup(token);
        index++;
        token = strtok(NULL, " ");
    }
    buffer[index] = NULL;      // adding NULL terminator at the end of the array
    return buffer;
}
int main(){
    char* buffer = get_input();
    char** argsArr = inputParser(buffer);
    if(argsArr!=NULL){
        for(int i = 0; argsArr[i] != NULL; i++){
            printf("%s\n", argsArr[i]);
        }
    }   
}