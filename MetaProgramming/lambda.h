#pragma once
#include <xutility>

namespace std
{

	template<typename _Func>
	struct lambda
	{
		_Func p_fun;
		explicit lambda(_Func fun)
			: p_fun{ fun }
		{}
		lambda<decltype(&_Func::operator())> lambda_call;
		template<typename...Args>
		auto operator()(Args&&...args)
		{
			return lambda_call(p_fun, std::forward<Args>(args)...);
		}

	};

	template<typename _Class, typename _Ret, typename...Args>
	struct lambda<_Ret(_Class::*)(Args...) const>
	{
		using result_type = _Ret;
		template<typename _Func>
		result_type operator()(_Func fun, Args&&...args)
		{
			return fun(std::forward<Args>(args)...);
		}

	};

}