/*
 * main.cpp
 *
 *  Created on: 2 Apr 2021
 *      Author: julianporter
 */




#include "Convolver.hpp"
#include "FFT.hpp"
#include "Convolver2.hpp"
#include <iostream>

#define BLOCKSIZE 64
#define NSEGMENTS 100

int main(const int argc,const char **argv) {

	try {
		int L=31;
		auto Lm = -(L-1)/2;

		auto fSample = 4000.f;
		auto freq = 600.f;
		auto angular = 2.f*meromorph::Pi*freq/fSample;
		auto pL = meromorph::Pi*(float)L;

		auto epsilon = .0001f;     //% avoids 0 / 0
		meromorph::cvec fir(L,meromorph::cx::Zero);
		for(auto i=0;i<L;i++) {
			fir[i]=sin(angular*float(i+Lm+epsilon))/pL;
		}




		//meromorph::Hilbert h(63);
		//meromorph::cvec fir(31);
		//h.fir(fir);

		//for(auto it=fir.begin();it!=fir.end();it++) {
		//	std::cout << std::real(*it) << " , " << std::imag(*it) << std::endl;
		//}

		//for(auto i=0;i<15;i++) fir[i]=meromorph::cx::One;

		meromorph::OverlapAdd os(fir,BLOCKSIZE);



		//std::cout << "X, R, I, X" << std::endl;
		std::cout << "N, X, Y" << std::endl;
		//std::cerr << "Creating instance of Hilbert" << std::endl;
		//meromorph::Hilbert h(64);


		//std::cerr << "Created it" << std::endl;
		//for(auto i=0;i<h.hilbert.size();i++) {
		//	auto z=h.hilbert[i];
		//	std::cout << i << " , " << z.real() << " , " << z.imag()  << std::endl;
		//}

		meromorph::rvec rins(64);
		//std::vector<meromorph::cx32> ins(64);
		meromorph::rvec routs(64);
		//std::vector<meromorph::cx32> outs(64);




		for(auto segment = 0;segment<NSEGMENTS;segment++) {
			auto start = BLOCKSIZE*segment;
			for(auto i=0;i<BLOCKSIZE;i++) rins[i] = cos((start+i)*angular);
			std::copy(rins.begin(),rins.end(),routs.begin());
			os(routs);

			//meromorph::FFT::rfft(rins,outs);
			//h.apply(ins,outs);
			//std::transform(outs.begin(),outs.end(),ins.begin(),[](meromorph::cx32 z) { return z; });

			//meromorph::FFT::rifft(routs,ins);

			for(auto i=0;i<routs.size();i++) {
				std::cout << start+i << ", " << rins[i] << ", " << routs[i] << std::endl;
				//auto zr=std::real(outs[i]);
				//auto zi=std::imag(outs[i]);
				//auto x=routs[i];
				//auto t = (i+start)*angular;
				//std::cout << rins[i] << ", " << zr << ", " << zi << ", " << x <<  std::endl;
				//auto r=std::real(ins[i]);
				//auto z=outs[i];

				//std::cout << t << ", " << r << " , " << z.real() << " , " << z.imag()  << std::endl;
			}
		}


	}
	catch(std::exception &e) {
		std::cerr << "Exception is " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
