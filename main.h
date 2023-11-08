#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

/* Converting a number */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Use to read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define FLUSH -1

/* Use to do command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * Custom data structure for a singly linked list.
 * @num: Number field.
 * @str: String field.
 * @next: Points to the next node in the list.
 */
typedef struct list
{
        int num;
        char *str;
        struct liststr *next;
} list_t;

/**
 * struct passinfo - Custom data structure for holding pseudo-arguments
 * to be passed into a function.
 * @arg: String generated from getline containing arguments.
 * @argv: Array of strings generated from the argument string.
 * @path: String path for the current command.
 * @argc: Number of arguments.
 * @line_count: Count of encountered errors.
 * @err_num: Error code used for exit operations.
 * @linecount_flag: Flag to indicate whether counting the current input line.
 * @fname: Name of the current program file.
 * @env: Linked list representing the local copy of the environment variables.
 * @environ: Custom modified copy of the environment variables from the LL env.
 * @history: Linked list node representing the history.
 * @alias: Linked list node representing aliases.
 * @env_changed: Flag indicator for changed environment variables..
 * @status: Status of the last executed command.
 * @cmd_buf: Address of the pointer to the command buffer used for chaining.
 * @cmd_buf_type: Type of command chaining (e.g., ||, &&, ;).
 * @readfd: File descriptor from which to read line input.
 * @histcount: Count of history line numbers.
 */
typedef struct name
{
        char *arg;
        char **argv;
        char *path;
        int argc;
        unsigned int line_count;
        int err_num;
        int linecount_flag;
        char *fname;
        list_t *env;
        list_t *history;
        list_t *alias;
        char **environ;
        int env_changed;
        int status;

        char **cmd_buf;
        int cmd_buf_type;
        int readfd;
        int histcount;
} info_t;

#define INFO_INIT
     \
        {
         \
                NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
                        0, 0, 0
                 \
        }
/**
 *struct builtin - Custom data structure for built-in commands
 *                                      and their associated functions.
 *@type: The built-in command flag (string representation).
 *@func: Pointer to the function that implements the built-in command.
 */
typedef struct builtin
{
        char *type;
        int (*func)(info_t *);
} builtin_table;

/*--------Function Prototypes--------*/

/*--------Funtion Prototypes for atoi.c--------*/
int check_interactive_mode(info_t *);
int check_delim(char, char *);
int check_alpha(int);
int our_atoi(char *);

/*--------Funtion Prototypes for builtin.c--------*/
int exits_func(info_t *);
int cd_func(info_t *);
int _help(info_t *);

/*--------Funtion Prototypes for builtin1.c--------*/
int _history(info_t *);
int _alias(info_t *);

/* loophsh.c */
int loophsh(char **);

/*--------Funtion Prototypes for environ.c--------*/
char *_getenvs(info_t *, const char *);
int my_enviroment(info_t *);
int mys_setenv(info_t *);
int mys_unsetenv(info_t *);
int displays_env_list(info_t *);

/*--------Funtion Prototypes for errors.c--------*/
void my_inputs(char *);
int my_inputchar(char);
int _putfiled(char c, int fd);
int puts_filed(char *str, int fd);

/*--------Funtion Prototypes for errors1.c--------*/
int _erroratoi(char *);
void print_error(info_t *, char *);
int print_decimal(int, int);
char *convert_num(long int, int, int);
void rm_comments(char *);

/*--------Funtion Prototypes for exits.c--------*/
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/*--------Funtion Prototypes for getenv.c--------*/
char **get_environment(info_t *);
int _unsetenviroment(info_t *, char *);
int _setenviroment(info_t *, char *, char *);

/*--------Funtion Prototypes for getinfo.c--------*/
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/*--------Funtion Prototypes for getline.c--------*/
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigint_handler(int);

/*--------Funtion Prototypes for history.c--------*/
char *_history_file(info_t *info);
int write_histo(info_t *info);
int read_histo(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_histo(info_t *info);

/*--------Funtion Prototypes for lists.c--------*/
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/*--------Funtion Prototypes for lists1.c--------*/
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/*--------Funtion Prototypes for memory.c--------*/
int freed(void **);

/*--------Funtion Prototypes for parser.c--------*/
int is_cmd(info_t *, char *);
char *aduplicate_chars(char *, int, int);
char *find_paths(info_t *, char *, char *);

/*--------Funtion Prototypes for realloc.c--------*/
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/*--------Funtion Prototypes for shell_loop.c--------*/
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/*--------Funtion Prototypes for string.c--------*/
int my_strlen(char *);
int my_strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/*--------Funtion Prototypes for string1.c--------*/
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/*--------Funtion Prototypes for tokenizer.c--------*/
char **split_string(char *, char *);
char **split_string2(char *, char);

/*--------Funtion Prototypes for vars.c--------*/
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
