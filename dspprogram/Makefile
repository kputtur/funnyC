CC = gcc
CFLAGS = -g -Wall

default: homework2

homework2:	utility.o transform.o menu.o
		$(CC) $(CFLAGS) -o homework2 utility.o transform.o menu.o

utility.o:	utility.c
		$(CC) $(CFLAGS) -c utility.c
menu.o:		menu.c
		$(CC) $(CFLAGS) -c menu.c	

transform.o:	transform.c
		$(CC) $(CFLAGS) -c transform.c 
clean:
	rm -rf out *o
	@echo "cleaning all files"
	
