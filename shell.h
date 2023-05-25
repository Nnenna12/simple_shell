#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

#define END_OF_FILE -2
#define EXIT -3
extern char **environ;



/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;


/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **fnt);
} builtin_t;


/**
 * struct al_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @val: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct al_s
{
	char *name;
	char *val;
	struct al_s *next;
} al_t;

al_t *als;

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lnptr(char **lnptr, size_t *n, char *buff, size_t b);
ssize_t _getline(char **lnptr, size_t *n, FILE *stm);
int _strlen(const char *c);
char *_strcpy(char *ds, const char *sc);
char *_strcat(char *ds, const char *sc);
char *_strncat(char *ds, const char *sc, size_t m);
char *_strchr(char *str, char c);
int _strspn(char *str, char *accept);
int _strcmp(char *str1, char *str2);
int _strncmp(const char *str1, const char *str2, size_t m);
char *get_arg(char *ln, int *exec_ret);
int call_arg(char **args, char **fnt, int *exec_ret);
int run_arg(char **args, char **fnt, int *exec_ret);
int handle_arg(int *exec_ret);
int check_arg(char **args);
int wont_open(char *file_pth);
int file_commands(char *file_path, int *exe_ret);
void handle_line(char **ln, ssize_t r);
ssize_t get_new_wen(char *ln);
void logical_ops(char *ln, ssize_t *new_wen);
void free_arg(char **args, char **fnt);
char *get_pid(void);
al_t *add_al_end(al_t **head, char *name, char *val);
void free_al_list(al_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);
char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);

int shel_al(char **args, char __attribute__((__unused__)) **fnt);
void set_al(char *var_name, char *val);
void print_al(al_t *al);
int shel_exit(char **args, char **fnt);
int shel_cd(char **args, char __attribute__((__unused__)) **fnt);
int shel_help(char **args, char __attribute__((__unused__)) **front);
int (*run_builtin(char *cmd))(char **args, char **fnt);
int shel_env(char **args, char __attribute__((__unused__)) **fnt);
int shel_setenv(char **args, char __attribute__((__unused__)) **fnt);
int shel_unsetenv(char **args, char __attribute__((__unused__)) **fnt);

void help_all(void);
void help_al(void);
void help_cd(void);
void help_exit(void);
void help_help(void);

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);
ar **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

int num_wen(int n);
char *_ito(int n);
int create_error(char **args, int er);

char *error_12(char **args);
char *error_13(char **args);

char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);

void sig_handler(int sig);
int execute(char **args, char **fnt);

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

int print_lowercase(int b);
void prompt(char **av, char **env);

#endif

