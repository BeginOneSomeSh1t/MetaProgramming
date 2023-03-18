#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <execution>

template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}

using namespace std;

static bool odd(int n) { return n % 2; }


int main(int argc, char**argv)
{
	vector<int> d(60000000);
	mt19937 gen;
	uniform_int_distribution<int> dis(0, 100000);
	auto rand_num([=]()mutable {return dis(gen); });

	generate(execution::par, begin(d), end(d), rand_num);

	sort(execution::par, begin(d), end(d));

	reverse(execution::par, begin(d), end(d));

	auto odds(count_if(execution::par, begin(d), end(d), odd));

	cout << (100.0 * odds / d.size())
		<< " % of the numbers are odd.\n";
	

}