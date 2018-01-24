#include "filters.h"
#include <stdio.h>
void
Filter::Update(){
	const char* sourcename = SourceName();
	char msg[256];
	sprintf(msg, "%s: about to update input1", sourcename); Logger::LogEvent(msg);
	if(imagein1 != NULL) imagein1->Update();
	if(imagein1 == NULL){
		char msg[1024];
		sprintf(msg, "%s: No input!", sourcename);
		DataFlowException e(sourcename, msg);
		throw e;

	}
	sprintf(msg, "%s: done updating input1", sourcename); Logger::LogEvent(msg);
	sprintf(msg, "%s: about to update input2", sourcename); Logger::LogEvent(msg);
	if(imagein2 != NULL) imagein2->Update();
	if(imagein2 == NULL){
		char msg[1024];
		sprintf(msg, "%s: No input!", sourcename);
		DataFlowException e(sourcename, msg);
		throw e;

	}
	sprintf(msg, "%s: done updating input2", sourcename); Logger::LogEvent(msg);
	Execute();
}

void
Shrinker::Execute(){
	int iiwidth = imagein1->GetWidth();
	int iiheight = imagein1->GetHeight();
	if (imagein1 == NULL){
		char msg[1024];
		const char* filtername = FilterName();
		sprintf(msg, "%s: No input!", filtername);
		DataFlowException e(filtername, msg);
		throw e;
	}
	if (iiwidth <= 0 || iiheight <=0){
		char msg[1024];
		const char* filtername = FilterName();
		sprintf(msg, "%s: Input Width:%d or Height:%d <=0", filtername, iiwidth,iiheight);
		DataFlowException e(filtername, msg);
		throw e;
	}
	imageout.SetSize(iiheight/2,iiwidth/2);
	int ioh = imageout.GetHeight();
	int iow = imageout.GetWidth();
    int width_adjustment = 4*iow;
    for(int i=0;i<ioh;i++){
    	for(int j=0;j<iow;j++){
    		imageout.SetPixel(i,j,imagein1->GetPixel(2*i,2*j));
    	}
    }
}

void
TBConcat::Execute(){
		int iih1 = imagein1->GetHeight();
		int iiw1 = imagein1->GetWidth();
		int iiw2 = imagein2->GetWidth();
		if (imagein1 == NULL){
			char msg[1024];
			const char* filtername = FilterName();
			sprintf(msg, "%s: No input 1!", filtername);
			DataFlowException e(filtername, msg);
			throw e;
		}
		if (imagein2 == NULL){
			char msg[1024];
			const char* filtername = FilterName();
			sprintf(msg, "%s: No input 2!", filtername);
			DataFlowException e(filtername, msg);
			throw e;
		}
		if (iiw1 != iiw2){
			char msg[1024];
			const char* filtername = FilterName();
			sprintf(msg, "%s: Widths must match %d, %d", filtername, iiw1,iiw2);
			DataFlowException e(filtername, msg);
			throw e;
		}
		imageout.SetSize(imagein2->GetHeight() + iih1,iiw1);
		int ioh = imageout.GetHeight();
		int iow = imageout.GetWidth();
		for(int i=0; i<ioh;i++){
			for(int j=0; j<iow; j++){
				if(i < iih1){
					imageout.SetPixel(i,j,imagein1->GetPixel(i,j));
				} else {
					imageout.SetPixel(i,j,imagein2->GetPixel(i-iih1,j));
				}
			}
		}
}

void
LRConcat::Execute(){
		int iiw1 = imagein1->GetWidth();
		int iih1 = imagein1->GetHeight();
		int iih2 = imagein2->GetHeight();
		if (imagein1 == NULL){
			char msg[1024];
			const char* filtername = FilterName();
			sprintf(msg, "%s: No input 1!", filtername);
			DataFlowException e(filtername, msg);
			throw e;
		}
		if (imagein2 == NULL){
			char msg[1024];
			const char* filtername = FilterName();
			sprintf(msg, "%s: No input 2!", filtername);
			DataFlowException e(filtername, msg);
			throw e;
		}
		if (iih1 != iih2){
			char msg[1024];
			const char* filtername = FilterName();
			sprintf(msg, "%s: Heights must match %d, %d", filtername, iih1,iih2);
			DataFlowException e(filtername, msg);
			throw e;
		}
		imageout.SetSize(iih1,iiw1 + imagein2->GetWidth());
		int iow = imageout.GetWidth();
		int ioh = imageout.GetHeight();
		for(int i=0; i<ioh;i++){
			for(int j=0; j<iow; j++){
				if(j >= iiw1){
					imageout.SetPixel(i,j,imagein2->GetPixel(i,j-iiw1));
				} else {
					imageout.SetPixel(i,j,imagein1->GetPixel(i,j));
				}
			}
		}
}

void
Blender::SetFactor(float factor_){
	factor = factor_; 
	otherFactor = 1 - factor_;
}

void
Blender::Execute(){
		int iih1 = imagein1->GetHeight();
		int iiw1 = imagein1->GetWidth();
		int iih2 = imagein2->GetHeight();
		int iiw2 = imagein2->GetWidth();
		if (imagein1 == NULL){
			char msg[1024];
			const char* filtername = FilterName();
			sprintf(msg, "%s: No input 1!", filtername);
			DataFlowException e(filtername, msg);
			throw e;
		}
		if (imagein2 == NULL){
			char msg[1024];
			const char* filtername = FilterName();
			sprintf(msg, "%s: No input 2!", filtername);
			DataFlowException e(filtername, msg);
			throw e;
		}
		if (iih1 != iiw2){
			char msg[1024];
			const char* filtername = FilterName();
			sprintf(msg, "%s: Heights must match %d, %d", filtername, iih1,iiw2);
			DataFlowException e(filtername, msg);
			throw e;
		}
		if (iiw1 != iiw2){
			char msg[1024];
			const char* filtername = FilterName();
			sprintf(msg, "%s: Widths must match %d, %d", filtername, iiw1,iiw2);
			DataFlowException e(filtername, msg);
			throw e;
		}
		if (factor > 1){
			char msg[1024];
			const char* filtername = FilterName();
			sprintf(msg, "%s: Invalid factor for Blender:%f", filtername, factor);
			DataFlowException e(filtername, msg);
			throw e;
		}
		imageout.SetSize(iih1, iiw1);
		int iow = imageout.GetWidth();
		Pixel* tempout = imageout.GetPixels();
		for(int i=0; i<iih1;i++){
			for(int j=0; j<iiw1; j++){
				tempout[i*iow+j].blue = (unsigned char)((imagein2->GetPixel(i,j).blue*otherFactor) + (factor*imagein1->GetPixel(i,j).blue));
				tempout[i*iow+j].green = (unsigned char)((imagein2->GetPixel(i,j).green*otherFactor) + (factor*imagein1->GetPixel(i,j).green));
				tempout[i*iow+j].red = (unsigned char)((imagein2->GetPixel(i,j).red*otherFactor) + (factor*imagein1->GetPixel(i,j).red));

			}
		}
		imageout.SetPixels(tempout);
}

void 
Invert::Execute(){
		if (imagein1 == NULL){
			char msg[1024];
			const char* filtername = FilterName();
			sprintf(msg, "%s: No input set!", filtername);
			DataFlowException e(filtername, msg);
			throw e;
		}
		imageout.SetSize(imagein1->GetHeight(), imagein1->GetWidth());
		Pixel* tempout = imageout.GetPixels();
		int ioh = imageout.GetHeight();
		int iow = imageout.GetWidth();
		for(int i=0; i<ioh;i++){
			for(int j=0; j<iow;j++){
				tempout[i*iow+j].blue = 255-(imagein1->GetPixel(i,j)).blue;
				tempout[i*iow+j].green = 255-(imagein1->GetPixel(i,j)).green;
				tempout[i*iow+j].red = 255-(imagein1->GetPixel(i,j)).red;
			}
		}
		imageout.SetPixels(tempout);
}

void
Transpose::Execute(){
		if (imagein1 == NULL){
			char msg[1024];
			const char* filtername = FilterName();
			sprintf(msg, "%s: No input set!", filtername);
			DataFlowException e(filtername, msg);
			throw e;
		}
		imageout.SetSize(imagein1->GetWidth(), imagein1->GetHeight());
		int ioh = imageout.GetHeight();
		int iow = imageout.GetWidth();
		for(int i=0; i<ioh;i++){
			for(int j=0; j<iow;j++){
				imageout.SetPixel(i,j,imagein1->GetPixel(j,i));
			}
		}
}

void
Crop::Execute(void){
    if (Istart < 0 || Istop < 0 || Jstart < 0 || Jstop < 0)
    {
        char msg[1024];
        const char* filtername = FilterName();
        sprintf(msg, "%s: uninitialized region", filtername);
        DataFlowException e(filtername, msg);
        throw e;
    }
    if (Istart >= imagein1->GetWidth() || Istop >= imagein1->GetWidth())
    {
        char msg[1024];
        const char* filtername = FilterName();
        sprintf(msg, "%s: region outside image width", filtername);
        DataFlowException e(filtername, msg);
        throw e;
    }
    if (Jstart >= imagein1->GetHeight() || Jstop >= imagein1->GetHeight())
    {
        char msg[1024];
        const char* filtername = FilterName();
        sprintf(msg, "%s: region outside image height", filtername);
        DataFlowException e(filtername, msg);
        throw e;
    }
    if (Istop < Istart || Jstop < Jstart)
    {
        char msg[1024];
        const char* filtername = FilterName();
        sprintf(msg, "%s: invalid region", filtername);
        DataFlowException e(filtername, msg);
        throw e;
    }

    int height = Jstop-Jstart+1;
    int width  = Istop-Istart+1;
    int inputWidth = imagein1->GetWidth();
    imageout.SetSize(height, width);
    Pixel *buffer = imageout.GetPixels();
    const Pixel *buffer1 = imagein1->GetPixels();
    for (int i = Istart ; i <= Istop ; i++)
        for (int j = Jstart ; j <= Jstop ; j++)
        {
            int idx1 = j*inputWidth+i;
            int idx  = (j-Jstart)*width+(i-Istart);
            buffer[idx].red   = buffer1[idx1].red;
            buffer[idx].green = buffer1[idx1].green;
            buffer[idx].blue = buffer1[idx1].blue;
        }
    imageout.SetPixels(buffer);
}

void 
Checkerboard::Execute(){
	int iih1 = imagein1->GetHeight();
	int iiw1 = imagein1->GetWidth();
	int iih2 = imagein2->GetHeight();
	int iiw2 = imagein2->GetWidth();
	if (imagein1 == NULL){
		char msg[1024];
		const char* filtername = FilterName();
		sprintf(msg, "%s: No input set for image1!", filtername);
		DataFlowException e(filtername, msg);
		throw e;
	}
	if (imagein2 == NULL){
		char msg[1024];
		const char* filtername = FilterName();
		sprintf(msg, "%s: No input set for image2!", filtername);
		DataFlowException e(filtername, msg);
		throw e;
	}
	if (iih1 != iih2){
		char msg[1024];
		const char* filtername = FilterName();
		sprintf(msg, "%s: Heights must match %d, %d", filtername, iih1,iih2);
		DataFlowException e(filtername, msg);
		throw e;
	}
	if (iiw1 != iiw2){
		char msg[1024];
		const char* filtername = FilterName();
		sprintf(msg, "%s: Widths must match %d, %d", filtername, iiw1,iiw2);
		DataFlowException e(filtername, msg);
		throw e;
	}
	imageout.SetSize(iih1,iiw1);
	for(int i=0; i<iih1;i++){
		for(int j=0; j<iiw1;j++){
			if ((i/10+j/10)%2 ==0){
				imageout.SetPixel(i,j,imagein1->GetPixel(i,j));
			} else {
				imageout.SetPixel(i,j,imagein2->GetPixel(i,j));
			}
		}
	}
}