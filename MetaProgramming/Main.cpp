#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <random>
#include <map>
#include <string>
#include <algorithm>


template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}

using namespace std;

template<typename _Ty>
void print_distro(_Ty distro, size_t samples)
{
	default_random_engine e;
	map<int, size_t> m;

	for (size_t i(0); i < samples; ++i)
		m[distro(e)] += 1;

	size_t max_elm(max_element(begin(m), end(m),
		[](const auto& a, const auto& b) {
			return a.second < b.second;
		})->second);

	size_t max_div(max(max_elm / 100, size_t(1)));

	for (const auto [randval, count] : m)
	{
		if (count < (max_elm / 100))
			continue;
		cout << setw(3) << randval << " : "
			<< string(count / max_div, '*') << '\n';
	}
}


int main(int argc, char**argv)
{
	
	size_t samples(0);

	if (!(cin >> samples))
		return 0;

	cout << "uniform_int_distribution\n";
	print_distro(uniform_int_distribution<int>(0, 9), samples);
	cout << "normal distibution: \n";
	print_distro(normal_distribution<double>(0.0, 2.0), samples);

	initializer_list<double> intervals{ 0, 5, 10, 30 };
	initializer_list<double> weights{ .2, .3, .5 };
	cout << "piecesize_constant_distribution\n";
	print_distro(
		piecewise_constant_distribution<double>
	{
		begin(intervals), end(intervals),
		begin(weights)
	}, 
		samples
	);

	cout << "piecewise_linear_distibution\n";
	initializer_list<double> weights2{ 0,1,1,0 };
	print_distro(
		piecewise_linear_distribution<double>
	{
		begin(intervals), end(intervals), begin(weights2)
	},
		samples
	);

	cout << "bernoulli distribution\n";
	print_distro(bernoulli_distribution(0.75), samples);
	cout << "discrete distribution\n";
	print_distro(discrete_distribution<int>({ 1,2,4,8 }), samples);
	cout << "binomial_distribution\n";
	print_distro(binomial_distribution<int>{10, 0.3}, samples);
	cout << "negative_binomial_distribution\n";
	print_distro(
		negative_binomial_distribution<int>{10, 0.8},
		samples);
	cout << "geometric_distribution\n";
	print_distro(geometric_distribution<int>{0.4}, samples);
	cout << "exponential_distribution\n";
	print_distro(exponential_distribution<double>{0.4}, samples);
	cout << "gamma_distribution\n";
	print_distro(gamma_distribution<double>{1.5, 1.0}, samples);
		cout << "weibull_distribution\n";
	print_distro(weibull_distribution<double>{1.5, 1.0}, samples);
	cout << "extreme_value_distribution\n";
	print_distro(
		extreme_value_distribution<double>{0.0, 1.0},
		samples);
	cout << "lognormal_distribution\n";
	print_distro(lognormal_distribution<double>{0.5, 0.5}, samples);
	cout << "chi_squared_distribution\n";
	print_distro(chi_squared_distribution<double>{1.0}, samples);
	cout << "cauchy_distribution\n";
	print_distro(cauchy_distribution<double>{0.0, 0.1}, samples);
	cout << "fisher_f_distribution\n";
	print_distro(fisher_f_distribution<double>{1.0, 1.0}, samples);
	cout << "student_t_distribution\n";
	print_distro(student_t_distribution<double>{1.0}, samples);

}