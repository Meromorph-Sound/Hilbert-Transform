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
#define NSEGMENTS 10

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

		meromorph::OverlapAdd os(fir,BLOCKSIZE);

		std::cout << "N, X, Y" << std::endl;


		meromorph::rvec rins(BLOCKSIZE);
		meromorph::rvec routs(BLOCKSIZE);


		for(auto segment = 0;segment<NSEGMENTS;segment++) {
			auto start = BLOCKSIZE*segment;
			for(auto i=0;i<BLOCKSIZE;i++) rins[i] = cos((start+i)*angular);
			std::copy(rins.begin(),rins.end(),routs.begin());
			os(routs);


			for(auto i=0;i<routs.size();i++) {
				std::cout << start+i << ", " << rins[i] << ", " << routs[i] << std::endl;
			}
		}


	}
	catch(std::exception &e) {
		std::cerr << "Exception is " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
