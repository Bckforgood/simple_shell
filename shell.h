#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define BUFSIZE 10240

extern char **environ;

int _putchar(char c);
int _strcmp(char *s1, char *s2);
int shell(char **argv);
int Path(char **env, char **argv);
<<<<<<< HEAD
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strdup(char *src);
char *_memcpy(char *dest, char *src, unsigned int n);
int _puts(char *c);
int _strlen(char *c);
char *_getline();
void hashtag(char *buffer);
int _atoi(char *s);
/*int exitShell(char *argv[], char *line);*/
void exitShell(__attribute__((unused)) char **argv, char *line);
=======
char *_strcpy(char *d, char *s);
char *_strcat(char *d, char *s);
char *_strdup(char *s);
char *_memcpy(char *d, char *s, unsigned int n);
int check_cmd(char **argv, char **env);
int main(__attribute__((unused)) int ac,
		__attribute__((unused)) char **av, char **env);

char *find_command(char *command);
void exit_shell(char **argv);



>>>>>>> ac33349d1cac31b2f53e5063bd2929bd9b7d4520
#endif
