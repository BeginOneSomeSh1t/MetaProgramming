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




int main()
{
	STD_ON;
	
	print({});
	print("a const char* array");
	print("an std::string_view literla"sv);
	print("an std::string instance"s);

	print("  \t\n foobar \n\t");

	char cstr[]{ 'a', 'b', 'c' };
	print(string_view(cstr, sizeof(cstr)));

	
}