/*
 * FFT.hpp
 *
 *  Created on: 1 Apr 2021
 *      Author: julianporter
 */

#ifndef FFT_HPP_
#define FFT_HPP_

//#include "base.hpp"
#include <complex>
#include <algorithm>
#include <vector>

namespace meromorph {

using uint32 = unsigned;
using float32 = float;
using cx32 = std::complex<float32>;

using cvec = std::vector<cx32>;
using rvec = std::vector<float32>;

inline float32 Pi = 3.141592653589793f;

namespace cx {
	inline cx32 Zero = cx32();
	inline cx32 I = cx32(0,1);
	inline cx32 One = cx32(1);
	inline cx32 Sqr2 = cx32(sqrt(2.f));
}




class FFT {
public:
	static void fft(cvec &buffer);
	static void rfft(const rvec &in,cvec &buffer);
	static void ifft(cvec &buffer);
	static void rifft(rvec &out,cvec &buffer);


};



} /* namespace meromorph */

#endif /* FFT_HPP_ */
