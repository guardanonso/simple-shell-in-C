#include <stdio.h>
#include <unistd.h>

int main() {
    char* argument_list[] = {"ls", "-l", NULL}; // NULL terminated array of char* strings

    // Ok! Will execute the command "ls -l"
    execvp("ls", argument_list);
    
}