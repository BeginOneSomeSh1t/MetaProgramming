#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <tuple>
#include <cctype>
#include <string_view>
#include <vector>

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

	// word count for string as well as for a file
	template<typename _Ty>
	size_t wordcount(_Ty& is)
	{
		return distance(istream_iterator<string>{is}, {});
	}

	vector<string> split_string(const string& s)
	{
		vector<string> r;
		for (auto next_it{ begin(s) }; next_it != end(s);)
		{
			auto word_end_it{ find(next_it, end(s), ' ') };
			r.emplace_back(next_it, word_end_it);
			if (word_end_it == end(s))
			{
				if (auto it = find(begin(r.back()), end(r.back()), '\n'); it != end(r.back()))
				{
					string word_without_endl{begin(r.back()), it};
					r.pop_back();
					r.emplace_back(word_without_endl);
				}
				break;
			}

			next_it = next(word_end_it);
		}
		return r;
	}
}


namespace std
{
	static constexpr char tolow(char c)
	{
		switch (c)
		{
		case 'A': return c - 'A' + 'a';
		case 'B': return c - 'B' + 'b';
		case 'C': return c - 'C' + 'c';
		case 'D': return c - 'D' + 'd';
		case 'E': return c - 'E' + 'e';
		case 'F': return c - 'F' + 'f';
		case 'G': return c - 'G' + 'g';
		case 'H': return c - 'H' + 'h';
		case 'I': return c - 'I' + 'i';
		case 'J': return c - 'J' + 'j';
		case 'K': return c - 'K' + 'k';
		case 'L': return c - 'L' + 'l';
		case 'M': return c - 'M' + 'm';
		case 'N': return c - 'N' + 'n';
		case 'O': return c - 'O' + 'o';
		case 'P': return c - 'P' + 'p';
		case 'Q': return c - 'Q' + 'q';
		case 'R': return c - 'R' + 'r';
		case 'S': return c - 'S' + 's';
		case 'T': return c - 'T' + 't';
		case 'U': return c - 'U' + 'u';
		case 'V': return c - 'V' + 'v';
		case 'W': return c - 'W' + 'w';
		case 'X': return c - 'X' + 'x';
		case 'Y': return c - 'Y' + 'y';
		case 'Z': return c - 'Z' + 'z';

		default: return c;
			break;
		}
	}

	class lc_traits : public char_traits<char>
	{
	public:
		static constexpr
		void assign(char_type& r, const char_type& a)
		{
			r = tolow(a);
		}
		static char_type* copy(char_type* dest,
			const char_type* src,
			size_t count)
		{
			transform(src, src + count, dest, tolow);
			return dest;
		}
	};

	class ci_traits : public char_traits<char>
	{
	public:
		static constexpr bool eq(char_type a, char_type b)
		{
			return tolow(a) == tolow(b);
		}
		static constexpr bool lt(char_type a, char_type b)
		{
			return tolow(a) < tolow(b);
		}
		static constexpr int compare(const char_type* s1,
			const char_type* s2,
			size_t count)
		{
			for (; count; ++s1, ++s2, --count)
			{
				const char_type diff{ tolow(*s1) - tolow(*s2) };
				if (diff < 0) return -1;
				if (diff > 0) return +1;
			}
			return 0;
		}
		static constexpr
			const char_type* find(const char_type* p,
				size_t count,
				const char_type& ch)
		{
			const char_type find_c{ tolow(ch) };
			for (; count != 0; --count, ++p)
			{
				if (find_c == tolow(*p)) return p;
			}
			return nullptr;
		}
	};

	using lc_string = basic_string<char, lc_traits>;
	using ci_string = basic_string<char, ci_traits>;

	ostream& operator <<(ostream& os, const lc_string& str)
	{
		return os.write(str.data(), str.size());
	}
	ostream& operator<<(ostream& os, const ci_string& str)
	{
		return os.write(str.data(), str.size());
	}
}