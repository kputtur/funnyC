#include "mycat.h"
//defination for globals
int read_stdin = true;
int setNumber = false;
int setNumber_nonblank = false;
int file_open_mode = O_RDONLY;

#define BUFF_LC 20

static char buf_cnt[BUFF_LC] =
  {
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0',
    '\t', '\0'
  };

/* This will hold to width of 6 digit Max 999999 */
static char *line_print = buf_cnt + BUFF_LC - 8;

/* first digit*/
static char *line_start = buf_cnt + BUFF_LC - 3;

/* last digit */
static char *line_end = buf_cnt + BUFF_LC - 3;

/* Line number calculation goes here */

/* Here the logic is keep on incrementing the number
 * untill you hit number 9, once you hit > 9 put 0
 * on the last byte
 *
 *
 *  This is shamelessly adopted from the logic present
 *  in the core-utils program
 *  Reference:http://www.gnu.org/software/coreutils
 *
 */

static void next_num (void)
{
  char *endp = line_end;
  do
    {
      if ((*endp)++ < '9')
        return;
      *endp-- = '0';
    }
  while (endp >= line_start);

  /* 10, 100,1000,10000 go here	*/
  if (line_start > buf_cnt)
  {
    *--line_start = '1';
  }

  else
  {
    *buf_cnt = '>';
  }

  if (line_start < line_print)
  {
    line_print--;
  } 
}

/* here outbuf is compared with pointer to next character
 * in the buffer if *ptrout - outbuf is greater than 0
 * then write happens otherwise program just returns
 */

static void doWriteCall (char *outbuf, char **ptrout)
{
  size_t total_write = *ptrout - outbuf;
  char fwriteerr[] = "write: error occured";

  if (0 < total_write)
    {
      if (write(STDOUT_F, outbuf, total_write) != total_write)
      {
    	write(STDOUT_F, fwriteerr,mesglength(fwriteerr) );
      }
      *ptrout = outbuf;
    }
}

int readwrite(char *inbuf, char * outbuf, int setNumber, int setNumber_nonblank)
{
	
	// last char
	unsigned char lastch;

	// pointer to next character in the input buffer
	char *bufferin;
	
	// end of buffer
	char *endbuff;

	//pointer to out buffer position where next char will be written
	char *bufferout;

	// number of characters read by the last read call
	size_t n_read;
	
	// new lines
	int newlines = 0;
	
	// At the start set end buff to inbuf and bufferin is enbuff + 1
	endbuff = inbuf;
	bufferin = endbuff + 1;

	// initialize buffer out to outbuff --which is empty
	bufferout = outbuf;


for(;;)
{
   do {
			//input buffer must be empty
	 if ( bufferin > endbuff)	
	   {
	    //if there is something to written better write now
	    //after writing set bufferout = outbuf
	   doWriteCall(outbuf, &bufferout);

	//do a read
	 n_read	= read(input_fd, inbuf, READ_LENGTH);

	//if read is 0 , must be endof file write pending and then return 
	if ( n_read == 0)
	{
	/*must have reached the end of file */
	 doWriteCall(outbuf, &bufferout);
	 return false; //all good here
	}

	bufferin = inbuf;	
	endbuff = bufferin + n_read;

	//set a fake new line as guard for running over
	*endbuff = '\n';
 	}
	//else is entered only on finding the new line
	else
	 {
		//we found a new line
		if(++newlines > 0)
		{	
		//this is beginning of new line, so if want line no print it
		if( (setNumber == true) && !(setNumber_nonblank == true))
		{
		  next_num();
		  bufferout = doCpyBuff(bufferout, line_print);
		 }
		}
	//Make sure the new line is put into the buffer as well
	       *bufferout++ = '\n';
	  }
	lastch = *bufferin++;
}
while( lastch == '\n');


if ( (newlines >= 0) && (setNumber == true))
{
	//get the next number
	next_num();
	//copy the number back to bufferout address
	bufferout = doCpyBuff(bufferout, line_print);
}

//following for loop is for writing bytes from bufferin to bufferout
//until you hit the new line.
for(;;)
{
	//if we are not newline copy contents
	if ( lastch != '\n')
	 *bufferout++ = lastch;
	else
	 {
		//if we find actual new line
		//set the newlines to -1 and break out of loop
	      newlines = -1;
	      break;
	  }
		//byte to byte copy happens here
	    lastch = *bufferin++;
}


}
}


void setoptions(char *input)
{
	char *in = input;
	char opterrmsg[]  = "ERROR:invalid option in option string..ignoring";
	 while ( *in != '\0')
	 {
	  switch( *in)
	  {
	  case '-':
				 break;
	  case 'n':
			     setNumber = true;
				 setNumber_nonblank = false;
				  break;
	  case  'b':
			     setNumber = true;
				 setNumber_nonblank = true;
				 break;

	  default:
			   write(STDOUT_F, opterrmsg, mesglength(opterrmsg));
			   write(STDOUT_F, "\n", 2);
	  }
	  //increment array
	  in = input++;

    } //for while

}


int main(int argc, char **argv)
{
	int i = 0;
	char *inbuf = (char *) malloc(sizeof(char) * READ_LENGTH * 2);
	char *outbuf = (char *) malloc(sizeof(char) * READ_LENGTH * 2);
	int status = 0;
	//set globals


	char fopenmsg[] = "cat: :No such directory or file\n";
	char ferrmesg3[]= "an error occured while outputting the file";


	/*set program name */
	//char * progname = argv[0];

	 /* set input fd to STDIN */
	input_fd = STDIN_F;

	 if ( (argc > 1) && (*argv[1] == '-')  )
	 {
		 setoptions(argv[1]);


	     if (( argc > 2) && (*argv[2] == '-' ))
	     {
	    	 setoptions(argv[2]);
	      }
	 }

	 // open file descriptor for reading
	 while ( --argc)
	 {

		if ( *argv[++i] == '-')
			continue;
		 //must be a file open it
		inFile = argv[i];
		input_fd = open(inFile, file_open_mode);

		if ( input_fd < 0 )
		{

		 write(STDOUT_F, fopenmsg, mesglength(fopenmsg));
		 read_stdin = false;

		  }
		else {

		 	read_stdin = false;
			status = readwrite(inbuf, outbuf,setNumber, setNumber_nonblank);
			if ( status == 1)
				write(STDOUT_F, ferrmesg3, mesglength(ferrmesg3));
			close(input_fd);
		     }
	     }


if ( read_stdin)
{
	status = readwrite(inbuf, outbuf,setNumber, setNumber_nonblank);
	if ( status == 1)
		write(STDOUT_F, ferrmesg3, mesglength(ferrmesg3));
   }

	free(inbuf);
	free(outbuf);
	return status;

}



			


	
