#pragma once
#include <string>
#include <vector>
#include <random>
#include <limits>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <algorithm>


namespace std
{
	template<typename RD>
	void histogram(size_t partitions, size_t samples)
	{
		using rand_t = typename RD::result_type;
		partitions = max<size_t>(partitions, 10);

		RD rd;
		rand_t div((double(RD::max()) + 1) / partitions);

		vector<size_t> v(partitions);
		for (size_t i{ 0 }; i < samples; ++i) {
			++v[rd() / div];
		}


		rand_t max_elm(*max_element(begin(v), end(v)));
		rand_t max_div( max(max_elm / 100, rand_t{1}) );

		for (size_t i{ 0 }; i < partitions; ++i)
			cout << setw(2) << i << ": "
			<< string(v[i] / max_div, '*') << '\n';

	}
}