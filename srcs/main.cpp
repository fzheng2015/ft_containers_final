#include "../includes/map_test.hpp"
#include "../includes/stack_test.hpp"
#include "../includes/vector_test.hpp"
#include <iostream>
#define yello "\33[33m"
#define white "\33[0m"

int main(int ac, char **av)
{

	std::ostream &cout = std::cout;

	if (ac == 1)
	{
		vector_test(cout);
		stack_test(cout);
		map_test(cout);
		return 0;
	}
	if (ac != 2)
	{
		cout << "./exec.a [name of the container]\n";
		return 1;
	}
	std::string container;
	container = av[1];
	if (container == "stack")
		stack_test(cout);
	else if (container == "vector")
		vector_test(cout);
	else if (container == "map")
		map_test(cout);
	else
	{
		cout << "wrong container name: ";
		cout << "accepted containers are 'vector', 'stack' & 'map'\n";
		cout << "You can also launch without arguments, the program will test all the available containers\n";
	}

	return 0;
}