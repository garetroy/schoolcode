#ifndef SINK_H
#define SINK_H
#include "image.h"
#include "logging.h"

class Sink{
	protected:
		Image* imagein1;
		Image* imagein2;
	public:
		Sink(){imagein1 = NULL; imagein2 = NULL;};
		virtual void SetInput(Image* image_){imagein1 = image_;};
		virtual void SetInput2(Image* image_){imagein2 = image_;};
		virtual const char *SinkName() = 0;
	private:
		
};
#endif