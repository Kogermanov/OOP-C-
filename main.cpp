#include "buffer.h"
#include <iostream>
#include <cassert>
#include <algorithm>

int main() {
	int a[] = { 5,7,1,2,3,9,4,6 };
	CircularBuffer buf(8, a);
	buf.Push_front(0);
	buf.Push_front(0);
	buf.Erase(3,6);
	buf.Print();
	return 0;
}