#pragma once
#include <iostream>
#include <tuple>
#include <list>
#include <utility>
#include <string>
#include <iterator>
#include <numeric>
#include <algorithm>

namespace std
{
	template<typename _Ty, typename..._Ts>
	void print_args(ostream& os, const _Ty& v, const _Ts&...vs)
	{
		os << v;
		(void)initializer_list<int>{((os << ", " << vs), 0)...};
	}

	template<typename..._Ts>
	ostream& operator << (ostream& os, const tuple<_Ts...>& t)
	{
		auto print_to_os{ [&os](const auto&...xs) { print_args(os, xs...); } };
		os << "(";
		apply(print_to_os, t);
		return os << ")";
	}

	template<typename _Ty>
	tuple<double, double, double, double>
		sum_min_max_avg(const _Ty& range)
	{
		auto min_max{ minmax_element(begin(range), end(range)) };
		auto sum{ accumulate(begin(range), end(range), 0.) };
		return { sum, *min_max.first, *min_max.second, sum / range.size() };
	}

	template <typename T1, typename T2>
	static auto zip(const T1& a, const T2& b)
	{
		auto z([](auto ...xs) {
			return [xs...](auto ...ys) {
				return tuple_cat(make_tuple(xs, ys) ...);
			};
			});

		return apply(apply(z, a), b);
	}


}

