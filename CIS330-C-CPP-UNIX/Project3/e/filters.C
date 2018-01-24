#include "filters.h"
#include <stdio.h>

void
Shrinker::Execute(){
	int iiw1 = imagein1->GetWidth();
	int iih1 = imagein1->GetHeight();
	imageout.SetSize(iih1/2,iiw1/2);
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