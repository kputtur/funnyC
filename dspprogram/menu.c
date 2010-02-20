/*
 * menu.c
 *
 *  Created on: Feb 17, 2010
 *      Author: kiran
 */
#include "module.h"

void mainMenu(int *arrayp1)
{
	printf("\n\n\n\n");
	printf("     |*|  MAIN MENU |*| \n");
	printf("   -----------------------\n\n");
	printf("  1.select average transform \n");
	printf("  2.select negative transform \n");
	printf("  3.select new transform \n");
	printf("  4.select new transform \n");
	printf("  5.select new transform \n");
	printf("\n");
	printf("\tcurrently loaded/transformed image from file");
	printarray(arrayp1);
	return;
}

void MainLoop(int *arrayp1, int *arrayp2, int *arrayp3)
{
		command = 10;
		ctransform = 0;
		while ( command != 0)
		{
			mainMenu(arrayp2);
			prompt();
			switch (command)
			{
			case 1:
					ctransform = AVGTRANSFORM;
					command = subMenu(arrayp1, arrayp2, arrayp3);
					break;
			case 2:
				    ctransform = NEGTRANSFORM;
				    command = subMenu(arrayp1, arrayp2, arrayp3);
				    break;
			case 3:
					ctransform = NEWTRANSFORM;
					command= subMenu(arrayp1, arrayp2, arrayp3);
					break;
			case 4:
					ctransform = NEWTRAN1;
					command = subMenu(arrayp1, arrayp2, arrayp3);
				    break;
			case 5:
					ctransform = NEWTRAN2;
					command = subMenu(arrayp1, arrayp2, arrayp3);
					break;
			case 0:
					break;
			default:
					 printf("\n Invalid selection \n");

			}


		}
		return;
}

int subMenu(int *arrayp1, int *arrayp2, int *arrayp3) {

	while (charcommand != 'x')
	{
	printf("\n\n\n\n");
	printf("     |*|  APPLY TRANSFORMATION |*| \n");
    printf("        -----------------------\n");
	printf("f : apply current transform\n");
	printf("b : undo the last transform \n");
	printf("s : save the transform to new file \n");
	printf("m : getback to the menu \n");
	printf("h : help about this program\n");
	printf("x : exit the menu\n");
	printf("\n");
	charprompt();

	switch (charcommand)
	{
	case 'f':
			  copyarray(arrayp3, arrayp2);
			  applytransform(arrayp2);
			  break;
	case 'b':
			   undotransform(arrayp2, arrayp3);
			   break;
	case 's':
			   savetransform(arrayp2);
			   break;
	case 'm':
			  command = 10;
			  return command;
	case 'h':
			  ShowUsage();
			  break;
	case 'x':
			  command = 0;
			  printf("\n Exiting the Program. Have a nice Day \n");
			  return command;
	default:
			  printf("\n invalid selection \n");
	}
	 waitforuser();
	}
return (1); //keeping the compiler happy :)

}


void prompt()
{
		char string[STRINGLENGTH];
		char *input = string;
		printf("\n\n Command [press 0 to exit]: ");
		input = fgets(input, STRINGLENGTH, stdin);
		if ( strlen(input) > 2) command = 10;
		else {
			scanstatus = sscanf(input, "%d", &command);
			if ( scanstatus <= 0 || command < 0)
				command = 10;

		}
}

void waitforuser()
{
	 char string[STRINGLENGTH];
	 char *input = string;
	 printf("\n\n Press any Key to proceed:");
	  do {
	 input = fgets(input, STRINGLENGTH, stdin);
	 } while (strlen(input)<=0 );
}

void charprompt()
{
	   char string[STRINGLENGTH];
	   char *input = string;
	   printf("\n\n Command:");
	   input = fgets(input, STRINGLENGTH, stdin);
	   if ( strlen(input) > 2) charcommand = 'u';
	   else {
		     scanstatus = sscanf(input, "%c", &charcommand);
		     if ( scanstatus <= 0)
		    	 charcommand = 'u';
	   }
}

void ParseCmdLine(int argc, char ** argv)
{
	  FILE *fp;

	   /* Initialize global ERROR to zero */
	  ERROR = 0;

	  if ( argc != 2)
	  {
		  fprintf(stderr, "\n please check usage");
		  fprintf(stderr, "\n---------------------\n");
		   ShowUsage();
		   exit(1);
	  }
	  else  if ( (fp = fopen(argv[1], "r")) == NULL )
	  {
		fprintf(stderr, "\n Error opening the file %s \n", argv[1]);
		exit(1);
	   }

	  else {
				getinarray(fp);
		  		if ( ERROR == 1) {
		  			printf("\n ERROR occured while processing file \n");
		  			exit(1);
		  		}
		  		fclose(fp);
	  }



}

int main(int argc, char **argv)
{

		ParseCmdLine(argc, argv);
		int i;
		int **arrayg = malloc(ROWS * sizeof(int *));
		arrayg[0] = malloc(ROWS * COLUMNS * sizeof(int));
		for ( i = 1; i < ROWS; i++)
		{
			arrayg[i] = arrayg[0] + i * COLUMNS;
		}

		  int **resultarr = malloc(ROWS * sizeof(int *));
		  resultarr[0] = malloc(ROWS * COLUMNS * sizeof(int));
		  for ( i = 1; i < ROWS; i++)
		  {
					resultarr[i] = arrayg[0] + i * COLUMNS;
		  }

		  int **holdarrayg = malloc(ROWS * sizeof(int *));
		  holdarrayg[0] = malloc(ROWS * COLUMNS * sizeof(int));
		  		  for ( i = 1; i < ROWS; i++)
		  		  {
		  					holdarrayg[i] = arrayg[0] + i * COLUMNS;
		  		  }

		setarray(&arrayg[0][0], &resultarr[0][0],&holdarrayg[0][0]);
		/*Enter the Menu Loop */
		MainLoop(&arrayg[0][0], &resultarr[0][0], &holdarrayg[0][0]);

		//free the array
		free((void *)arrayg[0]);
		free((void *)arrayg);

		free((void *)resultarr[0]);
		free((void *)resultarr);


		free((void *)holdarrayg[0]);
		free((void *)holdarrayg);

		exit(0);
}
