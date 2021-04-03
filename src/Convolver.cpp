/*
 * Convolver.cpp
 *
 *  Created on: 31 Mar 2021
 *      Author: julianporter
 */

#include "Convolver.hpp"
#include <iostream>
#include <algorithm>

namespace meromorph {

void copy(std::valarray<cx32> &buffer,float32 *in) {
	for(auto n=0;n<buffer.size();n++) buffer[n]=cx32(in[n]);
}
void copy(float32 *out,std::valarray<cx32> &buffer,const cx32 phase) {
	buffer *= phase;
	for(auto n=0;n<buffer.size();n++) out[n]=std::real(buffer[n]);
}

void Hilbert::makeHilbertKernel() {


	for(auto i=0;i<nStages;i++) {
		cx32 value = (0==(i&1)) ? cx::Zero : cx32(2.0/(Pi * i));
		hilbert[nStages+i] = value;
		hilbert[nStages-i] = -value;
	}
	FFT::fft(hilbert);
}



Hilbert::Hilbert(const uint32 N_) : N(N_), nStages((N-1)/2), hilbert(cx::Zero,2*N), buffer(cx::Zero,2*N), tmp(cx::Zero,2*N) {
	std::cerr << "NStages = " << nStages << " n = " << N << std::endl;
	makeHilbertKernel();
}



void Hilbert::reset() {
	buffer = cx::Zero;
}

void Hilbert::apply(const std::valarray<cx32> &in,std::valarray<cx32> &out) {
	buffer = buffer.shift(N);
	for(auto i=0;i<N;i++) buffer[N+i]=in[i];
	//std::copy(std::begin(buffer),std::end(buffer),std::begin(out));
	tmp=buffer;
	FFT::fft(tmp);
	tmp=tmp * hilbert;
	FFT::ifft(tmp);

	tmp.shift(N);
	for(auto i=0;i<N;i++) out[i]= in[i] + cx::I * tmp[N-1-i];
}


}
