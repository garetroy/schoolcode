#include <stdio.h>
#include "PNMwriter.h"
#include "logging.h"
void
PNMwriter::Write(char *filename){
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL){
        char msg[1024];
        sprintf(msg, "%s: File could not be opened with filename:%s",SinkName(),filename);
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    fprintf(fp, "%s\n%d %d\n%d\n",imagein1->GetMagicNum(),imagein1->GetWidth(),imagein1->GetHeight(),imagein1->GetMaxVal());
    fwrite(imagein1->GetPixels(),sizeof(Pixel),imagein1->GetWidth()*imagein1->GetHeight(),fp);
    try{
        fclose(fp);
    } catch(FILE fp){
        char msg[1024];
        sprintf(msg, "%s: File did not successfully close", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
}

