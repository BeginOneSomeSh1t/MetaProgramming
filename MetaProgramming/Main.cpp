#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <filesystem>
#include "string_plus.h"


template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}

using namespace std;
using namespace filesystem;

static size_t entry_size(const directory_entry& entry)
{
	if (!is_directory(entry)) return file_size(entry);
	return accumulate(directory_iterator{ entry }, {}, 0u,
		[](size_t accum, const directory_entry& e)
		{
			return accum + entry_size(e);
		});
}



int main(int argc, char**argv)
{
	args_string args{ args_string::unskip_ws{} };
	path dir{ args.argc > 1 ? args[1] : "." };
	if (!exists(dir))
	{
		cout << "Path " << dir << " does not exist.\n";
		return 1;
	}

	for (const auto& entry : directory_iterator{ dir })
	{
		cout << setw(5) << right
			<< size_string(entry_size(entry))
			<< " " << entry.path().filename().string()
			<< '\n';
	}
}