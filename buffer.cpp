#include "buffer.h"
#include <iostream>
#include <cassert>
#include <algorithm>

CircularBuffer::CircularBuffer(const int capacity) {
	maxSize = capacity;
	buffer = new value_type[capacity];
}

CircularBuffer::CircularBuffer(const int capacity, const value_type arr[]) {
	maxSize = capacity;
	buffer = new value_type[capacity];
	for (int i = 0; i < maxSize; ++i) {
		buffer[i] = arr[i];
	}
	end = maxSize - 1;
	size = maxSize;
}

CircularBuffer::CircularBuffer(int capacity, const value_type elem) {
	maxSize = capacity;
	buffer = new value_type[capacity];
	for (int i = 0; i < capacity; ++i) {
		buffer[i] = elem;
		++size;
	}
	end = capacity - 1;
}

CircularBuffer::~CircularBuffer() {
	delete[] buffer;
}

value_type& CircularBuffer::operator[](int i) {
	return buffer[i];
}

int CircularBuffer::Module(int i) {
	if (i < 0 or i > maxSize) {
		return maxSize - 1;
	}
	else {
		return i % maxSize;
	}
}

value_type& CircularBuffer::At(int i) {
	if (i >= 0 and i < maxSize) {
		return buffer[i];
	}
	else {
		std::cout << "incorrect index" << std::endl;
	}
}

value_type& CircularBuffer::Front() {
	return buffer[start];
}

value_type& CircularBuffer::Back() {
	return buffer[end];
}

int CircularBuffer::Size() const {
	return size;
}

bool CircularBuffer::Empty() const {
	if (size == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool CircularBuffer::Full() const {
	if (size == maxSize) {
		return true;
	}
	else {
		return false;
	}
}

int CircularBuffer::Reserve() const {
	return (maxSize - size);
}

int CircularBuffer::Capacity() const {
	return maxSize;
}

void CircularBuffer::Push_back(const value_type item) {
	if ((*this).Empty() == true) {
		end = Module(end + 1);
		(*this)[end] = item;
		size += 1;
	}
	else {
		end = Module(end + 1);
		(*this)[end] = item;
		if (size != maxSize) {
			size += 1;
		}
		if (end == start) {
			start = Module(start + 1);
		}
	}
}

void CircularBuffer::Push_front(const value_type item) {
	start = Module(start - 1);
	(*this)[start] = item;
	if (size < maxSize) {
		size += 1;
	}
	if (start == end) {
		end = Module(end - 1);
	}
}

void CircularBuffer::Print() {
	std::cout << "\n";
	if (this->Empty() == true) {
		std::cout << "buffer is empty" << "\n";
	}
	else {
		for (int i = 0; i < maxSize; i++) {
			std::cout << buffer[i];
		}
		std::cout << "\n";
		std::cout << "start: " << start << "\n" << "end: " << end << "\n" << "size: " << size << std::endl;
	}
}

void CircularBuffer::Pop_back() {
	this->Back() = NULL;
	end = Module(end - 1);
	if (end == start) {
		start = Module(start - 1);
	}
	size -= 1;
}

void CircularBuffer::Pop_front() {
	this->Front() = NULL;
	size -= 1;
	start = Module(start + 1);
}

void CircularBuffer::Linearize2() {
	if (this->Is_linearized() == false) {
		value_type* cloud = new value_type[maxSize]{ 0 };
		int first = start;
		int last = end;
		for (int i = 0; i < maxSize; ++i) {
			cloud[i] = (*this)[first];
			first = Module(first + 1);
		}
		for (int j = 0; j < maxSize; ++j) {
			(*this)[j] = cloud[j];
		}
		start = 0;
		end = size - 1;
	}
}

void CircularBuffer::Linearize() {
	if (!this->Is_linearized()) {
		std::rotate(buffer, buffer+start, buffer+size);
		start = 0;
		end = size - 1;
	}
}

bool CircularBuffer::Is_linearized() const {
	if (start == 0 and end == size - 1) {
		return true;
	}
	else {
		return false;
	}
}

void CircularBuffer::Set_capacity(int new_capacity) {
	(*this).Linearize();
	value_type* cloud = new value_type[new_capacity];
	if (new_capacity >= maxSize) {
		for (int i = 0; i < size; ++i) {
			cloud[i] = (*this)[i];
		}
	}
	else {
		for (int j = 0; j < new_capacity; ++j) {
			cloud[j] = (*this)[j];
		}
		if (size > new_capacity) {
			size = new_capacity;
		}
		end = size - 1;
	}
	delete[] buffer;
	buffer = cloud;
	maxSize = new_capacity;
}

CircularBuffer& CircularBuffer::operator=(const CircularBuffer& cb) {
	(*this).Set_capacity(cb.Capacity());
	maxSize = cb.Capacity();
	for (int i = 0; i < cb.Capacity(); ++i) {
		(*this)[i] = cb.buffer[i];
	}
	start = 0;
	end = maxSize - 1;
	size = cb.Size();
	return (*this);
}

bool CircularBuffer::operator==(const CircularBuffer& cb) {
	int flag = 0;
	if (cb.Size() > (*this).Size() || cb.Size() < (*this).Size()) {
		return false;
	}
	for (int i = 0; i < (*this).Size(); ++i) {
		if ((*this)[i] == cb.buffer[i]) {
			++flag;
		}
	}
	if (flag == (*this).Size()) {
		return true;
	}
	else {
		return false;
	}
	
}

void CircularBuffer::Resize(int new_size, const value_type item) {
	int memory = (*this).Size();
	(*this).Set_capacity(new_size);
	if (new_size > memory) {
		for (int i = memory; i < new_size; ++i) {
			(*this)[i] = item;
			++size;
		}
		end = new_size - 1;
	}
}

void CircularBuffer::Rotate(int new_begin) {
	start = new_begin;
	end = Module(new_begin - 1);
	(*this).Linearize();
}

void CircularBuffer::Swap(CircularBuffer& cb) {
	std::swap((*this).maxSize, cb.maxSize);
	std::swap((*this).size, cb.size);
	std::swap((*this).start, cb.start);
	std::swap((*this).end, cb.end);
	std::swap(buffer, cb.buffer);
}

void CircularBuffer::Insert(int pos, const value_type item) {
	if ((*this).Is_linearized() == false) {
		(*this).Linearize();
	}
	(*this)[pos] = item;
}

void CircularBuffer::Erase(int first, int last) {
	if ((*this).Is_linearized() == false) {
		(*this).Linearize();
	}
	std::rotate(buffer, buffer + first, buffer + last);
	end = size - 1;
	for (int i = 0; i < (last - first); ++i) {
		(*this)[i] = NULL;
		size -= 1;
	}
	start = (last - first);
	std::rotate(buffer,buffer+start,buffer+end+1);
	start = 0;
	end = size - 1;
}

void CircularBuffer::Clear() {
	delete[] buffer;
	value_type* cloud = new value_type[maxSize];
	buffer = cloud;
	start = 0;
	end = -1;
	size = 0;
}