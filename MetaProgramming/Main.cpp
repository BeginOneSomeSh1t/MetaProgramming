#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <regex>
#include <vector>
#include <filesystem>
#include "string_plus.h"


template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}

using namespace std;
using namespace filesystem;

template<typename _Ty>
static string replace(string s, const _Ty& replacements)
{
	for (const auto& [pattern, repl] : replacements)
		s = regex_replace(s, pattern, repl);
	return s;
}



int main(int argc, char**argv)
{
	cin.unsetf(ios::skipws);
	string patterns_replacements{ istream_iterator<char>{cin}, {} };

	auto split_pr{ split_string(patterns_replacements) };
	if (split_pr.size() < 3)
	{
		cout << "Usage: " << split_pr[0]
			<< " <pattern> <replacement> ...\n";
		return 1;
	}

	vector<pair<regex, string>> patterns;
	for (int i{ 0 }; i < split_pr.size(); i += 2)
		patterns.emplace_back(split_pr[i], split_pr[i + 1]);

	for (const auto& entry :
		recursive_directory_iterator{ current_path() })
	{
		path opath{ entry.path() };

		string rname{ replace(opath.filename().string(), patterns) };
		
		path rpath{ opath };
		rpath.replace_filename(rname);

		if (opath != rpath)
		{
			cout << opath.string() << " --> "
				<< rpath.filename().string() << '\n';
			if (exists(rpath))
			{
				cout << "Can't rename."
					" Destination file exists.\n";
			}
			else
				rename(opath, rpath);
		}
	}

}