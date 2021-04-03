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
		//std::cerr << "Creating instance of Hilbert" << std::endl;
		meromorph::Hilbert h(64);

		//std::cerr << "Created it" << std::endl;
		//for(auto i=0;i<h.hilbert.size();i++) {
		//	auto z=h.hilbert[i];
		//	std::cout << i << " , " << z.real() << " , " << z.imag()  << std::endl;
		//}

		std::valarray<meromorph::cx32> ins(meromorph::cx::Zero,64);
		std::valarray<meromorph::cx32> outs(meromorph::cx::Zero,64);

		for(auto segment = 0;segment<5;segment++) {
			auto start = 64*segment;
			for(auto i=0;i<64;i++) ins[i] = meromorph::cx32(cos((start+i)*0.1f));

			h.apply(ins,outs);

			for(auto i=0;i<outs.size();i++) {
				auto z=outs[i];
				std::cout << (i+start) << " , " << z.real() << " , " << z.imag()  << std::endl;
			}
		}


	}
	catch(std::exception &e) {
		std::cerr << "Exception is " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
