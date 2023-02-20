//
//  Integrator.h
//  VCO
//
//  Created by Julian Porter on 08/12/2014.
//
//

#ifndef __VCO__Integrator__
#define __VCO__Integrator__

#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include "CircularBuffer.hpp"


#include "AFIntegrationRule.hpp"

namespace meromorph
{


class FastIntegrator {
protected:
	float integral;
	float delta;

	virtual float convolve(const float value) { return 0.f; };

public:
	FastIntegrator(const float delta_) : integral(0.f), delta(delta_) {};
	virtual ~FastIntegrator() = default;

	virtual void reset() { integral = 0.f; }
	virtual float step(const float value);
	float value() const { return integral; }
};


class RectangularIntegrator : public FastIntegrator  {
protected:

	virtual float convolve(const float value);
};

class TrapezoidalIntegrator : public FastIntegrator {
protected:
	float d = 0.f;
	virtual float convolve(const float value);
public:
	virtual void reset();
};


class SimpsonIntegrator : public FastIntegrator {
protected:
	float d = 0.f;
	float e = 0.f;
	virtual float convolve(const float value);
public:
	virtual void reset();
};

class Simpson38Integrator : public FastIntegrator {
protected:
	float d = 0.f;
	float e = 0.f;
	float f=0.f;
	virtual float convolve(const float value);
public:
	virtual void reset();
};




class Integrator {
private:


	float integral = 0.f;
	float delta = 0.f;
	unsigned capacity = 0;
	CircularBuffer<float> data;
	std::vector<float> pattern;


	float convolve();

public:

	Integrator() = default;
	Integrator(const Integrator &other) = default;
	Integrator(const float delta_,size_t capacity_,const float *array);
	Integrator(const float delta_,const IntegrationRule &rule);
	virtual ~Integrator() = default;



	float operator()(const float newValue);
	float value() const ;
	void Reset();
};



}

#endif /* defined(__VCO__Integrator__) */
