#include <iostream>
#include <chrono>
#include <ratio>
#include <cmath>
#include <iomanip>
#include <optional>

#define STD_ON using namespace std

template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}

using seconds = std::chrono::duration<double>;

using miliseconds = std::chrono::duration<double, std::ratio_multiply<seconds::period, std::milli>>;

using microseconds = std::chrono::duration<double, std::ratio_multiply<seconds::period, std::micro>>;


static std::pair<std::string, seconds> get_input()
{
	std::string s;
	const auto tic{ std::chrono::steady_clock::now() };
	if (!(std::cin >> s))
		return { {}, {} };
	const auto toc{ std::chrono::steady_clock::now() };
	return { s, toc - tic };
}

int main(int argc, char**argv)
{
	STD_ON;
	while (true)
	{
		print_whatever("Please, type the word \"C++17\" as fast as you can.\n");
		const auto [user_input, diff] {get_input()};
		if (user_input == "") break;
		if (user_input == "C++17")
		{
			print_whatever("Bravo!. You did that!:\n");
			print_whatever(fixed, setprecision(2), setw(12), diff.count(), " seconds.\n");
			print_whatever(setw(12), miliseconds(diff).count(), " miliseconds.\n");
			print_whatever(setw(12), microseconds(diff).count(), " microseconds.\n");
			break;
		}
		else
			print_whatever("Sorry, your input does not match, try again!\n");
	}

	
}