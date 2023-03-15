#pragma once
#include <iterator>

namespace std
{
	class cstring_iterator_sentinel {};

	class cstring_iterator
	{
		const char* s{ nullptr };
	public:
		explicit cstring_iterator(const char* str)
			: s{ str }
		{}
		char operator*() const { return *s; }
		cstring_iterator& operator++()
		{
			++s;
			return *this;
		}
		bool operator!=(const cstring_iterator_sentinel) const
		{
			return s != nullptr && *s != '\0';
		}
	};

	class cstring_range
	{
		const char* s{ nullptr };
	public:
		cstring_range(const char* str)
			:
			s{ str }
		{}
		cstring_iterator begin() const
		{
			return cstring_iterator{ s };
		}
		cstring_iterator_sentinel end() const
		{
			return {};
		}
	};


	class num_iterator
	{
		size_t i;
	public:
		num_iterator(size_t position = 0)
			:i{ position }
		{}
		size_t operator*() const { return i; }
		num_iterator& operator++()
		{
			++i;
			return *this;
		}
		bool operator!=(const num_iterator& r) const
		{
			return i != r.i;
		}
	};

	template<>
	struct iterator_traits<num_iterator>
	{
		using iterator_category = forward_iterator_tag;
		using value_type = size_t;
		using difference_type = size_t;
	};


	class num_range
	{
		size_t a, b;
	public:
		explicit num_range(size_t from, size_t to)
			: a{ from }, b{ to }
		{}
		num_iterator begin() const
		{
			return num_iterator{ a };
		}
		num_iterator end() const
		{
			return num_iterator{ b };
		}
		template<typename _Fc>
		explicit num_range(size_t from, size_t to, _Fc fun)
			:a{ from }, b{ to }
		{
			for (; a != b; ++a)
				fun(a);
		}
	};

	template<class _It>
	class it_range
	{
		_It it_begin;
		_It it_end;
	public:
		explicit it_range(_It b, _It e)
			:it_begin{ b }, it_end{ e }
		{}
		template<typename _Func>
		explicit it_range(_It b, _It e, _Func fun)
			: it_begin{ b }, it_end{ e }
		{
			(*this)(fun);
		}
		template<typename _Func>
		void operator()(_Func fun)
		{
			for (auto it = it_begin; it != it_end; ++it)
				fun(it);
		}
	};
}