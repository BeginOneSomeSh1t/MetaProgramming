#pragma once
#include <xutility>
#include <vector>

namespace delegation
{
	template<typename _FunSig>
	class base_delegate
	{
		using delegate_type = base_delegate<decltype(&_FunSig::operator())>;
		delegate_type p_fun;
	public:
		base_delegate(_FunSig p_fun)
			: p_fun(p_fun)
		{}

		template<typename..._Args>
		auto operator()(_Args&&...args)
		{
			return p_fun(std::forward<_Args>(args)...);
		}
	};


	template<typename _Ret, typename..._Args>
	class base_delegate<_Ret(*)(_Args...)>
	{
		using func_type = _Ret(*)(_Args...);
		func_type p_func;
	public:
		base_delegate(func_type p_fun)
			: p_func(p_fun)
		{}

		template<typename..._Args>
		auto operator()(_Args&&...args)
		{
			return p_func(std::forward<_Args>(args)...);
		}
	};

	//template<typename _Class, typename _Ret, typename..._Args>
	//class base_delegate<_Ret(_Class::*)(_Args...)>
	//{

	//};
}
