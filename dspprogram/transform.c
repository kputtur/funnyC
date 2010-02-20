/*
 * transform.c
 *
 *  Created on: Feb 17, 2010
 *      Author: kiran
 */
#include "module.h"

int avgtransform(int *arrayp, int rows, int columns, int posx, int posy)
{
		int count = 0, sum = 0;
		int lcindex, rcindex,brindex, urindex;
	   int trdrindex, trdcindex, brdrindex, brdcindex;
	   int tldrindex, tldcindex, bldcindex, bldrindex;
	    int total;
	    float fvalue;
	   	int rindex = posx;
		int cindex = posy;
		//print neighbors of corner "0";
		//left step
		 lcindex = cindex - 1;
		if ( lcindex >= 0 && lcindex < columns ) {
			count++;
			sum += arrayp[rindex * columns + lcindex];
			total = rindex * columns + lcindex;
			//printf("\n iam here left step total = %d, sum=%d \n", total, sum);
		}
        //right step
		  rcindex = cindex + 1;
		  if ( rcindex >= 0 && rcindex < columns) {
			  count++;
			  sum += arrayp[rindex * columns + rcindex];
			  total = rindex * columns + rcindex;
			  //printf("\niam here right step total=%d, sum=%d\n", total, sum);
		  }
		 //top step
		  urindex = rindex - 1;

		  if (urindex >= 0 && rindex < rows)
		  {
			  count++;
			  sum += arrayp[urindex * columns + cindex];
			  total = urindex * columns + cindex;
			 // printf("\niam here top step total=%d, sum=%d \n", total, sum);
		  }

		  //bottom step
		  brindex = rindex + 1;
		  if ( brindex >= 0 && brindex < rows)
		  {
			  count++;
			  sum += arrayp[brindex * columns + cindex];
			  total = brindex * columns + cindex;
			//  printf("\n i am here bottom step total=%d, sum=%d\n", total, sum);
		  }

		  //diagnol top right
		  trdrindex = rindex - 1;
		  trdcindex = cindex - 1;

		  if ( (trdrindex >= 0 && trdrindex < rows) && (trdcindex >=0 && trdcindex < columns)) {
			  count++;
			  sum += arrayp[trdrindex * columns + trdcindex];
			  total = trdrindex * columns + trdcindex;
			 // printf("\n I am in diagnoal top right total=%d, sum=%d\n", total, sum);
		  }

		//diagnol bottom right
		   brdrindex = rindex + 1;
		   brdcindex = cindex + 1;

		   if ( (brdrindex >= 0 && brdrindex < rows) && (brdcindex >=0 && brdcindex < columns)) {
		   			  count++;
		   			  sum += arrayp[brdrindex * columns + brdcindex];
		   			  total = brdrindex * columns + brdcindex;
		   		//	  printf("\n I am in diagnoal bottom right total=%d, sum=%d\n", total,sum);
		   		  }

		  //diagnol left top
		   tldrindex = rindex - 1;
		   tldcindex = cindex + 1;
		   if ( (tldrindex >=0 && tldrindex < rows) && ( tldcindex >= 0 && tldcindex < columns)) {
			   count++;
			   sum += arrayp[tldrindex * columns + tldcindex];
			   total = tldrindex * columns + tldcindex;
			 //  printf("\n I am in diagnoal left top total = %d, sum=%d\n", total,sum);
		   }

         //diagnol left bottom
		   bldrindex = rindex + 1;
		   bldcindex = cindex - 1;

		   if ( (bldcindex >=0 && bldcindex < columns) && ( bldrindex >=0 && bldrindex <rows))
		   {
			   count++;
			   sum += arrayp[bldrindex * columns + bldcindex];
			   total = bldrindex * columns + bldcindex;
			 //  printf("\n I am in diagnoal left bottom total=%d, sum=%d\n", total,sum);
		   }


		  sum += arrayp[rindex * columns + cindex];
		 // printf("\n Total sum value is %d \n",sum);
		  count++;
		  fvalue = sum / count;
		  total = (int)fvalue;

		 // printf("The total sum is %d \n", total);
		  return total;



}

int negtransform(int val)
{
		int x = val - 31;
		return abs(x);
}

void applytransform(int *arrayp2)
{
		int i, j;
		int localresult[ROWS][COLUMNS];
		if ( ctransform == AVGTRANSFORM)
		{
		printf("\n Applying Average Transformation \n");
		for ( i = 0; i<ROWS; i++)
		{
			for ( j = 0; j<COLUMNS; j++)
			{
				localresult[i][j] = avgtransform(arrayp2, ROWS,COLUMNS,i,j);
			}
		}
		}
		else if ( ctransform == NEGTRANSFORM)
		{
			printf("\n Applying Negative Transformation \n");
			for ( i = 0; i<ROWS; i++)
					{
						for ( j = 0; j<COLUMNS; j++)
						{
						   localresult[i][j] = negtransform(arrayp2[i * COLUMNS + j]);
						}
					}

		}
		else if ( ctransform == NEWTRANSFORM)
		{
			  printf("\n Applying stub  Transformation \n");
				stubtrans1(1);
				return;
		}
		else if ( ctransform == NEWTRAN1)
		{
			printf("\n Applying stub  Transformation \n");
			   stubtrans1(2);
			   return;
		}
		else if ( ctransform == NEWTRAN2)
		{
			printf("\n Applying stub  Transformation \n");
				stubtrans1(3);
				return;
		}
		else
		{
			printf("\n No transformation chosen \n");
			return;
		}

		copyarray(arrayp2, &localresult[0][0]);
		printarray(arrayp2);
}

void stubtrans1(int val)
{
		printf("\n\n\n");
		printf("\n ------------PLACE HOLDER FOR FUTURE TRANSFORMS %d-----\n", val);

}
