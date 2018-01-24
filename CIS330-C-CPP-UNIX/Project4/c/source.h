#ifndef SOURCE_H
#define SOURCE_H
#include "image.h"
#include "logging.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

class Source{
	public:
		Source(){UpdateSource();};
		Image* GetOutput(){return &imageout;};
		virtual void Update();
		void UpdateSource(){imageout.SetSource(this);};
		virtual const char *SourceName() = 0;
		virtual double GetTime(){gettimeofday(&endtime, 0); return double((endtime.tv_sec - starttime.tv_sec)+double(endtime.tv_usec - starttime.tv_usec)) / 100000;};
		virtual void SetStart(){gettimeofday(&starttime, 0);};
	protected:
		char msg[256];
		Image imageout;
		struct timeval starttime;
		struct timeval endtime;
		virtual void Execute() = 0;
	private:
};

#endif