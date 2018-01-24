#ifndef FILTER_H
#define FILTER_H
#include "PNMreader.h"
#include "PNMwriter.h"
#include "color.h"
#include "checksum.h"

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

class Invert: public Filter{
	public:
		virtual void Execute();
		virtual const char *FilterName(){return "Invert";};
	private:
};

class Transpose: public Filter{
	public:
		virtual void Execute();
		virtual const char *FilterName(){return "Transpose";};
	private:
};

class Crop : public Filter{
  public:
    Crop() {Istart = Istop = Jstart = Jstop = -1; };
    virtual const char *FilterName() { return "Crop"; };
    virtual void Execute();
    void SetRegion(int Istart_, int Istop_, int Jstart_, int Jstop_){Istart = Istart_;Istop  = Istop_;Jstart = Jstart_;Jstop  = Jstop_;}

  private:
    int Istart, Istop, Jstart, Jstop;
};

class Checkerboard: public Filter{
	public:
		virtual void Execute();
		virtual const char *FilterName(){return "Checkerboard";};
	private:

};

#endif