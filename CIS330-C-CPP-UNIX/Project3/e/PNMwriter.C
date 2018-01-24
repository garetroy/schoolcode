#include <stdio.h>
#include "PNMwriter.h"
void
PNMwriter::Write(char *filename){
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL){
        printf("File Pointer is NULL");
    }
    fprintf(fp, "%s\n%d %d\n%d\n",imagein1->GetMagicNum(),imagein1->GetWidth(),imagein1->GetHeight(),imagein1->GetMaxVal());
    fwrite(imagein1->GetPixels(),sizeof(Pixel),imagein1->GetWidth()*imagein1->GetHeight(),fp);
    fclose(fp);
}

