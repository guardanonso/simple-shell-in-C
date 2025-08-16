#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUF_INCREMENT 3

char** safeRealloc(char** buffer, int size){
    char** temp_buff = realloc(buffer, size);
    if(temp_buff == NULL){
        free(buffer); // we can free memory because we used a temp buffer to try reallicating
        printf("reallocation error\n");
        return NULL; 
    }
    return temp_buff;
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
char** function(){
    char** buffer = malloc(10*sizeof(char*));

    char* str1 = "first string";
    char* str2 = "second   string";
    
    buffer[0] = str1;
    // buffer[1] = str2;

    return buffer;
}
char** inputParser(char* input){
    int counter = 0;
    char** buffer;
    char str[strlen(input)+1];
    strcpy(str, input);

    char* token = strtok(str, " ");

    while (token != NULL){
        if(counter == 0){
            buffer = malloc(1 * sizeof(char*));
        }
        else{
            buffer = safeRealloc(buffer, (counter + 1) * sizeof(char*));
        }
        buffer[counter] = strdup(token);
        counter++;
        token = strtok(NULL, " ");
    }
    return buffer;
}
int main(){
    char* buffer = get_input();
    char** strAr = inputParser(buffer);

    // char** buf = function();
    // printf("%s\n", buf[0]);
}