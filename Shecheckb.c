#include "shell.h"

void help_all(void);
void help_al(void);
void help_cd(void);
void help_exit(void);
void help_help(void);

/**
 * help_all -  shel commands.
 */
void help_all(void)
{
	char *msg = "Shellby\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "out more about the function 'name'.\n\n  al   \t";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "al [NAME[='VAL'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "\n  setenv  \tsetenv [VARIABLE] [VAL]\n  unsetenv\t";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, msg, strlen(msg));
}

/**
 * help_al - Displays information on the shellby builtin command 'alias'.
 */
void help_al(void)
{
	char *msg = "al: al[NAME[='VAL'] ...]\n\tHandles als.\n";

	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "\n\tal: Prints a list of all als, one per line, in ";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "the format NAME='VAL'.\n\tal name [name2 ...]:prints";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = " the als name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "form NAME='VALUE'.\n\tal NAME='VAL' [...]: Defines";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = " an al for each NAME whose VAL is given. If NAME ";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "is already an al, replace its value with VAL.\n";
	write(STDOUT_FILENO, msg, strlen(msg));
}

/**
 * help_cd - shel commands
 */
void help_cd(void)
{
	char *msg = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, msg, strlen(msg));
	msg = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "after a change of directory.\n";
	write(STDOUT_FILENO, msg, strlen(msg));
}

/**
 * help_exit - shel commands
 */
void help_exit(void)
{
	char *msg = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = " exit 0.\n";
	write(STDOUT_FILENO, msg, strlen(msg));
}

/**
 * help_help - shel command
 */
void help_help(void)
{
	char *msg = "help: help\n\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, msg, strlen(msg));
	msg = "builtin command.\n";
	write(STDOUT_FILENO, msg, strlen(msg));
}
