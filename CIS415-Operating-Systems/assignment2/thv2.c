/*
	Garett Roberts
	groberts
	This is all my work, except for previous mentioned help from thv1
*/


#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "p1fxns.h"
#define BUFF_SIZE 100

int setsignal= 0;


void
set_signal(){

	setsignal = 1;
}

int
main(int argc, char *argv[])
{
	char *errbuff;
	char *command[BUFF_SIZE] = {'\0'};
	char **temp;
	int tempargc, status, position, charpos, nprocesses, nprocessors, i;

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
		temp[i] = malloc(sizeof(char));
		if(temp[i] == NULL){
			errbuff = "malloc() failed";
			p1perror(2,errbuff);
			_exit(EXIT_FAILURE);
		}
	}

	if(argc <= 1){
			errbuff = "usage: ./thv2 [--number=<nprocesses>] [--proccessors=<nproccessors>] --command='command'\n"; 
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
			
			if(nprocesses > 100){
				errbuff = "nprocesses has to be less than 100\n";
				p1putstr(2,errbuff);
				_exit(EXIT_FAILURE);
			}

		}else if(p1strneq(argv[position], "--processors", 12) != 0){

			charpos = p1strchr(argv[position], '=') + 1;
			nprocessors = p1atoi(argv[position] + charpos);
			
			if(nprocessors > 100){
				errbuff = "nprocessors has to be less than 100\n";
				p1putstr(2,errbuff);
				_exit(EXIT_FAILURE);
			}

		}else{	
			errbuff = "usage: ./thv2 [--number=<nprocesses>] [--proccessors=<nproccessors>] --command='command'\n"; 
			p1putstr(2, errbuff);
			_exit(EXIT_FAILURE);
		}
		argc--;
		position++;
		
	}


	if(nprocesses == -1 && (getenv("TH_NPROCESSES")) == NULL){
		errbuff = "TH_NPROCCESSES NOT SET\n";
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

        pid_t child[BUFF_SIZE];

	signal(SIGUSR1,set_signal);	

	for(i = 0; i < nprocesses; i++){
		switch(child[i] = fork()){
			case 0:
				while(!setsignal){
					sleep(1);
				};
				if(execvp(command[0],command) == -1){
					errbuff = "exevp() failed";
                                        p1perror(2,errbuff);
                                        _exit(EXIT_FAILURE);

				}
				break;
			case -1:	
				errbuff = "fork() failed";
				p1perror(2,errbuff);
				_exit(EXIT_FAILURE);
			
			default:
				if(gettimeofday(&starttime, NULL) == -1){
					errbuff = "gettimeofday() failed";
					p1putstr(2, errbuff);
					_exit(EXIT_FAILURE);
				}
				kill(child[i], SIGUSR1);
				kill(child[i], SIGSTOP);
				kill(child[i], SIGCONT);
				child[i] = waitpid(child[i],&status, 0);
				if(child[i] == -1){
					errbuff = "waitpid() failed";
					p1perror(2,errbuff);
					_exit(EXIT_FAILURE);
				}
		}
	}
	
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
	

	_exit(EXIT_SUCCESS);
}
