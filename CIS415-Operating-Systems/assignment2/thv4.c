/*
	Garett Roberts
	groberts
	This is my own authorship discussed with Kenny Smith, Elizabeth Olson, Randy Chen, Howard Lin, and Chris Brooks with the printing of proc
*/
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "p1fxns.h"

#define BUFF_SIZE 1024

typedef struct node Node;
typedef struct queue Queue;

void procexe(pid_t pid);
void procio(pid_t pid);
void procmem(pid_t pid);
void procinfo(pid_t pid);


int setsignal      = 0;
int child_dead     = 0;
int processors_    = 0;
int dead_size      = 0;
Queue *queue;      
Queue *buffqueue; 
pid_t *dead_children;

struct node{
	int status;
	pid_t pid;
	Node *next;
};

typedef struct queue{
	Node *tail;
	Node *head;
	int size;
}Queue;

Queue*
queue_create()
{
	Queue *newqueue;
	newqueue = (Queue *)malloc(sizeof(Queue));
	if(newqueue == NULL){
		return NULL;
	}

	newqueue->head = NULL;
	newqueue->tail = NULL; 
	newqueue->size = 0;
	return newqueue;

}	

void
enqueue(Queue *queue, pid_t childpid, int status)
{
	Node *newnode = (Node *)malloc(sizeof(Node));
	if(newnode == NULL)
		return;

	newnode->pid    = childpid;
	newnode->status = status;
	
	if(queue->head == NULL){
		queue->head = newnode;
		queue->tail = newnode;
	} else {
	queue->tail->next      = newnode;
	queue->tail            = newnode;
	queue->tail->next      = NULL;
	}

	queue->size = queue->size + 1;           
} 

Node*
dequeue(Queue *queue)
{
	Node *tempnode;

	if(queue->head == NULL){
		return NULL;
	}
	
	tempnode    = queue->head;
	queue->head = queue->head->next;
	queue->size = queue->size - 1;
	return tempnode;
}			

int
queue_empty(Queue *queue)
{
	if(queue->head == NULL){
		return 1;
	}
	return 0;
}

void
set_signal()
{
	setsignal = 1;
}

int children_dead = 0;

void
alarm_handl()
{	
	int i;
	for(i = 0; i < processors_; i++){
		if(!queue_empty(queue)){
			Node *tempnode = dequeue(queue);
			if(tempnode->status == 0){
				tempnode->status = 1;
				kill(tempnode->pid,SIGUSR1);
			}
			else if(tempnode->status == 1){
				kill(tempnode->pid,SIGCONT);
			}
			enqueue(buffqueue,tempnode->pid,tempnode->status);	
			free(tempnode);
		}
	}
	int q;
	for(i = 0; i < buffqueue->size-1; i++){
		int wentoff = 0;
		Node *tempnode = dequeue(buffqueue);
		kill(tempnode->pid,SIGSTOP);
		for(q = 0; q < children_dead; q++){
			if(dead_children[q] == tempnode->pid){
				free(tempnode);
				wentoff = 1;
			}
		}
		if(!wentoff){
			if(kill(tempnode->pid,0) >= 0)
				procinfo(tempnode->pid);
			enqueue(queue,tempnode->pid,1);
			free(tempnode);
		}
	}
}


void
sigchild()
{
	int status;
	pid_t pid;
	children_dead = 0;	

	while((pid = waitpid(-1,&status,WNOHANG)) > 0){
		if(WIFEXITED(status)){
			dead_children[children_dead] = pid;
			children_dead++;
		}
	}
}

void
procio(pid_t pid)
{
	char *errbuff;
	char readbuff[BUFF_SIZE]     = {'\0'};
	char writebuff[BUFF_SIZE]    = {'\0'};
	char accessstring[BUFF_SIZE] = {'\0'}; 
	char pidstring[BUFF_SIZE]    = {'\0'};
	int fd, i;	

	p1strcat(accessstring,"/proc/");
	p1itoa(pid,pidstring);
	p1strcat(accessstring,pidstring);
	p1strcat(accessstring,"/io");
	
	if((fd = open(accessstring,O_RDONLY)) == -1){
		errbuff = "open() failed";
		p1perror(2,errbuff);
		_exit(EXIT_FAILURE);
	}
	
	for(i = 0; i < 4; i++){		
		if(p1getline(fd,readbuff,BUFF_SIZE) <= 0){
			errbuff = "p1getline() could not get line in proc";
			p1perror(2,errbuff);
			_exit(EXIT_FAILURE);
		}
	}
	
	if(p1getline(fd,readbuff,BUFF_SIZE) <= 0){
		errbuff = "p1getline() could not get line in proc";
		p1perror(2,errbuff);
		_exit(EXIT_FAILURE);
	}
	
	if(p1getline(fd,writebuff,BUFF_SIZE) <= 0){
		errbuff = "p1getline() could not get line in proc";
		p1perror(2,errbuff);	
		_exit(EXIT_FAILURE);
	}
	
	p1putstr(1,"\n---Proc I/O---(pid:");
	p1putstr(1,pidstring);
	p1putstr(1,")\n");
	p1putstr(1,readbuff);
	p1putstr(1,writebuff);
	p1putstr(1,"--------");

	close(fd);
}

void
procexe(pid_t pid)
{
	int fd, i;	
	char *errbuff;
	char timebuff[BUFF_SIZE]     = {'\0'};
	char pidstring[BUFF_SIZE]    = {'\0'};
	char accessstring[BUFF_SIZE] = {'\0'}; 
		
	p1strcat(accessstring,"/proc/");
	p1itoa(pid,pidstring);
	p1strcat(accessstring,pidstring);
	p1strcat(accessstring,"/sched");

	if((fd = open(accessstring,O_RDONLY)) == -1){
		errbuff = "open() failed";
		p1perror(2,errbuff);
		_exit(EXIT_FAILURE);
	}

	
	for(i = 0; i < 5; i++){	
		if(p1getline(fd,timebuff,BUFF_SIZE) <= 0){
			errbuff = "p1getline() could not get line in proc";
			p1perror(2,errbuff);
			_exit(EXIT_FAILURE);
		}
	}
	
	p1putstr(1,"\n---Execution Time---(pid:");
	p1putstr(1,pidstring);
	p1putstr(1,")\n");
	p1putstr(1,timebuff);
	p1putstr(1,"------\n");
	
	close(fd);
}

void
procmem(pid_t pid)
{
	int fd, i;	
	char *errbuff;
	char membuff[BUFF_SIZE]     = {'\0'};
	char pidstring[BUFF_SIZE]    = {'\0'};
	char accessstring[BUFF_SIZE] = {'\0'}; 
		
	p1strcat(accessstring,"/proc/");
	p1itoa(pid,pidstring);
	p1strcat(accessstring,pidstring);
	p1strcat(accessstring,"/smaps");

	
	if((fd = open(accessstring,O_RDONLY)) == -1){
		errbuff = "open() failed";
		p1perror(2,errbuff);
		_exit(EXIT_FAILURE);
	}
	
	int flag    = 0;
	int charloc = 0;
	char buff[BUFF_SIZE];
	while(!flag){
		charloc = 0;
		if(p1getline(fd,membuff,BUFF_SIZE) <= 0){
			errbuff = "p1getline() could not get line in proc";
			p1perror(2,errbuff);
			_exit(EXIT_FAILURE);
		}	
		while((charloc = p1getword(membuff,charloc,buff)) != -1){
			if(p1strneq(buff,"[stack]",7) == 1)
				flag = 1;
		}
	}
	if(p1getline(fd,membuff,BUFF_SIZE) <= 0){
		errbuff = "p1getline() could not get line in proc";
		p1perror(2,errbuff);
		_exit(EXIT_FAILURE);
	}
	p1putstr(1,"\n---Memory Usage---(pid:");
	p1putstr(1,")");
	p1putstr(1,pidstring);
	p1putstr(1,"\nHeap Usage\n");
	p1putstr(1,membuff);
	p1putstr(1,"\n------\n");
	
	close(fd);
}

void
procinfo(pid_t pid)
{
	procio(pid);
	procexe(pid);
	procmem(pid);
}

int
main(int argc, char *argv[])
{
	char *errbuff;
	char *command[BUFF_SIZE] = {'\0'};
	char **temp;
	int tempargc, position, charpos, nprocesses, nprocessors, i;
	queue     = queue_create();
	buffqueue = queue_create();

	errbuff     = NULL;
	position    = 1;
	charpos     = 0;
	nprocesses  = -1;
	nprocessors = -1;
	tempargc    = argc;

	temp = (char **)malloc(sizeof(char*)*tempargc);
	if(temp == NULL){
		errbuff = "malloc() failed";
		p1perror(2,errbuff);
		_exit(EXIT_FAILURE);
	}

	for(i = 0; i < tempargc; i++){
		temp[i] = malloc(sizeof(*command));
		if(temp[i] == NULL){
			errbuff = "malloc() failed";
			p1perror(2,errbuff);
			_exit(EXIT_FAILURE);
		}
	}

	if(argc <= 1){
			errbuff = "usage: ./thv3 [--number=<nprocesses>] [--processors=<nproccessors>] --command='command'\n"; 
			p1putstr(2, errbuff);
			_exit(EXIT_FAILURE);
	}	
	
	while(argc > 1){
		
		if(p1strneq(argv[position], "--command", 9) != 0){
			i = 0;
				
			charpos = p1strchr(argv[position],'=') + 1;
			while((charpos = p1getword(argv[position], charpos, temp[i])) != -1){
				command[i] = temp[i];
				i++;
			}

			command[i] = NULL;
				
		}else if(p1strneq(argv[position], "--number", 8) != 0){
	
			charpos = p1strchr(argv[position], '=') + 1;
			nprocesses = p1atoi(argv[position] + charpos);
			
			if(nprocesses > 100000){
				errbuff = "nprocesses has to be less than 100000\n";
				p1putstr(2,errbuff);
				_exit(EXIT_FAILURE);
			}

		}else if(p1strneq(argv[position], "--processors", 12) != 0){

			charpos = p1strchr(argv[position], '=') + 1;
			nprocessors = p1atoi(argv[position] + charpos);
			processors_ = nprocessors;
			if(nprocessors > 100){
				errbuff = "nprocessors has to be less than 100\n";
				p1putstr(2,errbuff);
				_exit(EXIT_FAILURE);
			}

		}else{	
			errbuff = "usage: ./thv3 [--number=<nprocesses>] [--processors=<nproccessors>] --command='command'\n"; 
			p1putstr(2, errbuff);
			_exit(EXIT_FAILURE);
		}
		argc--;
		position++;
		
	}


	if(nprocesses == -1 && (getenv("TH_NPROCESSES")) == NULL){
		errbuff = "TH_NPROCESSES NOT SET\n";
		p1putstr(2, errbuff);
		_exit(EXIT_FAILURE);

	}else if(nprocesses == -1){
		nprocesses = atoi(getenv("TH_NPROCESSES"));
	}

	if(nprocessors == -1 && (getenv("TH_NPROCESSORS")) == NULL){
		errbuff = "TH_NPROCESSORS NOT SET\n";
		p1putstr(2, errbuff);	
		_exit(EXIT_FAILURE);

	}else if(nprocessors == -1){
		nprocessors = atoi(getenv("TH_NPROCESSORS"));
	}

	struct timeval starttime,endtime;
	struct itimerval runtime;
        pid_t child[BUFF_SIZE];

	dead_children = (pid_t *)malloc(sizeof(pid_t)*nprocesses);
	if(dead_children == NULL){
		errbuff = "malloc() failed";
		p1perror(2,errbuff);
		_exit(EXIT_FAILURE);
	}

	runtime.it_value.tv_sec     = 0;
	runtime.it_value.tv_usec    = 250000;
	runtime.it_interval         = runtime.it_value;
	
	if(signal(SIGUSR1,set_signal) == SIG_ERR){
		errbuff = "signal() failed";
		p1perror(2,errbuff);
		_exit(EXIT_FAILURE);
	}
	
	if(signal(SIGALRM,alarm_handl) == SIG_ERR){
		errbuff = "signal() failed";
		p1perror(2,errbuff);
		_exit(EXIT_FAILURE);
	}

	if(signal(SIGCHLD,sigchild) == SIG_ERR){
		errbuff = "signal() failed";
		p1perror(2,errbuff);
		_exit(EXIT_FAILURE);
	}

	for(i = 0; i < nprocesses; i++){
		switch(child[i] = fork()){
			case 0:
				while(!setsignal){
					pause();
				};
				if(execvp(command[0],command) == -1){	
					errbuff = "exevp() failed";
                                        p1perror(2,errbuff);
                                        _exit(EXIT_FAILURE);

				}
				_exit(EXIT_SUCCESS);
				break;
			case -1:	
				errbuff = "fork() failed";
				p1perror(2,errbuff);
				_exit(EXIT_FAILURE);
		}
	}
	for(i = 0; i < nprocesses; i++){
		enqueue(queue,child[i],0);
	}

	if(gettimeofday(&starttime, NULL) == -1){
		errbuff = "gettimeofday() failed";
		p1putstr(2, errbuff);
		_exit(EXIT_FAILURE);
	}

	if(setitimer(ITIMER_REAL,&runtime,NULL) != 0){
		errbuff = "setitimer() failed";
		p1perror(2,errbuff);
		_exit(EXIT_FAILURE);
	}
	
	for(i = 0; i < nprocesses; i++){
		wait(child+i);
	}
	
	while(!queue_empty(queue)){
		free(dequeue(queue));
	}
	
	while(!queue_empty(buffqueue)){
		free(dequeue(buffqueue));
	}		

	free(queue);
	free(buffqueue);
	
	if(gettimeofday(&endtime, NULL) == -1){
		errbuff = "gettimeofday() failed";
		p1putstr(2, errbuff);
		_exit(EXIT_FAILURE);
	}

	float totaltime;
	totaltime = (((endtime.tv_sec - starttime.tv_sec)*1000000L + endtime.tv_usec) - starttime.tv_usec)/1000000.0;
	
	unsigned int whole   = (unsigned int)totaltime;
	unsigned int decimal = (unsigned int)((totaltime - whole) * 1000);

	p1putstr(1,"Time elapsed to execute ");
	p1putint(1,nprocesses);
	p1putstr(1," copies of ");
	p1putstr(1,*command);
	p1putstr(1, " on ");
	p1putint(1,nprocessors);
	p1putstr(1," processors is ");
	p1putint(1,whole);
	p1putstr(1,".");
	if(decimal < 10){
		p1putstr(1,"00");
		p1putint(1,decimal);
	}else if(decimal < 100){
		p1putstr(1, "0");
		p1putint(1,decimal);
	}
	p1putint(1,decimal);
	p1putstr(1," sec\n");
	
	for(i = 0; i < tempargc; i++){
		free(temp[i]);
	}
	free(temp);
	free(dead_children);
	_exit(EXIT_SUCCESS);
}
