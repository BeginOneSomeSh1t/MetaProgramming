#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <chrono>

#define STD_ON using namespace std

template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}

std::ostream& operator<<(std::ostream& os, const std::chrono::time_point<std::chrono::system_clock>& t)
{
	const auto tt{ std::chrono::system_clock::to_time_t(t) };
	const auto loct{ std::localtime(&tt) };
	return os << std::put_time(loct, "%c");
}

using days = std::chrono::duration 
< std::chrono::hours::rep, 
	std::ratio_multiply<std::chrono::hours::period, std::ratio<24>>>;


constexpr days operator ""_days(unsigned long long h)
{
	return days{ h };
}

int main(int argc, char**argv)
{
	STD_ON;
	auto now{ chrono::system_clock::now() };
	print_whatever("The current date and time is ", now, '\n');

	chrono::hours chrono_12h{ 12 };
	print_whatever("In 12 hourse it'll be: ", (now + chrono_12h), '\n');

	using namespace chrono_literals;
	print_whatever("12 hours and 15 minutes ago it was ", (now - 12h - 15min), '\n');
	print_whatever("One week ago: ", (now - 7_days), '\n');
	
}