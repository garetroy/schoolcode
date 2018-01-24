#ifndef FILTER_H
#define FILTER_H
#include "sink.h"
#include "source.h"
#include "PNMreader.h"
#include "PNMwriter.h"

class Filter: public Sink, public Source{
	public:
		virtual void Execute(){};
};

class Shrinker: public Filter{
	public:
		virtual void Execute();
	private:

};

class TBConcat: public Filter{
	public:
		virtual void Execute();
	private:
};

class LRConcat: public Filter{
	public:
		virtual void Execute();
	private:
};

class Blender: public Filter{
	public:
		void SetFactor(float factor_);
		virtual void Execute();
	private:
		float factor;
		float otherFactor;
};

#endif