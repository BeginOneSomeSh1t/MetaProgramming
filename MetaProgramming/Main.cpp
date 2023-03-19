#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <thread>
#include <mutex>
#include <sstream>
#include <vector>
template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}

using namespace std;
using namespace chrono_literals;

struct pcout : public stringstream
{
	static inline mutex cout_mutex;
	~pcout()
	{
		lock_guard g{ cout_mutex };
		cout << rdbuf();
		cout.flush();
	}
};


static void print_cout(int id)
{
	cout << "Cout hello from" << id << '\n';
}
static void print_pcout(int id)
{
	pcout{} << "pcout hello from" << id << '\n';
}


int main(int argc, char**argv)
{
	vector<thread> vt;
	for (size_t i{ 0 }; i < 10; ++i)
		vt.emplace_back(print_cout, i);

	for (auto& t : vt)
		t.join();

	cout << "======================\n";

	vt.clear();
	for (size_t i{ 0 }; i < 10; ++i)
		vt.emplace_back(print_pcout, i);
	for (auto& t : vt)
		t.join();



}