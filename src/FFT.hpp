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
#include <valarray>

namespace meromorph {

using uint32 = unsigned;
using float32 = float;
using cx32 = std::complex<float32>;

inline float32 Pi = 3.141592653589793f;

namespace cx {
	inline cx32 Zero = cx32();
	inline cx32 I = cx32(0,1);
	inline cx32 One = cx32(1);
}

class FFT {
public:
	static void fft(std::valarray<cx32> &buffer);
	static void ifft(std::valarray<cx32> &buffer);
};

} /* namespace meromorph */

#endif /* FFT_HPP_ */
