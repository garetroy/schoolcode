#include <stdio.h>
#include "PNMwriter.h"
#include "logging.h"
void
PNMwriter::Write(char *filename){
    FILE *fp;
    int error;
    fp = fopen(filename, "wb");
    if (fp == NULL){
        char msg[1024];
        sprintf(msg, "%s: File could not be opened with filename: %s Reason: %s",SinkName(),filename,strerror(errno));
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    error = fprintf(fp, "%s\n%d %d\n%d\n",imagein1->GetMagicNum(),imagein1->GetWidth(),imagein1->GetHeight(),imagein1->GetMaxVal());
    if (error < 0){
        char msg[1024];
        sprintf(msg, "%s: fprintf failed. Reason: %s",SinkName(),strerror(errno));
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    error = fwrite(imagein1->GetPixels(),sizeof(Pixel),imagein1->GetWidth()*imagein1->GetHeight(),fp);
    if (error == sizeof(Pixel)*imagein1->GetWidth()*imagein1->GetHeight()){
        char msg[1024];
        sprintf(msg, "%s: fwrite failed (most likely due to wrong amount written). Reason: %s",SinkName(),strerror(errno));
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    try{
        fclose(fp);
    } catch(FILE fp){
        char msg[1024];
        sprintf(msg, "%s: File did not successfully close", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
}