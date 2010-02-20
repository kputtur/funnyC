/*
 * module.h
 *
 *  Created on: Feb 17, 2010
 *  Author: Kiran Puttur
 */

#ifndef MODULE_H_
#define MODULE_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define RCOUNT 10
#define CCOUNT 10
#define STRINGLENGTH 80

#define AVGTRANSFORM 1
#define NEGTRANSFORM 2
#define NEWTRANSFORM 3
#define NEWTRAN1     4
#define NEWTRAN2     5

int ROWS; 
int COLUMNS;

/*input variables */
int ctransform;
int scanstatus, command;
char charcommand;



/* dynamic array holder */


/* error handling */
int ERROR;

int ARRAY[RCOUNT][CCOUNT];

/* conversion functions */


extern char returnchar(int i);
extern int returnint(char c);
extern int isvalid(char c);

/*input file reader */
extern void getinarray(FILE *);

/* end conversion functions */


/* average transform */
extern int avgtransform(int *arrayp, int nrows, int ncolumn, int posx, int posy);

/* negative transform */
extern int negtransform(int val);

/* stub transformations */

extern void stubtrans1(int i);

/* end transformation functions */

extern void setarray(int *, int *, int *);
/* print array :prints array */
extern void printarray(int *);

/*copy array */
extern void copyarray(int *, int *);

extern void applytransform(int *);
extern void undotransform(int *, int *);
extern void savetransform(int *);

extern void ShowUsage();

void mainMenu(int *);
void mainLoop(int *, int *, int *);
int subMenu(int *, int *, int *);
void prompt();
void charprompt();
void ParseCmdLine(int, char **);
void waitforuser();

#endif /* MODULE_H_ */
