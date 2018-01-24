#ifndef FILTER_H
#define FILTER_H
#include "PNMreader.h"
#include "PNMwriter.h"

class Filter: public Sink, public Source{
	public:
		virtual const char *FilterName() = 0;
		virtual void Execute(){};
		virtual void Update();
		const char *SourceName(){return FilterName();};
		const char *SinkName(){return FilterName();};
};

class Shrinker: public Filter{
	public:
		virtual void Execute();
		virtual const char *FilterName(){return "Shrinker";};
	private:

};

class TBConcat: public Filter{
	public:
		virtual void Execute();
		virtual const char *FilterName(){return "TBConcat";};
	private:
};

class LRConcat: public Filter{
	public:
		virtual void Execute();
		virtual const char *FilterName(){return "LRConcat";};
	private:
};

class Blender: public Filter{
	public:
		void SetFactor(float factor_);
		virtual void Execute();
		virtual const char *FilterName(){return "Blender";};
	private:
		float factor;
		float otherFactor;
};

#endif