#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <list>

template<typename _In_it, typename _Out_it, typename _Ty, typename _Fun>
_In_it split(_In_it it, _In_it end_it, _Out_it out_it, _Ty split_val, _Fun bin_func)
{
	while (it != end_it)
	{
		auto slice_end{ std::find(it, end_it, split_val) };
		*out_it++ = bin_func(it, slice_end);
		if (slice_end == end_it) return end_it;
		it = std::next(slice_end);
	}
	return it;
}


//Possible implementation
// 
// 
//const string s{ "a-b-c-d-e-f-g" };
//auto bin_func
//{
//	[](auto it_a, auto it_b)
//	{
//		return string{it_a, it_b};
//	}
//};
//
//list<string> l;
//split(begin(s), end(s), back_inserter(l), '-', bin_func);
//copy(begin(l), end(l), ostream_iterator<string>{cout, "\n"});