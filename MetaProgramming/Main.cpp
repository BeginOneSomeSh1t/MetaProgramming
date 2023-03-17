#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "tuple_plus.h"

#define STD_ON using namespace std

template<typename...Args>
void print_whatever(Args...args)
{
	((std::cout << args), ...);
}



int main(int argc, char**argv)
{
	STD_ON;
	auto student_desc{ make_tuple("ID", "Name", "GPA") };
	auto student{ make_tuple(123456,"JonhDoes", 3.7) };

	print_whatever(student_desc, '\n', student, '\n');

	print_whatever(tuple_cat(student_desc, student), '\n');

	auto zipped(zip(student_desc, student));

	auto numbers = { 0., 1., 2., 3., 4. };
	print_whatever(zip(make_tuple("Sum", "Minimum", "Maximum", "Average"), sum_min_max_avg(numbers)));


	
}