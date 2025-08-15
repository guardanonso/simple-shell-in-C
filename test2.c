#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main(void){
      
    char *args[] = {"man","ls", NULL};
    execvp("man", args);
    perror("execvp");
    return 1;
}