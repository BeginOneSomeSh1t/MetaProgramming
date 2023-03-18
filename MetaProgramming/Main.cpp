#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory>
#include <string>


template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}

using namespace std;

struct person
{
	string name;
	size_t age;
	person(string n, size_t a)
		: name{ move(n) }, age{ a }
	{
		print_whatever("Ctor ", name, '\n');
	}
	~person() { print_whatever("DCTOR ", name, '\n'); }
};


int main(int argc, char**argv)
{
	shared_ptr<string> shared_name;
	shared_ptr<size_t> shared_age;

	{
		auto sperson{ make_shared<person>("John Doe", 30) };

		shared_name = shared_ptr<string>{ sperson, &sperson->name };
		shared_age = shared_ptr<size_t>{ sperson, &sperson->age };
	}
	// person object is stil alive
	print_whatever("Name: ", *shared_name, "\nage: ", *shared_age, '\n');




}