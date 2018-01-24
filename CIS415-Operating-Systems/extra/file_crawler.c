#define _DEFAULT_SOURCE 1	/* enables macros to test type of directory entry */

#include <sys/types.h>
#include <dirent.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "linkedlist.h"
#include "treeset.h"
#include "re.h"

pthread_cond_t queue_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t queue_mtx = PTHREAD_MUTEX_INITIALIZER;
LinkedList *crawlerqueue;
char **matched_files;
pthread_t threadarray[32];
int thread_count;
int nthreads;
RegExp *globalreg;

/*
 * routine to convert bash pattern to regex pattern
 * 
 * e.g. if bashpat is "*.c", pattern generated is "^.*\.c$"
 *      if bashpat is "a.*", pattern generated is "^a\..*$"
 *
 * i.e. '*' is converted to ".*"
 *      '.' is converted to "\."
 *      '?' is converted to "."
 *      '^' is put at the beginning of the regex pattern
 *      '$' is put at the end of the regex pattern
 *
 * assumes 'pattern' is large enough to hold the regular expression
 */

void*
thread_func()
{
	char *dire;
	DIR *dd;
	struct dirent *dent; 

	while(1){
		thread_count++;
		pthread_mutex_lock(&queue_mtx);
	        ll_remove(crawlerqueue, 0, (void **)&dire);
		dd = opendir(dire);
		while((dent = readdir(dd)) != NULL){
      			if (strcmp(".", dent->d_name) == 0 || strcmp("..", dent->d_name) == 0)
         			continue;
			if(dent->d_type & DT_DIR){
				char directorystring[1024] = {'\0'};
				char *temphold = malloc(sizeof(char) * 1024);
				sprintf(directorystring, "%s/%s", dire, dent->d_name);
				strcpy(temphold,directorystring);
				ll_addLast(crawlerqueue,temphold);
			}else if(re_match(globalreg, dent->d_name)){
				fprintf(stderr, "%s/%s\n", dire, dent->d_name);
			}
		}

		closedir(dd);	
		pthread_mutex_unlock(&queue_mtx);			
		thread_count--;
		while (ll_size(crawlerqueue) == 0){
			pthread_cond_wait(&queue_cond,&queue_mtx);
		}
		pthread_cond_broadcast(&queue_cond);
	}
	return NULL;	
}	

static void cvtPattern(char pattern[], const char *bashpat) {
   char *p = pattern;

   *p++ = '^';
   while (*bashpat != '\0') {
      switch (*bashpat) {
      case '*':
         *p++ = '.';
	 *p++ = '*';
	 break;
      case '.':
         *p++ = '\\';
	 *p++ = '.';
	 break;
      case '?':
         *p++ = '.';
	 break;
      default:
         *p++ = *bashpat;
      }
      bashpat++;
   }
   *p++ = '$';
   *p = '\0';
}

static int processDirectory() {
	int i;

	char currdir[10] = ".";
	ll_addLast(crawlerqueue,currdir);
	for(i = 0; nthreads > i; i++){
		pthread_create(&(threadarray[i]), NULL, &thread_func, NULL);
	}
	while(1){
		if(thread_count == nthreads)
			break;
	}
	return 1;
}

int main(int argc, char *argv[]) {
   char pattern[4096];
   RegExp *reg;
   thread_count = 0;
   crawlerqueue  = ll_create();

   if (argc < 2) {
      fprintf(stderr, "Usage: ./fileCrawler pattern [dir] ...\n");
      return -1;
   }
   /*
    * convert bash expression to regular expression and compile
    */
	 
   if(getenv("CRAWLER_THREADS") == NULL){
	nthreads = 2;	
   }else{
	nthreads = atoi(getenv("CRAWLER_THREADS"));
   }

   cvtPattern(pattern, argv[1]);
   if ((reg = re_create()) == NULL) {
      fprintf(stderr, "Error creating Regular Expression Instance\n");
      return -1;
   }
   if (! re_compile(reg, pattern)) {
      char eb[4096];
      re_status(reg, eb, sizeof eb);
      fprintf(stderr, "Compile error - pattern: `%s', error message: `%s'\n",
              pattern, eb);
      re_destroy(reg);
      return -1;
   }

   globalreg = reg;

   processDirectory();
   
   if (crawlerqueue != NULL)
   	ll_destroy(crawlerqueue, free);

   re_destroy(reg);
   return 0;
}
