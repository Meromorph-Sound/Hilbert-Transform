/*
 * Convolver.cpp
 *
 *  Created on: 31 Mar 2021
 *      Author: julianporter
 */

#include "Convolver.hpp"
#include <iostream>

namespace meromorph {

void Hilbert::makeHilbertKernel() {
	//std::cerr << "Building array" << std::endl;
	//std::cerr << "N = " << N << " NHilbert = " << hilbertN << std::endl;
	//std:: cerr << "Zero = " << cx::Zero << std::endl;
	for(auto i=0;i<hilbertN;i++) {
		//std::cerr << "i = " << i << std::endl;
		cx32 value = (0==(i&1)) ? cx::Zero : cx32(2.0/(Pi * i));
		//std::cerr << "value = " << value << std::endl;
		hilbert[hilbertN+i] = value;
		//std::cerr << "Set +" << std::endl;
		hilbert[hilbertN-i] = -value;
		//std::cerr << "Set -" << std::endl;
	}
	//for(auto i=0;i<2*N;i++) std::cout << i << ", " << hilbert[i].real() << "," << hilbert[i].imag() << std::endl;
	//std::cerr << "Built array; about to do FFT" << std::endl;
	FFT::fft(hilbert);
	//std::cerr << "Performed FFT" << std::endl;
}



Hilbert::Hilbert(const uint32 N_) :
		N(N_), hilbertN((N/2)-1),
		hilbert(cx::Zero,2*N), buffer(cx::Zero,2*N), tmp(cx::Zero,2*N) {
	//std::cerr << "About to try to make Kernel" << std::endl;
	makeHilbertKernel();
}



void Hilbert::reset() {
	buffer = cx::Zero;
}

void Hilbert::apply(std::valarray<cx32> &real) {
	buffer = buffer.shift(N);
	for(auto i=0;i<N;i++) buffer[N+i]=real[i];
	tmp=buffer;
	FFT::fft(tmp);
	tmp=tmp * hilbert;
	FFT::ifft(tmp);

	tmp.shift(N);
	tmp *= cx::I;
	real += tmp;
}

}
