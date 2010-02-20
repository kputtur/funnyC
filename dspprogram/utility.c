/*
 * utility.c
 *
 *  Created on: Feb 17, 2010
 *      Author: kiran
 */

#include "module.h"

char returnchar(int i)
{
			char convert[32] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E',
								'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T',
								'U','V'};
			char c;
			ERROR = 0;
			if ( i < 0 && i > 31)
			{
				ERROR = 1;
			}
			c = convert[i];
			return c;
}

int returnint(char c)
{

		char convert[32] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E',
								'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T',
								'U','V'};
	    int returnint = 35, i = 0;
	    ERROR = 0;
   		for( i = 0; i < 32;i++)
		{
				if ( c == convert[i])
				{
					returnint = i;
				}
		}
		if ( returnint == 35)
		{
			ERROR = 1;
		}
		return returnint;

}

int isvalid(char c)
{
	if ((c >= '0' && c <= '9') || ( c >= 'A' && c <= 'V'))
		return 1;
	else
		return 0;
}

void getinarray(FILE *fp)
{
	  char c;
	  /* input validaters */
	  int expectnewline = 1;
	  /*debug remove later */
	  //int k,l,m;

	  /* array walkers */
	  int i = 0, j = 0;
	  int oldj = 0;

	  /* initialize ERROR */
	  ERROR = 0;

	   while ( (c = getc(fp)) != EOF)
	   {
	      if (c == '\n') {
			if(expectnewline == 0)
			{
			  printf("\n ignoring consecutive new lines \n");
			  continue;
			 }
			/* increment row count */
			i++;

			/*check column length or report error */
		    if ( ( i > 1) && ( oldj != j))
			{
			  printf("\n Error in the input \n");
			  ERROR = 1;
			}
			/* reset column values, save old values */
			oldj = j;
			j = 0;
			printf("\n");

			/*check rowcount increase ROWCOUNT */
			if ( i > RCOUNT)
			{
			  printf("Cannot exceeed rcount value ");
			  ERROR = 1;
			 }


			expectnewline = 0;
			continue;
			}

	   if ( isspace(c))  {
		printf("spaces are not allowed ...exiting");
		ERROR = 1;
		break;
		}

	    if ( ! isvalid(c)) {
		printf("invalid data found ...exiting");
		ERROR = 1;
	    break;
		}
      	// printf("\t%c,", c);
		 ARRAY[i][j] = returnint(c);
		/*space is expected */
	    expectnewline = 1;

		/*increment column */
		j++;
 	   }


		 //printf("\nDEBUG:val of i=%d, j=%d \n", i, oldj);
	    if (i <= 0 || oldj <= 0)
	    {
	    	printf("\nError getting the input from file ");
	        ERROR = 1;

	    }
	    else {
	    	 // printf("\n column = %d, row = %d \n", oldj, i);
	    	  ROWS = i;
	    	  COLUMNS = oldj;
	    }
	    /* debug below remove later */


}

void printarray(int *arrayp)
{
			int i,j,k;
			char c;
			printf("\n\n\n\n");
			for ( i=0; i< ROWS; i++)
			{
				for ( j=0; j<COLUMNS; j++)
				{
					if ( j < (COLUMNS - 1)) {
					k = arrayp[i * COLUMNS + j];
					c = returnchar(k);
					if ( ERROR == 1)
					{
					printf("\n Error occured while transforming \n");
					break;
					}
					printf("\t%c,\t", c);
					}
					else {
					k = arrayp[i * COLUMNS + j];
					c = returnchar(k);
					if ( ERROR == 1) {
					printf("\n Error occured while transforming \n");
					break;
					}
				printf("%c \n", c);
					}
				}
			}
}

void setarray(int *arrayp1, int *arrayp2, int *arrayp3)
{
	int i, j;

	for ( i = 0; i < ROWS; i++)
	{
		for ( j = 0; j<COLUMNS; j++)
		{
				arrayp1[i * COLUMNS + j] = ARRAY[i][j];
		}
	}
	copyarray(arrayp2, arrayp1);
	copyarray(arrayp3, arrayp1);

}

void copyarray(int *dest, int *source)
{
		int i, j;
		for ( i = 0; i < ROWS; i++)
		{
			for (j = 0; j < COLUMNS; j++)
			{
				dest[i *COLUMNS+ j] = source[i * COLUMNS + j];
			}
		}
}



void undotransform(int *dest, int *source)
{
		//	resultarr = holdarrayg;
		copyarray(dest, source);
		printarray(dest);
}

void savetransform(int *arrayp)
{
		FILE *ofp;
		int i, j, k;
		char c;

		printf("\n\n\t *saving the transformation to file:transform* \n\n");
		printarray(arrayp);
		if ( (ofp = fopen("transform", "w")) == NULL )
		{
			fprintf(stderr, "Error opening the file for writing ");
			exit(1);
		}
		for ( i=0; i< ROWS; i++)
					{
						for ( j=0; j<COLUMNS; j++)
						{
							if ( j < (COLUMNS - 1)) {
							k = arrayp[i * COLUMNS + j];
						    c = returnchar(k);
							if ( ERROR == 1)
							{
							fprintf(stderr,"\n Error occured while transforming \n");
							break;
							}
							fprintf(ofp, "%c", c);
							}
							else {
							k = arrayp[i * COLUMNS + j];
							c = returnchar(k);
							if ( ERROR == 1) {
							fprintf(stderr, "\n Error occured while transforming \n");
							break;
							}
						fprintf(ofp, "%c\n", c);
							}
						}
					}
		fclose(ofp);

}

void ShowUsage() {
					printf("\n usage:<PROGRAMNAME> <FILENAME> \n");
					printf("Moreinfo:\n");
					printf(" \n This is image transformation program ");
					printf(" invoke the program like this \n homework1 filename");
					printf("\n main Menu presents the available transformation ");
					printf("\n Transformation menu lets user apply the transformation ");
					printf("\n\n ------------------------\n");
					printf("Have fun using the program \n");
}

