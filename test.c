#include <stdio.h>
#include <unistd.h>

int main() {
    char* argument_list[] = {"mkdir", "./ciao", NULL}; // NULL terminated array of char* strings

    // Ok! Will execute the command "ls -l"
    execvp("mkdir", argument_list);

    printf("ciao\n");
    
}