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

// helper
template<typename _InputIt>
void print(_InputIt it, _InputIt end_it)
{
	while (it != end_it)
	{
		const std::string link{ *it++ };
		if (it == end_it) break;
		const std::string desc{ *it++ };
		print_whatever(std::left, std::setw(28), desc, ": ", link, '\n');
	}
}

int main(int argc, char**argv)
{
	STD_ON;
	cin >> noskipws;
	const string in{ istream_iterator<char>{cin}, {} };
	const regex link_re{ "<a href=\"([^\"]*)\"[^<]*>([^<]*)</a>" };
	sregex_token_iterator it{ begin(in), end(in), link_re, {1,2} };
	print(it, {});
	
}