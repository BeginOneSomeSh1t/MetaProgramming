#pragma once
#include <iostream>
#include <iomanip>
#include <locale>
#include <fstream>

namespace std
{
	void print_aligned_demo(int val, size_t width, char fill_char = ' ')
	{
		cout << setfill(fill_char);
		cout << left << setw(width) << val << '\n';
		cout << right << setw(width) << val << '\n';
		cout << internal << setw(width) << val << '\n';
	}

	class redirect_cout_region
	{
		using buftype = decltype(cout.rdbuf());
		ofstream ofs;
		buftype buf_backup;
	public:
		explicit
		redirect_cout_region(const string& filename)
			: ofs{filename},
			buf_backup{cout.rdbuf(ofs.rdbuf())}
		{}
		redirect_cout_region()
			:ofs{},
			buf_backup{cout.rdbuf(ofs.rdbuf())}
		{}
		~redirect_cout_region()
		{
			cout.rdbuf(buf_backup);
		}
	};

	void my_output_heavy_function()
	{
		cout << "Some output\n";
		cout << "This does really heavy work\n";
		cout << "....alotta it....\n";
		//....
	}
}