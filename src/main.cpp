/*
 * main.cpp
 *
 *  Created on: 2 Apr 2021
 *      Author: julianporter
 */




#include "Convolver.hpp"
#include <iostream>

int main(const int argc,const char **argv) {

	try {
		std::cout << " HX, HY, DX, DY" << std::endl;
		//std::cerr << "Creating instance of Hilbert" << std::endl;
		meromorph::Hilbert h(64);

		//std::cerr << "Created it" << std::endl;
		//for(auto i=0;i<h.hilbert.size();i++) {
		//	auto z=h.hilbert[i];
		//	std::cout << i << " , " << z.real() << " , " << z.imag()  << std::endl;
		//}

		std::vector<meromorph::cx32> ins(64);
		std::vector<meromorph::cx32> outs(64);

		auto freq = 1000.f;
		auto angular = 2.f*meromorph::Pi/freq;

		for(auto segment = 0;segment<100;segment++) {
			auto start = 64*segment;
			for(auto i=0;i<64;i++) ins[i] = meromorph::cx32(cos((start+i)*angular));

			h.apply(ins,outs);

			for(auto i=0;i<outs.size();i++) {
				auto r=std::real(ins[i]);
				auto z=outs[i];
				auto t = (i+start)*angular;
				std::cout << t << ", " << r << " , " << z.real() << " , " << z.imag()  << std::endl;
			}
		}


	}
	catch(std::exception &e) {
		std::cerr << "Exception is " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
