#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<errno.h>

struct primelist {
	unsigned long long int data;
	struct primelist *next;
	struct primelist *prev;
     };

struct primelist *head, *tail;

void insert_at_tail(struct primelist **tailRef, unsigned long long int data);
void insert_at_head(struct primelist **headRef, unsigned long long int data);
void remove_node(struct primelist **headRef, unsigned long long int data);
struct primelist * find_next_prime(struct primelist *lnode, unsigned long long int prime);
unsigned long long int square(unsigned long long int data);

int  main(void)
{ 
  int i, count = 0,exit_code = 0;
  unsigned long long int input;	
  unsigned long long int u_input;
  unsigned long long int temp;
  unsigned long long int firstprime = 2;
  struct primelist *plist = NULL;
  struct primelist *head = plist;
  struct primelist *current = NULL;
  char buff[25];
  char *end_ptr;	

for ( ; ;)
	{
	  printf("Enter int max val, return to quit: ");
	  fflush(stdout);
	  fgets(buff, sizeof buff, stdin);
	
	   if ( buff[0] == '\n')
	    {
		exit_code = 1;
		break;
	     }
	
	   errno = 0;

	   u_input = strtoull(buff, &end_ptr, 0);
	   
	   if ( ERANGE == errno)
	   {
	     printf("MAX value cannot exceed 2^64-1 sorry \n");
	   }
	   else if ( u_input > ULLONG_MAX)
	   {
	     printf("MAX VALUE %llu cannot exceed 2^64-1 sorry\n", u_input);
	    }

	  else if ( end_ptr == buff)
	   {
		printf("not a valid numeric input \n");
	   }
	
	   else if ( u_input <= 2)
	   {
	     printf("%llu is too small,[enter > 2 value]\n", u_input);
	   }
	   else
	   {
          input = u_input;
	  printf("\nPrime numbers will be calculated from 2 to %llu\n", input);
	  break;
           }
}


			/*insert firstprime in head */
			insert_at_head(&head, firstprime);
			struct primelist *nextprime = head ;
			struct primelist *tail = head;
		        plist = head;
		        for ( i = firstprime; i < input; i++)
			 {
			    if ( (i% firstprime) != 0)
			    {
			      insert_at_tail(&tail, i);
			      tail = tail->next;
			     }
			  }
			/* now keep spinning the wheel untill u get all prime */
	while ((square(nextprime->data)) < input) 
        {
	  temp = nextprime->data;
	  nextprime = find_next_prime(plist, temp);
	  for(current = nextprime->next; current != NULL; current=current->next)
	   {
	     if( (current->data % nextprime->data) == 0)
	      {
	       remove_node(&head, current->data);
		 }
	     
	   }
	}
 
	/* print the found primenumbers */
	for ( current = head; current != NULL; current=current->next)
	{
	  count++;
	  fprintf(stdout, "%llu \t", current->data);
  
	   if ( (count == 10) || ( count % 10 == 0))
          {
	    fprintf(stdout, "\n");
	   }

         }

fprintf(stdout, "\n ********** Found %d prime numbers ********\n", count);
return exit_code;	
}

void insert_at_head(struct primelist** headRef, unsigned long long int data) {
	struct primelist* newNode = malloc(sizeof(struct primelist));
	
	newNode->data = data;
	newNode->next = *headRef;
	newNode->prev = NULL;
	*headRef = newNode;
}

void insert_at_tail(struct primelist** tailRef, unsigned long long int data) {
	struct primelist* newNode = malloc(sizeof(struct primelist));
	
	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = *tailRef;
	(*tailRef)->next = newNode;	
}

void remove_node(struct primelist** headRef, unsigned long long int searchvalue)
{
	/* can't be first node so skip coding for first node possibility */
        struct primelist* temp = (*headRef)->next;
	
        for(; temp && temp->data != searchvalue; temp=temp->next);

	if ( temp != NULL) 
	{
	  temp->prev->next = temp->next;
	   if ( temp->next)
		{
		  temp->next->prev = temp->prev;
		} 	
	   free(temp);
	  }
}

struct primelist * find_next_prime(struct primelist *primeRef, unsigned long long int prime)
{
	struct primelist * temp = NULL;
	
	 for(temp = primeRef; temp && temp->data != prime; temp = temp->next);

	 if ( temp->next != NULL)
	 {
		temp=temp->next;
	  }
	return temp;
} 

unsigned long long int square( unsigned long long int data)
{
	unsigned long long int value = (data * data);
	return value;
}
	 
