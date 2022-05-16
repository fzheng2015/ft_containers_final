#include "../includes/stack_test.hpp"
#include "../containers/stack.hpp"
#include <stack>

void ft_output(std::string str)
{
	std::cout << yello << "outputing " << str << ": " << white;
}

void ft_action(std::string str)
{
	std::cout << yello << "action: " << white << str << '\n';
}

void stack_string(std::ostream &cout)
{
	cout << "constructor test\n";
	cout << "construct stack<string> tabstr:\n";
	LIB::stack<std::string> tabstr;
	cout << "tabstr push (hello, how, are, you)\n";
	tabstr.push("hello");
	tabstr.push("how");
	tabstr.push("are");
	tabstr.push("you");
	cout << "construct const stack<string> tabconst(tabstr):\n";
	const LIB::stack<std::string> tabconst(tabstr);
	cout << "pop tabstr\n";
	tabstr.pop();
	cout << "is tabstr empty? " << std::boolalpha << tabstr.empty() << '\n';
	cout << "size of tabstr: " << tabstr.size() << '\n';
	cout << "size of tabconst: " << tabconst.size() << '\n';
	cout << "top of tabstr: " << tabstr.top() << '\n';
	cout << "top of tabconst: " << tabconst.top() << '\n';
	cout << "end of constructor test\n";
}

void stack_test(std::ostream &cout)
{
	cout << "=== stack tests ===\n";
	stack_string(cout);
	LIB::stack<int> stackv;
	{
		cout << yello << "regarding stackv\n"
			 << white;
		ft_action("push int 5");
		stackv.push(5);
		ft_action("push int 4");
		stackv.push(4);
		if (!stackv.empty())
		{
			ft_action("pop");
			stackv.pop();
		}
		ft_output("empty or not");
		{
			if (!stackv.empty())
				cout << "not empty" << '\n';
			else
				cout << "empty" << '\n';
		}

		if (!stackv.empty())
		{
			ft_output("the size");
			cout << stackv.size() << '\n';
			ft_output("the top");
			cout << stackv.top() << '\n';
		}
	}
	ft_action("assigning stackv to stackj");
	LIB::stack<int> stackj(stackv);
	if (!stackj.empty())
	{
		cout << yello << "regarding stackj\n"
			 << white;
		ft_output("the size");
		cout << stackj.size() << '\n';
		ft_output("the top");
		cout << stackj.top() << '\n';
	}
	cout << yello << "testing relational operators\n"
		 << white;
	cout << "stackj == stackv " << std::boolalpha << (stackj == stackv) << '\n';
	cout << "stackj != stackv " << std::boolalpha << (stackj != stackv) << '\n';
	cout << "stackj >= stackv " << std::boolalpha << (stackj >= stackv) << '\n';
	cout << "stackj <= stackv " << std::boolalpha << (stackj <= stackv) << '\n';
	cout << "stackj > stackv " << std::boolalpha << (stackj > stackv) << '\n';
	cout << "stackj < stackv " << std::boolalpha << (stackj < stackv) << '\n';
	ft_action("push int 3 to stackv");
	stackv.push(3);
	cout << "stackj == stackv " << std::boolalpha << (stackj == stackv) << '\n';
	cout << "stackj != stackv " << std::boolalpha << (stackj != stackv) << '\n';
	cout << "stackj <= stackv " << std::boolalpha << (stackj <= stackv) << '\n';
	cout << "stackj < stackv " << std::boolalpha << (stackj < stackv) << '\n';
	cout << "stackj >= stackv " << std::boolalpha << (stackj >= stackv) << '\n';
	cout << "stackj > stackv " << std::boolalpha << (stackj > stackv) << '\n';

	ft_action("push int 2 to stackj");
	stackj.push(2);
	cout << "stackj == stackv " << std::boolalpha << (stackj == stackv) << '\n';
	cout << "stackj != stackv " << std::boolalpha << (stackj != stackv) << '\n';
	cout << "stackj <= stackv " << std::boolalpha << (stackj <= stackv) << '\n';
	cout << "stackj < stackv " << std::boolalpha << (stackj < stackv) << '\n';
	cout << "stackj >= stackv " << std::boolalpha << (stackj >= stackv) << '\n';
	cout << "stackj > stackv " << std::boolalpha << (stackj > stackv) << '\n';

	ft_action("push int 5 to stackj");
	stackj.push(5);
	cout << "stackj == stackv " << std::boolalpha << (stackj == stackv) << '\n';
	cout << "stackj != stackv " << std::boolalpha << (stackj != stackv) << '\n';
	cout << "stackj <= stackv " << std::boolalpha << (stackj <= stackv) << '\n';
	cout << "stackj < stackv " << std::boolalpha << (stackj < stackv) << '\n';
	cout << "stackj >= stackv " << std::boolalpha << (stackj >= stackv) << '\n';
	cout << "stackj > stackv " << std::boolalpha << (stackj > stackv) << '\n';

	cout << "===\n\n";
}