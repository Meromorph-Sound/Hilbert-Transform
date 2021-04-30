//
//  Integrator.cpp
//  VCO
//
//  Created by Julian Porter on 08/12/2014.
//
//

#include "AFIntegrator.hpp"

namespace meromorph {



float FastIntegrator::step(const float value) {
	auto term = convolve(value);
	integral += term*delta;
	return integral;
}

float RectangularIntegrator::convolve(const float value) { return value; }

float TrapezoidalIntegrator::convolve(const float value) {
	auto n=0.5f*(d+value);
	d=value;
	return n;
}

void TrapezoidalIntegrator::reset() {
	FastIntegrator::reset();
	d=0.f;
}


float SimpsonIntegrator::convolve(const float value) {
	auto n = (d + 4.f*e + value)/6.f;
	d=e;
	e=value;
	return n;
}

void SimpsonIntegrator::reset() {
	FastIntegrator::reset();
	d=e=0.f;
}

float Simpson38Integrator::convolve(const float value) {
	auto n = (d + 3.f*(e+f) + value)*0.125f;
	d=e;
	e=f;
	f=value;
	return n;
}

void Simpson38Integrator::reset() {
	FastIntegrator::reset();
	d=e=f=0.f;
}





using iterator=CircularBuffer<float>::iterator;

Integrator::Integrator(const Integrator &other) : integral(other.integral),
		delta(other.delta), capacity(other.capacity), data(other.data), pattern(other.pattern) {};



Integrator::Integrator(const float delta_,size_t capacity_,const float *array) : integral(),
		delta(delta_), capacity(capacity_), data(capacity), pattern(capacity) {
	for(auto i=0;i<capacity;i++) pattern[i]=array[i];
};

Integrator::Integrator(const float delta_,const IntegrationRule &rule) : Integrator(delta_,rule.length,rule.pattern) {};

float Integrator::convolve() {
	auto itd=data.begin();
	auto itp=pattern.begin();
	for(auto offset=0;offset<capacity;offset++) {
		auto d=*(itd++);
		auto t=*(itp++);
		integral+=t*d;
	}
	return integral*delta;
};

float Integrator::operator()(const float newValue) {
	data.push(newValue);
	return convolve();
};

float Integrator::value() const {
	return integral;
}

void Integrator::Reset() {
	integral=0;
	data.reset();
}

}
