#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <tuple>

namespace std
{
	template<typename _It>
	tuple<_It, char, size_t> occurrences(_It it, _It end_it)
	{
		if (it == end_it) return { end_it, '?', 0 };
		const char c{ *it };
		const auto diff_it{ find_if(it, end_it, [c](char x) { return c != x; }) };
		return { diff_it, c, distance(it, diff_it) };
	}

	string compress(const string& s)
	{
		const auto it_end(end(s));
		stringstream f;
		for (auto it{ begin(s) }; it != it_end;)
		{
			const auto [diff_it, c, d] {occurrences(it, it_end)};
			if(!isdigit(c))
				f << c << d;
			it = diff_it;
		}
		return f.str();
	}

	string decompress(const string& s)
	{
		stringstream ss{ s };
		stringstream f;

		char c;
		size_t n;
		while (ss >> c >> n) { f << string(n, c); };
		return f.str();
	}
}