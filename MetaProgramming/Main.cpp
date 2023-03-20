#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <filesystem>


template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}

using namespace std;
using namespace filesystem;

static vector<pair<size_t, string>>
matches(const path& p, const regex& re)
{
	vector<pair<size_t, string>> d;
	// possible mistake
	ifstream is{ p.c_str() };
	string s;
	for (size_t line{ 1 }; getline(is, s); ++line)
	{
		if (regex_search(begin(s), end(s), re))
			d.emplace_back(line, s);
	}
	return d;
}


int main(int argc, char**argv)
{
	string regex_s{ istream_iterator<char>{cin}, { } };

	if (regex_s.empty())
	{
		cout << "Empty. Enter someting\n";
		return 1;
	}

	regex pattern;
	try
	{
		pattern = regex{ regex_s };
	}
	catch (const regex_error er)
	{
		cout << "Invalid regulare expression provided.\n";
		return 1;
	}

	for (const auto& entry : recursive_directory_iterator{ current_path() })
	{
		auto ms{ matches(entry.path(), pattern) };
		for (const auto& [number, content] : ms)
		{
			cout << entry.path().string() << " : " << number
				<< " - " << content << '\n';
		}
	}
}