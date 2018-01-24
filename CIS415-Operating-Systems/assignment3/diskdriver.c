/*
	Garett Roberts
	groberts
	This is my own work, the implementation was heavly discussed with Howard Lin and Joe McLaughin.
*/ 
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "p1fxns.h"
#include "freesectordescriptorstore_full.h"
#include "diskdevice_full.h"
#include "BoundedBuffer.h"
#include "diskdriver.h"
#include "sectordescriptorcreator.h"

#define V_SIZE   30

typedef struct voucher{

	int              type;
	int              status;
	int		 finished;
	pthread_cond_t   condition;
	pthread_mutex_t  mtx;
	SectorDescriptor *sectordescriptor;

}Voucher;

Voucher                   voucherarray[V_SIZE];
pthread_t                 t1;
pthread_t                 t2;
DiskDevice 		  *newdd;
BoundedBuffer             *readbuffer;
BoundedBuffer 	          *writebuffer;
BoundedBuffer		  *freearray;
FreeSectorDescriptorStore *store;

void *ws()
{
	Voucher *v;

	while(1){
		
		v = (Voucher *) blockingReadBB(writebuffer);		

		pthread_mutex_lock(&v->mtx);

		v->status   = write_sector(newdd, v->sectordescriptor);
		v->finished = 1;
		pthread_cond_signal(&v->condition);
		blocking_put_sd(store, v->sectordescriptor);
	
		pthread_mutex_unlock(&v->mtx);	
	}
}

void *rs()
{
	Voucher *v;

	while(1){

		v = (Voucher *) blockingReadBB(readbuffer);
		
		pthread_mutex_lock(&v->mtx);
		
		v->status   = read_sector(newdd, v->sectordescriptor);
		v->finished = 1;		
		
		pthread_cond_signal(&v->condition);
		pthread_mutex_unlock(&v->mtx);
	}
}

void init_disk_driver(DiskDevice *dd, void *mem_start, unsigned long mem_length, FreeSectorDescriptorStore **fsds)
{
	int i                    = 0;
	char *errbuff 	         = '\0';
	*fsds                    = create_fsds();
	
	create_free_sector_descriptors(*fsds, mem_start, mem_length);
	
	store                    = *fsds;
	newdd 			 = dd;
	readbuffer    		 = createBB(V_SIZE * sizeof(Voucher *));
	writebuffer   		 = createBB(V_SIZE * sizeof(Voucher *));
	freearray                = createBB(V_SIZE * sizeof(Voucher *));	

	for(i = 0; i < V_SIZE; i++){	
		voucherarray[i].status   = 0;
		voucherarray[i].finished =  0;
		pthread_cond_init(&voucherarray[i].condition, NULL);
		pthread_mutex_init(&voucherarray[i].mtx, NULL);
		blockingWriteBB(freearray,(void *) &voucherarray[i]);
	}	

	if(pthread_create(&t1, NULL, &ws, NULL) != 0){
		errbuff = "pthread_create() failed";
		p1perror(2,errbuff);
		destroy_fsds(*fsds);
		_exit(EXIT_FAILURE);
	}

	if(pthread_create(&t2, NULL, &rs, NULL) != 0){
		errbuff = "pthread_create() failed";
		p1perror(2,errbuff);
		destroy_fsds(*fsds);
		_exit(EXIT_FAILURE);
	}	
}

void blocking_write_sector(SectorDescriptor *sd, Voucher **v)
{
	*v = (Voucher *) blockingReadBB(freearray);	

	(*v)->type             = 1;
	(*v)->sectordescriptor = sd;    

	blockingWriteBB(writebuffer, *v);
}

int nonblocking_write_sector(SectorDescriptor *sd, Voucher **v)
{
	Voucher *vouch;
	vouch = (Voucher *) blockingReadBB(freearray);

	vouch->type             = 1;
	vouch->sectordescriptor = sd;    

	if(nonblockingWriteBB(writebuffer, vouch) == 0){	
		return 0;
	}
	*v = vouch;
	return 1;
}

void blocking_read_sector(SectorDescriptor *sd, Voucher **v)
{
	*v = (Voucher *) blockingReadBB(freearray);

	(*v)->type             = 0;
	(*v)->sectordescriptor = sd;

	blockingWriteBB(readbuffer, *v);
}

int nonblocking_read_sector(SectorDescriptor *sd, Voucher **v)
{	
	Voucher *vouch;
	vouch = (Voucher *) blockingReadBB(freearray);

	vouch->type             = 0;
	vouch->sectordescriptor = sd;

	if(nonblockingWriteBB(readbuffer, vouch) == 0){	
		return 0;
	}
	*v = vouch;
	return 1;
}

int redeem_voucher(Voucher *v, SectorDescriptor **sd)
{
	pthread_mutex_lock(&v->mtx);

	while(v->finished != 1){
		pthread_cond_wait(&v->condition,&v->mtx);
	}

	if(v->status == 1){
		if(v->type == 0)
			*sd = v->sectordescriptor;
	
		v->status   = 0;
		v->finished = 0;
		blockingWriteBB(freearray,v);
		pthread_mutex_unlock(&v->mtx);
		return 1;
	}else{
		if(v->type == 0)
			blocking_put_sd(store, *sd);

		pthread_mutex_unlock(&v->mtx);
		return 0;
	}
}
