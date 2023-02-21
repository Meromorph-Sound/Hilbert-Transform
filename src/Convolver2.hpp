/*
 * Convolver2.hpp
 *
 *  Created on: 18 Apr 2021
 *      Author: julianporter
 */

#ifndef CONVOLVER2_HPP_
#define CONVOLVER2_HPP_

#include "FFT.hpp"
#include <vector>
#include <iostream>



namespace meromorph {



class OverlapAdd {
private:

	uint32 M;

	uint32 L;
	uint32 N;
	//uint32 offset;

	std::vector<cx32> fir;

	std::vector<cx32> buf;
	std::vector<float32> yt;
	std::vector<float32> outs;

public:

	OverlapAdd() : M(0), L(0), N(0), fir(), buf(), yt(), outs() {};
	OverlapAdd(const std::vector<cx32> &filt,const uint32 block);
	virtual ~OverlapAdd() = default;

	void operator()(std::vector<float32> &);
	void reset();
};


}
#endif /* CONVOLVER2_HPP_ */
