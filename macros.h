#ifndef HELPERS_H
#define HELPERS_H

#define MESSAGEDISPLAY "dali<3 "
#define UNUSED __attribute__((unused))
#define MEMORYCAPACITY 1024

#define CHANGEDIRECTORYHELPMESSAGE "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	Change current working directory.\n\n"\
"	If there is no argument given to the cd command it will be interpreted\n"\
"	as cd $HOME.\n"\
"	if the argument help is - (cd -), the command will be interpreted\n"\
"	as cd $OLDPWD.\n\n"

#define EXITHELPMESSAGE "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	Exit of the simple-shell.\n\n"\
"	Exits the shell with a status of N.  If N is omitted, the exit status\n"\
"	is that of the last command executed.\n\n"

#define ENVIROMENTHELPMESSAGE "env=\n"\
"env:\tenv \n\n"\
"	Print environment.\n\n"\
"	The env command will print a complete list of enviroment variables.\n\n"

#define SETENVIROMENTHELPMESSAGE "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	Modify or add an environment variable.\n\n"\
"	Create a new environment variable, or change an existing one\n"\
"	When there are not correct numbers of arguments print error message.\n\n"

#define UNSETENVIROMENTHELPMESSAGE "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	The unsetenv function removes one variable from the environment.\n\n"\
"	When there are no correct numbers of arguments print error message.\n\n"

#define HELPMESSAGE "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	Show the information about builtin commands.\n\n"\
"	Show brief summaries of builtin commands.  If BUILTIN_NAME is\n"\
"	specified, gives detailed help on all commands matching BUILTIN_NAME,\n"\
"	otherwise the list of help topics is printed BUILTIN_NAME list.\n"\
"	Arguments:\n\n"\
"	BUILTIN_NAME specifiying a help topic.\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[built_name]\n\n"

#endif
