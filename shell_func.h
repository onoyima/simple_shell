#ifndef_SHELL_FUNC_H_
#define_SHELL_FUNC_H_

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

/* for read abd write buffers */
#define READ_BUFF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define buF_FLUSH -1

/* Code for command chaining */
#define COMMAND_NORM 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

/* Code for converting numbers ()*/
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* get 1 if using the system getline()*/
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

exter char **environ;

/**
 * struck liststr - singly linked list
 * @number: the number field
 * @str: a string
 * @next: points to the next node
 */

typedef struck liststr
{
	int number;
	char *str;
	struck liststr *next
} shell_list_t;


/*
 * struck passinfomat - contains pseudo-argument to pass intO  function,
 * allowing uniform prototype for function pointer struct
 * @argument: a string generated from getlime containing argument
 * @argument_value: an array of strings generated from argument
 * @path: a string path for the current command
 * @argument_count: the argument count
 * @line_count: the error count
 * @error_number: the error code for exit()s
 * @line_count_flag: if on the count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the las exec'd command
 * command_buf: address of pointer to command_buf, on if chaining
 * @command_buf_type: command_type ||, &&,;
 * @read_f_d: the f_d from which to read line input
 * @hist_count: the history line number count
 */
typedef struct passinfomat
{
	char *argument;
	char **argument_value;
	char *path;
	int argument_count;
	unsigned int line-count;
	int errror_number;
	int line_count_flag;
	char *fname;
	shell_list_t *env;
	shell_list_t *histroy;
	shell_list_t *alias;
	char **eniron;
	int env_changeed;
	int status;
	char **command_buf;
	int read_f_d;
	int hist_count;
} shell_infomat_t;

#define infomat_INIT\ 
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0,
NULL,\
0, 0, 0}

/**
 * struck is_builtin_shell - contains a is_builtin_shell string and 
 * related function
 * @type: the is_builtin_shell command flag
 * @func: the function
 */
typedef struck is_builtin_shell
{
	char *type;
	int (*func) (shell_infomat_t*);
} is_builtin_shell_table;
/ * shell_0x16 project_shloop.c*/
int shell_hash(shell_infomat_t*, char**);
int find_is_builtin_shell(shell_infomat_t*);
void find_command(shell_infomate_t*);
void fork_command(shell_infomate_t*);

/* shell_0x16 prok=ject _parser.c*/
int is_command(shell_infomate_t*, char *);
char *duplicate_characters(char*, int, int);
char *find_path(shell_infomat_t*, char*, char *);

/* loopshell_hash.c*/
int loopsell_hash(char**);


/* shell_0x16 projecst errors.c */
void is_eputs(char **);
int is_eput_character(char);
int _putf_d(char *str, int f_d);

/* shell_0x16 project _string.c */
int _strlenths(char*);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* shell_0x16 project _string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putcharacter(char);

/* shell_0x16 project _exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* shell_0x16 project _tokenizer.c */
char **strtow(char *, char *);
char **str_to_word2(char *, char);

/* shell_0x16 project is__realloc.c */
char *is_memset(char *, char, unsigned int);
void shell_ffree(char **);
void *is__realloc(void *, unsigned int, unsigned int);

/* shell_0x16 project _memory.c */
int bfree_shell(void **);

/* shell_0x16 project is_shell_atoi.c */
int is_interactive(shell_infomat_t *);
int is_delimeter(char, char *);
int is_alphabetic(int);
int is_shell_atoi(char *);

/* shell_0x16 project _errors1.c */
int is_errorshell_atoi(char *);
void print_error(shell_infomat_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void is_remove_comments(char *);

/* shell_0x16 project _is_builtin_shell.c */
int is_my_own_exit(shell_infomat_t *);
int shell_my_own_cd(shell_infomat_t *);
int shell_myhelp(shell_infomat_t *);

/* shell_0x16 project _is_builtin_shell1.c */
int is_history(shell_infomat_t *);
int owned_myalias(shell_infomat_t *);

/*shell_0x16 project _getline.c */
ssize_t resurieve_input(shell_infomat_t *);
int _getline(shell_infomat_t *, char **, size_t *);
void sigintHandler(int);

/* shell_0x16 project _getinfomat.c */
void clear_infomat(shell_infomat_t *);
void set_infomat(shell_infomat_t *, char **);
void free_infomat(shell_infomat_t *, int);

/* shell_0x16 project _getenv.c */
char *is_getenv(shell_infomat_t *, const char *);
int owned_env(shell_infomat_t *);
int mount_env_shell(shell_infomat_t *);
int unmount_env_shell(shell_infomat_t *);
int increase_env_list(shell_infomat_t *);

/* shell_0x16 project is_environ.c */
char **get_environ(shell_infomat_t *);
int _unmount_env_shell(shell_infomat_t *, char *);
int _mount_env_shell(shell_infomat_t *, char *, char *);

/* shell_0x16 project _history.c */
char *get_history_file(shell_infomat_t *infomat);
int write_history(shell_infomat_t *infomat);
int read_history(shell_infomat_t *infomat);
int build_history_list(shell_infomat_t *infomat, char *buf, int line_count);
int renumber_history(shell_infomat_t *infomat);

/* shell_0x16 project _lists.c */
shell_list_t *add_node(shell_list_t **, const char *, int);
shell_list_t *add_node_end(shell_list_t **, const char *, int);
size_t display_list_str(const shell_list_t *);
int remove_node_at_index(shell_list_t **, unsigned int);
void free_list(shell_list_t **);

/* shell_0x16 project _lists1.c */
size_t list_length(const shell_list_t *);
char **shell_list_to_strings(shell_list_t *);
size_t display_list(const shell_list_t *);
shell_list_t *node_starts_with(shell_list_t *, char *, char);
ssize_t get_node_index(shell_list_t *, shell_list_t *);

/* shell_0x16 project _vars.c */
int is_chain(shell_infomat_t *, char *, size_t *);
void check_chain(shell_infomat_t *, char *, size_t *, size_t, size_t);
int replace_alias(shell_infomat_t *);
int replace_vars(shell_infomat_t *);
int replace_string(char **, char *);

#endif
