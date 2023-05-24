#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* input output*/
#include <unistd.h> /* forking, execve*/
#include <stdlib.h>
#include <string.h> /* string tokenization*/
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* wait */
#include <sys/stat.h> /* static function */
#include <signal.h> /* signal management */
#include <fcntl.h> /* to open files*/

/*----------- User defined header file ------------------*/
#include "macros.h" /* for msg help and prompt */

/*------------- Structure --------------*/

/**
 * info - struct for commands
 * @name: The executable name
 * @inputPointer: A pointer that points to the input
 * @cmdName: points first cmd
 * @execCount: num of excecuted cmds
 * @descFile: file description to the input of commands
 * @tkn: pointer to array of tokenized input
 * @envr: copy of the envriron
 * @aliasList: List of array pointers with aliases.
 */

typedef struct info
{
	char *name;
	char *inputPointer;
	char *cmdName;
	int execCount;
	int descFile;
	char **tkn;
	char **envr;
	char **aliasList;
} progData;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */

typedef struct builtins
{
	char *builtin;
	int (*function)(progData *prog);
} builtins;

/*------------ main functions of the program -------------*/
/*--  shell.c  --*/

void InitializeData(progData *prog, int arc, char *argv[], char **envr);
void sIsInfo(char *prompt, progData *prog);
void ctrlHandle(int opr UNUSED);

/*--  getLine.c  --*/

int getLine(progData *prog);
int logicCheck(char *cmdList[], int tmp1, char oprList[]);

/*-- exp.c --*/

void varExpand(progData *prog);
void aliasExpand(progData *prog);
int addBuffer(char *buffer, char *addStr);

/*-- tokenizeString.c --*/

char *stringToken(char *line, char *endStr);

/*-- token.c --*/

void tokStr(progData *prog);

/*-- runCommand.c --*/

int runCommand(progData *prog);

/*-- listBuiltin.c --*/

int executeBuiltin(progData *prog);

/*-- pathFind.c --*/

char **splitPath(progData *prog);
int searchPrg(progData *prog);
int check_file(char *fullPath);

/*--------------- HELPERS FOR MEMORY MANAGEMENT ---------------*/
/*-- freeHelper.c --*/

void arrayPointer(char **list);
void recData(progData *prog);
void freeAlldata(progData *prog);

/*----------- BUILTINS -----------*/
/*-- moreBuiltin.c --*/

int exitShell(progData *prog);
int changeDirectory(progData *prog);
int setWD(progData *prog, char *dirNew);
int displayHelp(progData *prog);
int manageAlias(progData *prog);

/*-- enviromentBuiltin.c --*/

int displayEnviroment(progData *prog);
int setEnviromentVariable(progData *prog);
int unsetEnviromentVariable(progData *prog);

/*------------ HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT ------------*/
/*-- manageEnviroment.c --*/

char *getKey(char *card, progData *prog);
int setKey(char *card, char *holder, progData *prog);
int removeKey(char *card, progData *prog);
void printEnv(progData *prog);

/*------------- HELPERS FOR PRINTING --------------*/
/*-- printHelper.c --*/

int printString(char *tmpStr);
int printError(char *tmpStr);
int printErrorMessage(int errMSG, progData *prog);

/*------------------ HELPERS FOR STRINGS MANAGEMENT ------------------*/
/*-- stringHelper.c --*/

int getStringLength(char *tmpStr);
char *duplicateString(char *tmpStr);
int stringCompare(char *tmpStr1, char *tmpStr2, int number);
char *stringConcatenate(char *tmpStr1, char *tmpStr2);
void stringReverse(char *tmpStr);

/*-- numbersHelper.c --*/

void longToStr(long number, char *tmpStr, int tmpConstant);
int _atoi(char *tmpStr);
int charCount(char *tmpStr, char *tmpChar);

/*-- manageAlias.c --*/

int printAlias(progData *prog, char *strChar);
char *getAlias(progData *prog, char *strChar);
int setAlias(char *strChar, progData *prog);

#endif

