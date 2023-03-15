#pragma once
#include <algorithm>
#include <iterator>


template<typename _It, typename _Pred>
std::pair<_It, _It> gather(_It first, _It last, _It gather_pos, _Pred pred)
{
	return { std::stable_partition(first, gather_pos, std::not_fn(pred)), std::stable_partition(gather_pos, last, pred) };
}

template <typename It, typename F>
void gather_sort(It first, It last, It gather_pos, F comp_func)
{
	auto inv_comp_func([&](const auto &...ps) {
		return !comp_func(ps...);
		});
	std::stable_sort(first, gather_pos, inv_comp_func);
	std::stable_sort(gather_pos, last, comp_func);
}


//Possible implementation
// 
// 
//auto is_a([](char c) { return c == 'a'; });
//string a{ "a_a_a_a_a_a_a_a_a_a" };
//
//auto middle{ begin(a) + a.size() / 2 };
//gather(begin(a), end(a), middle, is_a);
//cout << a << '\n';
//
//gather(begin(a), end(a), begin(a), is_a);
//cout << a << '\n';
//gather(begin(a), end(a), end(a), is_a);
//cout << a << '\n';
//
//gather(begin(a), end(a), middle, is_a);
//cout << a << '\n';
//
//string b{ "_9_2_4_7_3_8_1_6_5_0_" };
//gather_sort(begin(b), end(b), begin(b) + b.size() / 2,
//	less<char>{});
//cout << b << '\n';