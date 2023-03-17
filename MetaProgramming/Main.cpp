#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <variant>
#include <list>
#include <string>
#include <algorithm>

#define STD_ON using namespace std

template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}

class cat
{
	std::string name;
public:
	cat(std::string n) : name{n}{}
	void meow() const
	{
		print_whatever(name, "says Meow!\n");
	}
};

class dog
{
	std::string name;
public:
	dog(std::string n) : name{n}{}
	void woof() const { print_whatever(name, " says Woof"); }
};

using animal = std::variant<dog, cat>;

template<typename _Ty>
bool is_type(const animal& a)
{
	return std::holds_alternative<_Ty>(a);
}

struct animal_voice
{
	void operator()(const dog& d) const { d.woof(); }
	void operator()(const cat& c) const { c.meow(); }
};

int main(int argc, char**argv)
{
	STD_ON;
	list<animal> l{ cat{"Tuba"}, dog{"Balou"}, cat{"Bobby"} };

	

	for (const animal& a : l)
		visit(animal_voice{}, a);
	print_whatever("----------\n");


	
}