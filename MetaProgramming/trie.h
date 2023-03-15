#pragma once
#include <string>
#include <optional>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>


namespace std
{

	template<typename _Ty>
	class trie
	{
		std::map<_Ty, trie> tries;
	public:
		static std::function<void(std::vector<_Ty>&)> print_delegate;
	public:
		static std::map<_Ty, std::size_t> occurance_count_map;
		auto find_average_occurance() const
		{
			auto accum{ std::accumulate(std::begin(occurance_count_map), std::end(occurance_count_map), 0, [](auto sum, auto& p) { return sum + p.second; }) };
			return (accum / occurance_count_map.size());
		}
		template<typename _It>
		void insert(_It it, _It end_it)
		{
			if (it == end_it)
				return;
			++occurance_count_map[*it];
			tries[*it].insert(next(it), end_it);
		}
		template<typename _Cnt>
		void insert(const _Cnt& container)
		{
			insert(std::begin(container), std::end(container));
		}
		void insert(const std::initializer_list<_Ty>& il)
		{
			insert(std::begin(il), std::end(il));
		}
		void print(std::vector<_Ty>& v) const
		{
			if (tries.empty())
			{
				auto ave{ find_average_occurance() };
				std::partition(std::begin(v), std::end(v), [&](const _Ty& k) { return occurance_count_map[k] > ave; });
				print_delegate(v);
			}
			for (const auto& p : tries)
			{
				v.push_back(p.first);
				p.second.print(v);
				v.pop_back();
			}
		}
		void print() const
		{
			std::vector<_Ty> v;
			print(v);
		}

		template<typename _It>
		std::optional<std::reference_wrapper<const trie>>
			subtrie(_It it, _It end_it) const
		{
			if (it == end_it)
				return std::ref(*this);
			auto found{ tries.find(*it) };
			if (found == std::end(tries))
				return {};
			return found->second.subtrie(std::next(it), end_it);
		}
		template<typename _Cnt>
		auto subtrie(const _Cnt& c)
		{
			return subtrie(std::begin(c), std::end(c));
		}


	};
}
// allocate static member
template<typename _Ty>
std::map<_Ty, std::size_t> std::trie<_Ty>::occurance_count_map;
template<typename _Ty>
std::function<void(std::vector<_Ty>&)> std::trie<_Ty>::print_delegate;