#ifndef SINK_H
#define SINK_H
#include "image.h"
class Sink{
	public:
		virtual void SetInput(Image* image_){imagein1 = image_;};
		virtual void SetInput2(Image* image_){imagein2 = image_;};
	protected:
		Image* imagein1;
		Image* imagein2;
	private:
		
};
#endif