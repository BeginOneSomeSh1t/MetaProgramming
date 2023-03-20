#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <filesystem>
#include "string_plus.h"


template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}

using namespace std;
using namespace filesystem;

static size_t hash_from_path(const path& p)
{
	ifstream is{ p.c_str(), ios::in || ios::binary };
	if (!is)
		throw errno;
	string s;
	is.seekg(0, ios::end);
	s.reserve(is.tellg());
	is.seekg(0, ios::beg);
	s.assign(istreambuf_iterator<char>{is}, {});
	return hash<string>{}(s);
}

static size_t reduce_dupes(const path& dir)
{
	unordered_map<size_t, path> m;
	size_t count{ 0 };
	for (const auto& entry :
		recursive_directory_iterator{ dir })
	{
		const path p{ entry.path() };
		if (is_directory(p))
			continue;
		const auto& [it, success] =
			m.try_emplace(hash_from_path(p), p);
		if (!success) {
			cout << "Removed " << p.string()
				<< " because it is a duplicate of "
				<< it->second.string() << '\n';
			remove(p);
			create_symlink(absolute(it->second), p);
			++count;
		}
	}
	return count;
}



int main(int argc, char**argv)
{
	setlocale(LC_ALL, "rus");
	args_string args{};

	if (args.argc != 1)
	{
		cout << "Usage: " << args[0] << " <path>\n";
		return 1;
	}
	path dir{ args[0] };
	if (!exists(dir))
	{
		cout << "Path " << dir << " doesn't exist\n";
		return 1;
	}
	try
	{
		const size_t dupes{ reduce_dupes(dir) };
		cout << "Removed " << dupes << " diplicates.\n";
	}
	catch (filesystem_error er)
	{
		cout << "Er: " << er.what() << '\n';
		return 1;
	}
	
}