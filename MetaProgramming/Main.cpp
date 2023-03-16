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
#include <regex>
#include <algorithm>
#include <iomanip>

#define STD_ON using namespace std

template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}



int main(int argc, char**argv)
{
	STD_ON;
	// format guard test
	{
		format_guard g;
		print_whatever(hex, scientific, showbase, uppercase);
		print_whatever("Numbers with special formatting:\n");
		print_whatever(0x123abc, '\n');
		print_whatever(0.123456789, '\n');
	}

	print_whatever("Same numbers but format_guard is dead now:\n");
	print_whatever(0x123abc, '\n');
	print_whatever(0.123456789, '\n');

	print_whatever("Mixed formatting: \n");
	print_whatever(123.0, ' ', scientific_type{123.0}, " ", 123.456, '\n');

	
}