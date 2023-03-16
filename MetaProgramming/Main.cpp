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
	
	print_whatever("Please enter tow numbers: \n");
	int x;
	double y;
	if (cin >> x >> y)
		print_whatever("You entered: ", x, " and ", y, "\n");
	else
	{
		print_whatever("Oh that did not work out!\n");
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	print_whatever("Please< enter some comma-separated names: \n");
	for (string s; getline(cin >> ws, s, ',');)
	{
		if (s.empty())
			break;
		print_whatever("name: ", s, '\n');
	}

	
}