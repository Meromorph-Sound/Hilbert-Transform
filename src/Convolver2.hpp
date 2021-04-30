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

namespace meromorph {

/*
class BlockCircularBuffer {
private:
	uint32 blockSize;
	uint32 nBlocks;
	std::vector<float32> buffer;

	uint32 offsetFor(const uint32 b) {
		return (blockSize*b) % buffer.size();
	}


public:
	using iterator=std::vector<float32>::iterator;

	BlockCircularBuffer(const uint32 nB,const uint32 s) : blockSize(s), nBlocks(nB), buffer(blockSize*nBlocks) {};
	virtual ~BlockCircularBuffer() = default;

	iterator begin(const uint32 block) {
		return buffer.begin() + offsetFor(block);
	}
	iterator end(const uint32 block) {
		auto o=offsetFor(block);
		return (o==0) ? buffer.end() : buffer.begin() + o;
	}

};
class Convolver2 {
};
*/
}
#endif /* CONVOLVER2_HPP_ */
