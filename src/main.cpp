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
		for(auto i=0;i<h.hilbert.size();i++) {
			auto z=h.hilbert[i];
			std::cout << i << " , " << z.real() << " , " << z.imag()  << std::endl;
		}
		}
	catch(std::exception &e) {
		std::cerr << "Exception is " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
