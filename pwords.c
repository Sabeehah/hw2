#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

pthread_t tid[2];

/*void *thread_function(void *);
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int  counter = 0;*/

typedef struct dict {
  char *word;
  int count;
  struct dict *next;
} dict_t;

struct happy {
	dict_t *d;
	char *word;
};

char *
make_word( char *word ) {
  return strcpy( malloc( strlen( word )+1 ), word );
}

dict_t *
make_dict(char *word) {
  dict_t *nd = (dict_t *) malloc( sizeof(dict_t) );
  nd->word = make_word( word );
  nd->count = 1;
  nd->next = NULL;
  return nd;
}

dict_t *
insert_word( happy ) {
  
  //   Insert word into dict or increment count if already there
  //   return pointer to the updated dict
  
  dict_t *nd;
  dict_t *pd = NULL;		// prior to insertion point 
  dict_t *di = d;		// following insertion point
  // Search down list to find if present or point of insertion
  while(di && ( strcmp(word, di->word ) >= 0) ) { 
    if( strcmp( word, di->word ) == 0 ) { 
      di->count++;		// increment count 
      return d;			// return head 
    }
    pd = di;			// advance ptr pair
    di = di->next;
  }
  nd = make_dict(word);		// not found, make entry 
  nd->next = di;		// entry bigger than word or tail 
  if (pd) {
    pd->next = nd;
    return d;			// insert beond head 
  }
  return nd;
}

void print_dict(dict_t *d) {
  while (d) {
    printf("[%d] %s\n", d->count, d->word);
    d = d->next;
  }
}

int
get_word( char *buf, int n, FILE *infile) {
  int inword = 0;
  int c;  
  while( (c = fgetc(infile)) != EOF ) {
    if (inword && !isalpha(c)) {
      buf[inword] = '\0';	// terminate the word string
      return 1;
    } 
    if (isalpha(c)) {
      buf[inword++] = c;
    }
  }
  return 0;			// no more words
}

#define MAXWORD 1024
dict_t *
words( FILE *infile ) {
  dict_t *wd = NULL;
  char wordbuf[MAXWORD];
  while( get_word( wordbuf, MAXWORD, infile ) ) {
    wd = insert_word(wd, wordbuf); // add to dict
  }
  return wd;
}

void *thread_function(void *dummyPtr)
{
   printf("Thread number %ld\n", pthread_self());
   pthread_mutex_lock( &mutex1 );
   counter++;
   pthread_mutex_unlock( &mutex1 );
}

int
main( int argc, char *argv[] ) {
  dict_t *d = NULL;
  FILE *infile = stdin;
  if (argc >= 2) {
    infile = fopen (argv[1],"r");
  }
  if( !infile ) {
    printf("Unable to open %s\n",argv[1]);
    exit( EXIT_FAILURE );
  }

  for(int i = 0; i <= 4; i++){

	
       int pthread_create(&(tid[i]), NULL, insert_word, happy);

  }

  for(int j = 0; j <= 4; j++){

	 pthread_join(tid[j], NULL);

  }

  d = words( infile );
  print_dict( d );
  fclose( infile );
}