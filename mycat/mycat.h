/*
Header File : mycat.h
Author	    : Kiran Puttur
Date	    : Feb 27, 2010
*/
#ifndef  _MYCAT_H
#define  _MYCAT_H

//#include <sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
//#include<stdio.h>

#define   STDIN_F      0
#define   STDOUT_F     1
#define   STDERR_F     2

#define   true	       1
#define	  false	       0

#define O_RDONLY	     00
#define O_WRONLY	     01
#define O_RDWR		     02

#define READ_LENGTH		 81

char const *inFile;



/* input file descriptor */
int input_fd;

/* All Error Message Goes Here */
extern char fopenmsg[] ;
extern char fwriteerr[];
extern char ferrmesg3[];
extern char opterrmsg[];

/* global variables */
extern int read_stdin;
extern int setNumber;
extern int setNumber_nonblank ;
extern int file_open_mode;


extern int mesglength(char *);
extern int readwrite(char *, char *, int, int);
extern void setoptions(char *);
extern char *doCpyBuff(char *, const char *);


#endif
