#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <chrono>
#include <thread>

template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}

using namespace std;
using namespace chrono_literals;

int main(int argc, char**argv)
{
	cout << "Going to sleep for 5 seconds and 300 ms.\n";
	this_thread::sleep_for(5s + 300ms);

	cout << "Sleep for another 3 seconds\n";
	this_thread::sleep_until(
		chrono::high_resolution_clock::now() + 3s
	);

	cout << "That's it";
	

}