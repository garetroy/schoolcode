#ifndef CHECKSUM_H
#define CHECKSUM_H
#include "sink.h"
class CheckSum: public Sink{
	public:
		virtual const char *SinkName(){return "CheckSum";};
		virtual void OutputCheckSum(const char *);
	private:
};
#endif