#pragma once
#include <iostream>
#include <iomanip>
#include <locale>
#include <fstream>
#include <sstream>
#include <mutex>

namespace std
{
	void print_aligned_demo(int val, size_t width, char fill_char = ' ')
	{
		cout << setfill(fill_char);
		cout << left << setw(width) << val << '\n';
		cout << right << setw(width) << val << '\n';
		cout << internal << setw(width) << val << '\n';
	}

	void my_output_heavy_function()
	{
		cout << "Some output\n";
		cout << "This does really heavy work\n";
		cout << "....alotta it....\n";
		//....
	}
}

namespace std
{
	class redirect_cout_region
	{
		using buftype = decltype(cout.rdbuf());
		ofstream ofs;
		buftype buf_backup;
	public:
		explicit
			redirect_cout_region(const string& filename)
			: ofs{ filename },
			buf_backup{ cout.rdbuf(ofs.rdbuf()) }
		{}
		redirect_cout_region()
			:ofs{},
			buf_backup{ cout.rdbuf(ofs.rdbuf()) }
		{}
		~redirect_cout_region()
		{
			cout.rdbuf(buf_backup);
		}
	};
	
	/*Resets all cout flags when destructor fires*/
	class format_guard
	{
		decltype(cout.flags()) f{ cout.flags() };
	public:
		~format_guard() { cout.flags(f); }
	};

	template<typename _Ty>
	struct scientific_type
	{
		_Ty value;
		explicit scientific_type(_Ty val) : value{val}{}
	};

	template<typename _Ty>
	ostream& operator << (ostream& os, const scientific_type<_Ty>& w)
	{
		format_guard g;
		os << scientific << uppercase << showpos;
		return os << w.value;
	}


	struct pcout : stringstream
	{
		static inline mutex cout_mutex;
		~pcout()
		{
			lock_guard<mutex> l{ cout_mutex };
			cout << rdbuf();
			cout.flush();
		}	
	};
}