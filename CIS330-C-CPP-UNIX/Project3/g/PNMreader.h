#ifndef PNM_READER
#define PNM_READER
#include "source.h"
class PNMreader : public Source{
	public:
		PNMreader(char *filename_){strcpy(filename,filename_);}
		virtual void Execute();
		virtual const char *SourceName(){return "PNMreader";};
	private:
		char filename[256];
};
#endif