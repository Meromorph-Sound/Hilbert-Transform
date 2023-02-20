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

class OverlapSave {
private:
	//std::vector<float32> fir;
	uint32 nFIR;

	uint32 blockSize;
	uint32 nFFT;
	uint32 offset;

	cvec firBuffer;

	cvec buffer;
	rvec yt;
	rvec xs;






public:

	OverlapSave() : nFIR(0), blockSize(0), nFFT(0), offset(0),  firBuffer(), buffer(), yt(), xs() {};
	OverlapSave(const rvec &v,const uint32 fftsize,const uint32 block);
	OverlapSave(const rvec &v,const uint32 block);
	OverlapSave(cvec &v,const uint32 fftsize,const uint32 block);
	OverlapSave(cvec &v,const uint32 block);
	virtual ~OverlapSave() = default;

	void operator()(std::vector<float32> &vec);
	void reset() { xs.assign(nFFT,0); }
};

class OverlapAdd {
private:

	uint32 M;

	uint32 L;
	uint32 N;
	uint32 offset;

	std::vector<cx32> firBuffer;

	std::vector<cx32> buffer;
	std::vector<float32> yt;
	std::vector<float32> outs;





public:

	OverlapAdd() : M(0), L(0), N(0), offset(0),  firBuffer(), buffer(), yt(), outs() {};
	OverlapAdd(const std::vector<cx32> &v,const uint32 block);
	virtual ~OverlapAdd() = default;

	void operator()(std::vector<float32> &vec);
	void reset() { };
};


}
#endif /* CONVOLVER2_HPP_ */
