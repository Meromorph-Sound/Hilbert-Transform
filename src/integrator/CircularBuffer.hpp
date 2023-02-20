/*
 * CircularBuffer.hpp
 *
 *  Created on: 27 Apr 2021
 *      Author: julianporter
 */

#ifndef INTEGRATOR_CIRCULARBUFFER_HPP_
#define INTEGRATOR_CIRCULARBUFFER_HPP_

#include <type_traits>
#include <algorithm>

namespace meromorph {

// The clever bit:
// Use a buffer twice as long, so the iterator from begin() to end() always has a clear linear
// run along the array.  The slow down is simply an exytra assignation every time you put
// something in, but the speed-up is surely considerable, for linear indexing, at least.
template<typename T,class = typename std::enable_if<std::is_default_constructible<T>::value>::type>
class CircularBuffer {
private:
	T *values;
	unsigned N;
	unsigned offset;

public:
	using iterator = T*;
	using const_iterator = const T*;

	CircularBuffer() : N(0), offset(0), values(nullptr) {}
	CircularBuffer(const unsigned N_,const T def) : N(N_), offset(0) {
		values = new T[2*N];
		for(auto i=0;i<2*N;i++) values[i]=def;
	}
	CircularBuffer(const unsigned N_) : CircularBuffer(N_,T()) {}
	CircularBuffer(const CircularBuffer &o) : N(o.N), offset(o.offset) {
		values = new T[2*N];
		for(auto i=0;i<2*N;i++) values[i]=o.values[i];
	}

	virtual ~CircularBuffer() {
		if(values!=nullptr) delete [] values;
	}

	unsigned size() const { return N; };
	void fill(const T value = T()) { for(auto i=0;i<2*N;i++) values[i]=value; }
	void reset() {
		fill();
		offset=0;
	}

	void push(const T value) {
		values[offset+N] = values[offset] = value;
		offset=(offset+1)%N;
	}

	iterator begin() { return values+offset; }
	iterator end() { return values+offset+N; }

	const_iterator cbegin() const { return values+offset; }
	const_iterator cend() const { return values+offset+N; }
	T & operator[](const unsigned idx) { return values[(idx+offset)%N]; };



};

}



#endif /* INTEGRATOR_CIRCULARBUFFER_HPP_ */
