#include "color.h"

void
Color::Execute(){
	 if (r <0 || g <0 || b<0){
        char msg[1024];
        sprintf(msg, "%s: Red Green, and/or Blue set to a number sub zero %d,%d,%d",SourceName(),r,g,b);
        DataFlowException e(SourceName(), msg);
        throw e;
    }
	 if (h<=0 || w<=0){
        char msg[1024];
        sprintf(msg, "%s: Height and width given <= 0 %d,%d",SourceName(),h,w);
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    imageout.SetSize(h,w);
	Pixel *buffer = imageout.GetPixels();
    for(int i=0;i<imageout.GetHeight();i++){
    	for(int j=0;j<imageout.GetWidth();j++){
    		buffer[i*imageout.GetWidth()+j].red = (unsigned char)r;
    		buffer[i*imageout.GetWidth()+j].green = (unsigned char)g;
    		buffer[i*imageout.GetWidth()+j].blue = (unsigned char)b;
    	}
    }
}