#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUF_INCREMENT 3 

/* idk */
void run(const char* command, char* argsArr[]){
    pid_t pid = fork();
    if(pid == 0){
        // calling the execvp() system call
        int status_code = execvp(command, argsArr);
        if (status_code == -1) {
            printf("Process did not terminate correctly\n");
            exit(1);
        }
    }
    wait(NULL);
}

/* utility function to count words in user input */
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

/* Just a malloc() wrapper to safely use malloc() */
char** safeMalloc(int size){
    char** tmp_buff = malloc(size * sizeof(char *));
    if(tmp_buff == NULL){
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return tmp_buff;
}

/* safely reads standard input and returns it as string */
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


void freeMemory(char** buffer){
    for(int i = 0; buffer[i] != NULL; i++){
        free(buffer[i]);
    }
}

int main(){
    while(1){
        char* user_input = get_input();
        char** argsArr = inputParser(user_input);
        char* command = argsArr[0];
        run(command, argsArr);
        free(user_input);
        freeMemory(argsArr);
    }
}