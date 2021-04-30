/*
 * FFT.cpp
 *
 *  Created on: 1 Apr 2021
 *      Author: julianporter
 */

#include "FFT.hpp"
#include <algorithm>

namespace meromorph {

void FFT::fft(std::vector<cx32> &buffer) {
			// DFT
		uint32 N=buffer.size();
		auto k = N;
		float32 thetaT = Pi / (float32)N;
			auto phiT = std::polar(1.f,-thetaT);
			while (k > 1)
			{
				auto n = k;
				k >>= 1;
				phiT = phiT * phiT;
				auto T = cx::One;
				for (uint32 l = 0; l < k; l++)
				{
					for (uint32 a = l; a < N; a += n)
					{
						auto b = a + k;
						auto t = buffer[a] - buffer[b];
						buffer[a] += buffer[b];
						buffer[b] = t * T;
					}
					T *= phiT;
				}
			}
			// Decimate
			auto m = (uint32)log2(N);
			for (auto a = 0; a < N; a++)
			{
				uint32 b = a;
				// Reverse bits
				b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
				b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
				b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
				b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
				b = ((b >> 16) | (b << 16)) >> (32 - m);
				if (b > a)
				{
					auto t = buffer[a];
					buffer[a] = buffer[b];
					buffer[b] = t;
				}
			}


	}


void FFT::ifft(std::vector<cx32> &buffer)
	{
	std::transform(buffer.begin(),buffer.end(),buffer.begin(),[](cx32 z) { return std::conj(z);});
	fft(buffer);
	auto s = sqrt(cx32(buffer.size()));
	std::transform(buffer.begin(),buffer.end(),buffer.begin(),[s](cx32 z) { return std::conj(z)/s;});
	}



} /* namespace meromorph */
