#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <memory>

#define STD_ON using namespace std

template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}

struct Foo {
	int value;
	Foo(int i) : value{ i } {}
	~Foo() { std::cout << "DTOR Foo " << value << '\n'; }
};

void weak_ptr_info(const std::weak_ptr<Foo>& p)
{
	print_whatever("-------------", std::boolalpha, "\nexpired: ", p.expired());
	print_whatever("\nexpired: ", p.use_count());
	print_whatever("\ncontent: ");

	if (const auto sp{ p.lock() }; sp)
		print_whatever(sp->value, '\n');
	else
		print_whatever("<nullptr>");
}
int main(int argc, char**argv)
{
	STD_ON;
	weak_ptr<Foo> weak_foo;
	weak_ptr_info(weak_foo);
	{
		auto shared_foo{ make_shared<Foo>(1337) };
		weak_foo = shared_foo;
		weak_ptr_info(weak_foo);
	}

	weak_ptr_info(weak_foo);



	
}