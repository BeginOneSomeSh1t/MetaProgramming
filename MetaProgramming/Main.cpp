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
	
	size_t wc;

	if (argc == 2)
	{
		ifstream ifs{ argv[1] };
		wc = wordcount(ifs);
	}
	else
		wc = wordcount(cin);

	print_whatever("There are ", wc, " words\n");

	
}