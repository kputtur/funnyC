CC := gcc
CFLAGS := -ggdb -Wall

default:	clean mycat

mycat:	util.o mycat.o
	@echo "linking" 
	$(CC) $(CFLAGS) -o mycat util.o mycat.o
util.o:	util.c
				@echo "compiling..."	
	$(CC) $(CFLAGS) -c util.c
mycat.o:	mycat.c
	$(CC) $(CFLAGS) -c mycat.c

clean:	
		rm -rf mycat *o
		@echo "cleaning all files"
	

