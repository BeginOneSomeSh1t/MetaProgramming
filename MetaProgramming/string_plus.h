#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <tuple>
#include <cctype>

namespace std
{

	// string compression
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


	string trim_whitespace_surrounding(const string& s)
	{
		const char whitespace[]{ " \t\n" };
		const size_t first{ s.find_first_not_of(whitespace) };
		if (string::npos == first) return{};
		const size_t last{ s.find_last_not_of(whitespace) };
		return s.substr(first, (last - first + 1));
	}
}