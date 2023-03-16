#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <tuple>
#include <cctype>
#include <string_view>

namespace std
{

	// string compression

	/*Finds the first char in the it range that is not equal the current one*/
	template<typename _It>
	tuple<_It, char, size_t> occurrences(_It it, _It end_it)
	{
		if (it == end_it) return { end_it, '?', 0 };
		const char c{ *it };
		const auto diff_it{ find_if(it, end_it, [c](char x) { return c != x; }) };
		return { diff_it, c, distance(it, diff_it) };
	}
	/*Compresses a string to a character with a number of its repetition (e.g.: aaaaa - > a5 )*/
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
	/*This is oppsite actions of the compress function. Decompresses a string from
	a view of char5 to the view of charcharcharcharchar*/
	string decompress(const string& s)
	{
		stringstream ss{ s };
		stringstream f;

		char c;
		size_t n;
		while (ss >> c >> n) { f << string(n, c); };
		return f.str();
	}

	/*Trims \t,\n and ' ' characters in the passed string. (creates a copy when returning)*/
	string trim_whitespace_surrounding(const string& s)
	{
		const char whitespace[]{ " \t\n" };
		const size_t first{ s.find_first_not_of(whitespace) };
		if (string::npos == first) return{};
		const size_t last{ s.find_last_not_of(whitespace) };
		return s.substr(first, (last - first + 1));
	}

	/*This function realizes the berries of std::string_view class*/
	void print(string_view v)
	{
		// trim whitespaces of string_view string type
		const auto words_begin{ v.find_first_not_of(" \t\n") };
		v.remove_prefix(min(words_begin, v.size()));

		const auto words_end{ v.find_last_not_of(" \t\n") };
		if (words_end != string_view::npos)
			v.remove_suffix(v.size() - words_end - 1);

		cout << "Lenght: " << v.length()
			<< " [" << v << "]\n";
	}
}