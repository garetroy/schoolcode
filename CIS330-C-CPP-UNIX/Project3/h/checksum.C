#include "checksum.h"

void 
CheckSum::OutputCheckSum(const char * filename){
	unsigned char newred,newgreen,newblue;
	newblue=newred=newgreen=0;
	int error;
	int ii1w = imagein1->GetWidth(); 
	int ii1h = imagein1->GetHeight();
	FILE* outputfile = NULL;
	if (outputfile != NULL){
		char msg[1024];
		sprintf(msg, "%s: Outputfile pointer not initialized as NULL", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	if (imagein1 == NULL){
		char msg[1024];
		sprintf(msg, "%s: No input set!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	for(int i=0; i<ii1h;i++){
		for(int j=0; j<ii1w;j++){
			newred += imagein1->GetPixel(i,j).red;
			newgreen += imagein1->GetPixel(i,j).green;
			newblue += imagein1->GetPixel(i,j).blue;
		}
	}
	outputfile = fopen(filename, "w");
	if (outputfile == NULL){
        char msg[1024];
        sprintf(msg, "%s: File could not be opened with filename: %s Reason: %s",SinkName(),filename,strerror(errno));
        DataFlowException e(SinkName(), msg);
        throw e;
    }
	error = fprintf(outputfile, "CHECKSUM: %d, %d, %d\n", newred, newgreen, newblue);
    if (error < 0){
        char msg[1024];
        sprintf(msg, "%s: fprintf failed. Reason: %s",SinkName(),strerror(errno));
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    try{
        fclose(outputfile);
    } catch(FILE outputfile){
        char msg[1024];
        sprintf(msg, "%s: File did not successfully close", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
}