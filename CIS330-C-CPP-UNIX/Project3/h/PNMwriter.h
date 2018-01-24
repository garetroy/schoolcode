#ifndef PNM_WRITER
#define PNM_WRITER
#include "sink.h"
class PNMwriter : public Sink{
	public:
		void Write(char *filename_);
		virtual const char* SinkName(){return "PNMwriter";};
	private:
};

#endif