#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <algorithm>
#include "random_plus.h"

template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}

using namespace std;




int main(int argc, char**argv)
{
	
	size_t partitions{0};
	size_t samples{0};

	print_whatever("Please, enter partitions samples: ");
	string s;
	while (true)
	{

		if (getline(cin, s))
		{
			istringstream ss{ s };

			if (!(ss >> partitions >> samples))
			{
				print_whatever("You entered incorrect input, try that again: ");
				continue;
			}

			
		}

		print_whatever("Random device: ", '\n');
		histogram<random_device>(partitions, samples);

		print_whatever("\ndefault_random engine: ", '\n');
		histogram<default_random_engine>(partitions, samples);
		cout << "nminstd_rand0" << '\n';
		histogram<minstd_rand0>(partitions, samples);
		cout << "nminstd_rand" << '\n';
		histogram<minstd_rand>(partitions, samples);
		cout << "nmt19937" << '\n';
		histogram<mt19937>(partitions, samples);
		cout << "nmt19937_64" << '\n';
		histogram<mt19937_64>(partitions, samples);
		cout << "nranlux24_base" << '\n';
		histogram<ranlux24_base>(partitions, samples);
		cout << "nranlux48_base" << '\n';
		histogram<ranlux48_base>(partitions, samples);
		cout << "nranlux24" << '\n';
		histogram<ranlux24>(partitions, samples);
		cout << "nranlux48" << '\n';
		histogram<ranlux48>(partitions, samples);
		cout << "nknuth_b" << '\n';
		histogram<knuth_b>(partitions, samples);

		break;
	}
	

}