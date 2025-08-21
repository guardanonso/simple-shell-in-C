#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main(void){
      
    char *args[] = {"ls","-l", NULL};
    execvp("ls", args);
    perror("execvp");
    return 1;
}