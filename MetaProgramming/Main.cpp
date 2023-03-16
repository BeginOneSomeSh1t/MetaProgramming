#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <list>
#include <vector>
#include <functional>
#include "string_plus.h"
#include <string_view>
#include <sstream>
#include <fstream>
#include "stream_plus.h"

#define STD_ON using namespace std

template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}

namespace std
{
	template<typename _Ty>
	ostream& operator<<(ostream& os, vector<_Ty>& v)
	{
		copy(begin(v), end(v),
			ostream_iterator<_Ty>{cout, ", "});
		return os;
	}
}




int main(int argc, char**argv)
{
	STD_ON;
	
	print_aligned_demo(12345, 15);
	print_aligned_demo(123456, 15, '_');

	cout << hex << showbase;
	print_aligned_demo(0x123abc, 15);

	cout << oct;
	print_aligned_demo(0123456, 15);

	print_whatever("A hex number with upper case letters: ", hex, uppercase, 0x123abc, '\n');
	print_whatever("A number: ", 100, '\n');
	print_whatever(dec);
	print_whatever("Now in decimal again: ", 100, '\n');


	print_whatever(12.3, showpoint, 12.0, '\n');

	print_whatever("scientific: ", scientific, 1230000000.13, '\n');
	print_whatever(fixed, "Now fixed: ", 123000000.13, '\n');

	
}