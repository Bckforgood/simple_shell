#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"
#define BUFFER_SIZE 1024

void display_prompt() {
    char prompt[] = "#cisfun$ ";
    write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
}

int execute_command(char *line) {
    pid_t pid;
    
    pid = fork();
    
    if (pid == -1) {
        perror("fork");
        return -1;
    }
    
    if (pid == 0) {
        char **args = malloc(sizeof(char *) * 2);
        args[0] = line;
        args[1] = NULL;
        
        execve(line, args, NULL);
        perror("execve");
        exit(1);
    } else {
        int status;
        wait(&status);
    }
    
    return 0;
}

int main() {
    char line[BUFFER_SIZE];
    int status = 0;
    
    while (1) {
        display_prompt();
        
        if (fgets(line, sizeof(line), stdin) == NULL) {
            char goodbye[] = "Goodbye!\n";
            write(STDOUT_FILENO, goodbye, sizeof(goodbye) - 1);
            break;
        }
        
        line[strcspn(line, "\n")] = '\0';
        
        if (execute_command(line) == -1) {
            break;
        }
    }
    
    return status;
}

