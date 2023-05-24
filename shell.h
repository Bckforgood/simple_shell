#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;
int main(void);
int _putchar(char c);
int _strcmp(char *s1, char *s2);
int shell(char **argv);
int Path(char **env, char **argv);
char *_strcpy(char *d, char *s);
char *_strcat(char *d, char *s);
char *_strdup(char *s);
char *_memcpy(char *d, char *s, unsigned int n);
int check_cmd(char **argv, char **env);
int mainw(__attribute__((unused)) int ac,
		__attribute__((unused)) char **av, char **env);
#endif
