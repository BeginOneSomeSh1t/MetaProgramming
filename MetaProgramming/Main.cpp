#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <thread>
#include <string>
#include "stream_plus.h"
#include <future>

template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}

using namespace std;
using namespace chrono_literals;

static string create(const char* s)
{
	pcout{} << "3s CREATE " << quoted(s) << '\n';
	this_thread::sleep_for(3s);
	return { s };
}

static string concat(const string& a, const string& b)
{
	pcout{} << "5s CONCAT"
		<< quoted(a) << " "
		<< quoted(b) << "\n";
	this_thread::sleep_for(5s);
	return a + b;

}

static string twice(const string& s)
{
	pcout{} << "3s TWICE " << quoted(s) << '\n';
	this_thread::sleep_for(3s);
	return s + s;
}

template<typename _F>
static auto asynchronize(_F f)
{
	return [f](auto...xs)
	{
		return [=]()
		{
			return async(launch::async, f, xs...);
		};
	};
}

template<typename _F>
static auto fut_unwrap(_F f)
{
	return [f](auto...xs)
	{
		return f(xs.get()...);
	};
}

template<typename _F>
static auto async_adapter(_F f)
{
	return [f](auto...xs)
	{
		return [=]()
		{
			return async(launch::async, fut_unwrap(f), xs()...);
		};
	};
}


int main(int argc, char**argv)
{
	auto pcreate{ asynchronize(create) };
	auto pconcat{ async_adapter(concat) };
	auto ptwice{ async_adapter(twice) };
	
	auto result(
		pconcat(
			ptwice(
				pconcat(
					pcreate("foo "),
					pcreate("bar "))),
			pconcat(
				pcreate("this "),
				pcreate("that "))));

	cout << "Setup done. Nothing executed yet.\n";
	cout << result().get() << '\n';
}