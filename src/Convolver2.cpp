/*
 * Convolver2.cpp
 *
 *  Created on: 18 Apr 2021
 *      Author: julianporter
 */

#include "Convolver2.hpp"

namespace meromorph {

template<class InputIterator, class Size, class OutputIterator>
  OutputIterator copy_n (InputIterator first, Size n, OutputIterator result)
{
  while (n>0) {
    *result = *first;
    ++result; ++first;
    --n;
  }
  return result;
}

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


OverlapSave::OverlapSave(const rvec &fir,const uint32 fftsize,const uint32 block) : nFIR(fir.size()),
		blockSize(block), nFFT(fftsize), offset(nFIR-1),
		firBuffer(nFFT,cx::Zero), buffer(nFFT,cx::Zero), yt(nFFT), xs(nFFT) {
	rvec f(nFFT);
	std::copy(fir.begin(),fir.end(),f.begin());
	FFT::rfft(f,firBuffer);
	std::cerr << "nFIR=" << nFIR << " block=" << blockSize << " nFFT=" << nFFT << " offset=" << offset << std::endl;
}
OverlapSave::OverlapSave(cvec &fir,const uint32 fftsize,const uint32 block) : nFIR(fir.size()),
		blockSize(block), nFFT(fftsize), offset(nFIR-1),
		firBuffer(128,cx::Zero), buffer(128,cx::Zero), yt(nFFT), xs(128) {
	std::copy(fir.begin(),fir.end(),firBuffer.begin());
	FFT::fft(firBuffer);
	std::cerr << "nFIR=" << nFIR << " block=" << blockSize << " nFFT=" << nFFT << " offset=" << offset << std::endl;
}
OverlapSave::OverlapSave(const rvec &fir,const uint32 block) : OverlapSave(fir,nextPower(block+fir.size()-1),block) {}
OverlapSave::OverlapSave(cvec &fir,const uint32 block) : OverlapSave(fir,nextPower(block+fir.size()-1),block) {}



void OverlapSave::operator()(rvec &vec) {
	std::copy_n(xs.begin(),64,xs.begin()+64);
	std::copy_n(vec.begin(),64,xs.begin());
	//std::fill(xs.begin()+blockSize+offset,xs.end(),0);

	FFT::rfft(xs,buffer);
	std::transform(buffer.begin(),buffer.end(),firBuffer.begin(),buffer.begin(), std::multiplies<cx32>());
	FFT::rifft(yt,buffer);
	std::copy_n(yt.begin()+64,64,vec.begin());

	//std::move(xs.begin()+offset,xs.end(),xs.begin());
	//std::copy(vec.begin(),vec.end(),xs.begin()+offset);
	////for(auto i=0;i<offset;i++) xs[i]=xs[i+offset];
	////for(auto i=0;i<blockSize;i++) xs[i+offset]=vec[i];
	//FFT::rfft(xs,buffer);
	//std::transform(buffer.begin(),buffer.end(),firBuffer.begin(),buffer.begin(), std::multiplies<cx32>());
	////for(auto i=0;i<nFFT;i++) buffer[i]*=firBuffer[i];
	//FFT::rifft(yt,buffer);
	//std::copy_n(yt.begin(),blockSize,vec.begin());
	////for(auto i=0;i<blockSize;i++) vec[i]=yt[i];



}

OverlapAdd::OverlapAdd(const std::vector<cx32> &v,const uint32 block) :  M(v.size()),
		L(block), N(nextPower(L+M)), offset(N-L),
		firBuffer(N,cx::Zero), buffer(N,cx::Zero), yt(N), outs(N,0) {
	std::copy(v.begin(),v.end(),firBuffer.begin());
	FFT::fft(firBuffer);
	std::cerr << "nFIR=" << M << " block=" << L << " nFFT=" << N << " offset=" << offset << std::endl;
}

void OverlapAdd::operator()(std::vector<float32> &vec) {
	std::copy(vec.begin(),vec.end(),yt.begin());
	std::fill(yt.begin()+L,yt.end(),0);
	FFT::rfft(yt,buffer);
	for (int i = 0; i < N; i++) buffer[i]*=firBuffer[i];
	FFT::rifft(yt,buffer);

	for(auto i=0;i<N-L;i++) outs[i]=outs[i+L];
	for(auto i=N-L;i<N;i++) outs[i]=0;

	for(auto i=0;i<N;i++) outs[i]+=yt[i];

	for(auto i=0;i<L;i++) vec[i]=outs[i];

}



}

