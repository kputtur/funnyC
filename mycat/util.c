/*
 * util.c
 *
 *  Created on: Mar 1, 2010
 *      Author: kiran
 */

#include "mycat.h"

char * doCpyBuff(char *dest, const char *src)
{
  /*keeping it in register for faster operation */
  register char *d = dest;
  register const char *s = src;

  do
  {
    *d++ = *s;
  }
  while (*s++ != '\0');
  /* return address of destination - 1 because
   * you incremented in the loop
   */
  return d - 1;
}

/* find out the length of buffer or char ptr */

int mesglength(char *mesg)
{
	int i = 0;
	while ( mesg[i] != '\0')
	{
	  i++;
	}
         return i;
}



