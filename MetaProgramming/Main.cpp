#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <filesystem>
#include "string_plus.h"


template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}

using namespace std;
using namespace filesystem;

using ext_info = map<string, pair<size_t, size_t>>;

static ext_info ext_stats(const path& dir)
{
	ext_info m;
	for (const auto& entry :
		recursive_directory_iterator{ dir })
	{
		const path p{ entry.path() };
		const file_status fs{ status(p) };
		if (is_directory(fs)) { continue; }
		const string ext{ p.extension().string() };
		if (ext.length() == 0)
			continue;

		const size_t size{ file_size(p) };
		auto& [size_accum, count] = m[ext];
		size_accum += size;
		count += 1;
	}
	return m;
}



int main(int argc, char**argv)
{
	args_string args{};
	path dir{ args.argc > 1 ? args[1] : "." };
	if (!exists(dir))
	{
		cout << "Path " << dir << " does not exist";
		return 1;
	}

	for (const auto& [ext, stats] : ext_stats(dir))
	{
		const auto& [accum_size, count] = stats;
		cout << setw(15) << left << ext << ": "
			<< setw(4) << right << count
			<< " items, avg size "
			<< setw(4) << size_string(accum_size / count)
			<< '\n';
	}
}