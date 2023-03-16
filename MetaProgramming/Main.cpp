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
#include <unordered_map>

#define STD_ON using namespace std

template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}

std::string word_num(int i)
{
	std::unordered_map<int, std::string> m
	{
		{1, "one"},
		{2, "two"},
		{3, "three"},
		{4, "four"},
		{5, "five"},
	};
	const auto match{ m.find(i) };
	if (match == std::end(m))
		return "Unknown";
	return match->second;
}

struct bork
{
	int borks;
	bork(int i) : borks{i}{}

	void print(std::ostream& os) const
	{
		using namespace std::string_literals;
		std::fill_n(std::ostream_iterator<std::string>{os, " "}, borks, "bork!"s);
	}
};

std::ostream& operator<<(std::ostream& os, const bork& b)
{
	b.print(os);
	return os;
}

int main(int argc, char**argv)
{
	STD_ON;
	
	print_whatever("string: ", string{ "Foo Bar Baz" });
	print_whatever("lc_string: ", lc_string{ "Foo Bar Baz" });
	print_whatever("ci_string: ", ci_string{ "Foo Bar Baz" });

	ci_string user_input{ "MaGiC pASSword!" };
	ci_string pass{ "magic password!" };

	if (user_input == pass)
		print_whatever("Passes match: ", user_input, " == ", pass, '\n');
}