/*
 * Convolver.hpp
 *
 *  Created on: 31 Mar 2021
 *      Author: julianporter
 */

#ifndef CONVOLVER_HPP_
#define CONVOLVER_HPP_

#include <cmath>
#include <vector>
//#include "base.hpp"
#include "FFT.hpp"

/**
 * MATLAB code to emulate
 *
buffer2 = zeros(1,N*2);
buffer2(1:N) = data2;
f2 = fft(buffer2);

range = (N+1):(N*2);

outs = zeros(1,N*nBlocks);

buffer1 = zeros(1,N*2);
for chunk = 0:(nBlocks-1)
    offset=1+chunk*N;
    last=offset+N-1;
    buffer1(1:N) = buffer1(range);
    buffer1(range) = data1(offset:last);

    f1 = fft(buffer1);
    fp = f1 .* f2;
    out = ifft(fp);
    st = N*chunk+1;
    en = N*(chunk+1);
    outs(st:en) = out((N+1):N*2);
end

outs=outs(N:(N*nBlocks));

here data1 is the data, and data2 is the function to convolve with.
 *
 */

namespace meromorph {


class Hilbert {
private:
	uint32 N;

	uint32 nStages;
public:
	cvec hilbert;
	cvec buffer;
	cvec tmp;

	void makeHilbertKernel();


	Hilbert(const uint32 N_);
	virtual ~Hilbert() = default;

	void reset();
	void apply(const cvec &,cvec &);
	uint32 delay() const { return nStages; }

	void fir(cvec &);
};

}

#endif /* CONVOLVER_HPP_ */
