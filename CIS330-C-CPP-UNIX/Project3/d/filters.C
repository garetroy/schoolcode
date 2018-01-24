#include "filters.h"
#include <stdio.h>

void
Blender::SetFactor(float factor_){
	factor = factor_; 
	otherFactor = 1 - factor_;
}


void
Shrinker::Execute(){
	imageout.SetSize(imagein1->GetHeight()/2,imagein1->GetWidth()/2);
	int ioh = imageout.GetHeight();
	int iow = imageout.GetWidth();
    int width_adjustment = 4*imageout.GetWidth();
    for(int i=0;i<ioh;i++){
    	for(int j=0;j<iow;j++){
    		imageout.SetPixel(i,j,imagein1->GetPixel(2*i,2*j));
    	}
    }
}

void
TBConcat::Execute(){
		imageout.SetSize(imagein2->GetHeight() + imagein1->GetHeight(),imagein1->GetWidth());
		for(int i=0; i<imageout.GetHeight();i++){
			for(int j=0; j<imageout.GetWidth(); j++){
				if(i < imagein1->GetHeight()){
					imageout.SetPixel(i,j,imagein1->GetPixel(i,j));
				} else {
					imageout.SetPixel(i,j,imagein2->GetPixel(i-imagein1->GetHeight(),j));
				}
			}
		}
}

void
LRConcat::Execute(){
		imageout.SetSize(imagein1->GetHeight(),imagein1->GetWidth() + imagein2->GetWidth());
		for(int i=0; i<imageout.GetHeight();i++){
			for(int j=0; j<imageout.GetWidth(); j++){
				if(j > imagein1->GetWidth()){
					imageout.SetPixel(i,j,imagein2->GetPixel(i,j));
				} else {
					imageout.SetPixel(i,j,imagein1->GetPixel(i,j));
				}
			}
		}
}

void
Blender::Execute(){
		imageout.SetSize(imagein1->GetHeight(), imagein1->GetWidth());
		Pixel* tempin1 = imagein1->GetPixels();
		Pixel* tempin2 = imagein2->GetPixels();
		Pixel* tempout = imageout.GetPixels();
		for(int i=0; i<imagein1->GetHeight();i++){
			for(int j=0; j<imagein2->GetWidth(); j++){
				tempout[i*imageout.GetWidth()+j].blue = (unsigned char)((tempin2[i*imagein2->GetWidth()+j].blue*otherFactor) + (factor * tempin1[i*imagein1->GetWidth()+j].blue));
				tempout[i*imageout.GetWidth()+j].green = (unsigned char)((tempin2[i*imagein2->GetWidth()+j].green*otherFactor) + (factor * tempin1[i*imagein1->GetWidth()+j].green));
				tempout[i*imageout.GetWidth()+j].red = (unsigned char)((tempin2[i*imagein2->GetWidth()+j].red*otherFactor) + (factor * tempin1[i*imagein1->GetWidth()+j].red));

			}
		}
		imageout.SetPixels(tempout);
}