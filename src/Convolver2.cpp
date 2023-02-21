/*
 * Convolver2.cpp
 *
 *  Created on: 18 Apr 2021
 *      Author: julianporter
 */

#include "Convolver2.hpp"

namespace meromorph {



/*
(Overlap-save algorithm for linear convolution)
h = FIR_impulse_response
M = length(h)
overlap = M − 1
N = 8 × overlap    (see next section for a better choice)
step_size = N − overlap
H = DFT(h, N)
position = 0

while position + N ≤ length(x)
    yt = IDFT(DFT(x(position+(1:N))) × H)
    y(position+(1:step_size)) = yt(M : N)    (discard M−1 y-values)
    position = position + step_size
end
*/
uint32 nextPower(const uint32 n) {
	return (uint32)exp2(ceil(log2(n)));
}




OverlapAdd::OverlapAdd(const std::vector<cx32> &filt,const uint32 block) :  M(filt.size()),
		L(block), N(nextPower(L+M)),
		fir(N,cx::Zero), buf(N,cx::Zero), yt(N), outs(N,0) {
	std::copy(filt.begin(),filt.end(),fir.begin());
	FFT::fft(fir);
	std::cerr << "nFIR=" << M << " block=" << L << " nFFT=" << N << " offset=" << std::endl;
}

void OverlapAdd::operator()(std::vector<float32> &vec) {

	auto yend=std::copy(vec.begin(),vec.end(),yt.begin());
	std::fill(yend,yt.end(),0);
	FFT::rfft(yt,buf);
	std::transform(buf.begin(),buf.end(),fir.begin(),buf.begin(), std::multiplies<cx32>());
	FFT::rifft(yt,buf);


	auto end=std::copy(outs.begin()+L,outs.end(),outs.begin());
	std::fill(end,outs.end(),0);
	std::transform(outs.begin(),outs.end(),yt.begin(),outs.begin(), std::plus<float32>());
	std::copy(outs.begin(),outs.begin()+L,vec.begin());


}

void OverlapAdd::reset() { std::fill(yt.begin(),yt.end(),0); };



}

