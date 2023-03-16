#pragma once
#include <iostream>
#include <iomanip>
#include <locale>

namespace std
{
	void print_aligned_demo(int val, size_t width, char fill_char = ' ')
	{
		cout << setfill(fill_char);
		cout << left << setw(width) << val << '\n';
		cout << right << setw(width) << val << '\n';
		cout << internal << setw(width) << val << '\n';
	}
}