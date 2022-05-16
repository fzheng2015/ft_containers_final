#include "../includes/vector_test.hpp"
#include "../containers/vector.hpp"
#include <vector>
#include <unistd.h>

static void ft_printint_vector(LIB::vector<int> vector, int i)
{
	std::cout << "print the vector " << i << "\n";
	std::cout << "vector size: " << vector.size() << '\n';
	for (size_t i = 0; i < vector.size(); i++)
		std::cout << "vector " << i << ": " << vector[i] << '\n';
}
static void ft_printstr_vector(LIB::vector<std::string> vector)
{
	std::cout << "print string vector " << "\n";
	std::cout << "vector size: " << vector.size() << '\n';
	for (size_t i = 0; i < vector.size(); i++)
		std::cout << "vector " << i << ": " << vector[i] << '\n';
}

static void ft_reverse_iterator(std::ostream &cout, LIB::vector<int> vector1)
{
	cout << "---vector reverse iterator tests---\n";

	cout << "reverse iterator loop: \n";
	LIB::vector<int>::reverse_iterator rit = vector1.rbegin();
	for (; rit != vector1.rend(); rit++)
		cout << "reverse_iterator: " << *(rit) << '\n';

	cout << "const reverse iterator loop: \n";
	LIB::vector<int> const vector2 = vector1;
	for (LIB::vector<int>::const_reverse_iterator crit = vector2.rbegin(); crit != vector2.rend(); crit++)
		cout << "const reverse_iterator: " << *(crit) << '\n';

	cout << "---\n";
	cout << "reverse iterator non member functions tests\n";
	{
		cout << "comparison between reverse_iterators:\n";
		LIB::vector<int>::reverse_iterator crit = vector1.rbegin() + 2;
		rit = vector1.rbegin();
		cout << "*crit: " << *crit << '\n';
		cout << "*rit: " << *rit << '\n';
		cout << "(cit != rit)? " << (crit != rit) << '\n';
		cout << "(crit == rit)? " << (crit == rit) << '\n';
		cout << "(crit < rit)? " << (crit < rit) << '\n';
		cout << "(crit <= rit)? " << (crit <= rit) << '\n';
		cout << "(crit > rit)? " << (crit > rit) << '\n';
		cout << "(crit >= rit)? " << (crit >= rit) << '\n';
	}
	{
		cout << "comparison between const_reverse_iterators:\n";
		LIB::vector<int>::const_reverse_iterator crit = vector1.rbegin() + 2;
		LIB::vector<int>::const_reverse_iterator cri = vector1.rbegin() + 2;
		cout << "*cri: " << *cri << '\n';
		cout << "*crit: " << *crit << '\n';
		cout << "(crit != cri)? " << (crit != cri) << '\n';
		cout << "(crit == cri)? " << (crit == cri) << '\n';
		cout << "(crit < cri)? " << (crit < cri) << '\n';
		cout << "(crit <= cri)? " << (crit <= cri) << '\n';
		cout << "(crit > cri)? " << (crit > cri) << '\n';
		cout << "(crit >= cri)? " << (crit >= cri) << '\n';
	}
	{
		cout << "testing +/- overloads with vector1:\n";
		LIB::vector<int>::const_reverse_iterator crit(2 + vector1.rbegin());
		LIB::vector<int>::const_reverse_iterator cri(vector1.rend());
		cout << "*(rbegin() + 2): " << (*crit) << '\n';
		cout << "*(rend() - 1): " << *(vector1.rend() - 1) << '\n';
	}
	cout << "---\n";
	cout << "---end vector reverse iterator tests---\n";
}

static void ft_vector_iterator(std::ostream &cout, LIB::vector<int> vector1)
{
	cout << "---vector iterator tests---\n";
	LIB::vector<int>::iterator it;
	it = vector1.begin() + 1;

	cout << "*(it + 1): " << *it << '\n';
	cout << "iterator loop: \n";
	for (LIB::vector<int>::iterator ait = vector1.begin(); ait != vector1.end(); ait++)
		cout << "iterator " << (*ait) << ": " << *ait << '\n';
	cout << "const iterator loop: \n";
	for (LIB::vector<int>::const_iterator ait = vector1.begin(); ait != vector1.end(); ait++)
		cout << "const iterator: " << (*ait) << '\n';
	
	cout << "*(1 + it): " << *(1 + it) << '\n';

	cout << "---end vector iterator tests---\n";
}

static void ft_vector_normaltest(std::ostream &cout, LIB::vector<int> vector1)
{
	cout << "---vector basic tests---\n";
	cout << "size: " << vector1.size() << '\n';
	cout << "push_back 8, 9, 7, 6\n";
	vector1.push_back(8);
	vector1.push_back(9);
	vector1.push_back(7);
	vector1.push_back(6);
	ft_printint_vector(vector1,1);
	cout << "construct vector0 with vector1.begin(), vector1.end()\n";

	LIB::vector<int> vector0(vector1.begin(), vector1.end());
	ft_printint_vector(vector0, 0);
	cout << "construct const vector5(vector1)\n";
	const LIB::vector<int> vector5(vector1);
	ft_printint_vector(vector5, 5);

	cout << "\n///element access tests///\n";
	cout << "at test\n";
	{
		std::cout << "at pos 5: " << vector1.at(5) << '\n';
		try
		{
			std::cout << "at pos 20: " << vector1.at(20) << '\n';
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		std::cout << "at pos 5 (vector5 const): " << vector5.at(5) << '\n';
		try
		{
			std::cout << "at pos 20 (vector5 const): " << vector5.at(20) << '\n';
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	cout << "access pos 1 with operator[]: " << vector1[1] << '\n';
	cout << "access pos 1 with operator[] (vector5): " << vector5[1] << '\n';
	cout << "front(): " << vector1.front() << '\n';
	cout << "front() (vector5): " << vector5.front() << '\n';
	cout << "back(): " << vector1.back() << '\n';
	cout << "back() (vector5): " << vector5.back() << '\n';
	cout << "data()+1: " << *(vector1.data()+1) << '\n';
	cout << "data()+1 (vector5): " << *(vector5.data()+1) << '\n';

	cout << "\n///iterators tests///\n";
	cout << "begin(): " << *(vector1.begin()) << '\n';
	cout << "rbegin(): " << *(vector1.rbegin()) << '\n';
	cout << "end() - 1: " << *(vector1.end()-1) << '\n';
	cout << "rend()-1: " << *(vector1.rend()-1) << '\n';

	cout << "\n///capacity tests///\n";
	cout << "is empty? " << (vector1.empty()?"true":"false") << '\n';
	cout << "size? " << vector1.size() << '\n';
	cout << "max_size? " << vector1.max_size() << '\n';
	cout << "capacity? " << vector1.capacity() << '\n';
	cout << "reserve(20)\n";
	vector1.reserve(20);
	cout << "after reserve, capacity? " << vector1.capacity() << '\n';

	cout << "\n///modifiers tests///\n";
	cout << "assign tests\n";
	LIB::vector<int> vector3;
	cout << "assign 3 time 5 to vector3\n";
	vector3.assign(3, 5);
	ft_printint_vector(vector3,3);
	cout << "assign vector1.begin() till vector1.end() to vector3\n";
	vector3.assign(vector1.begin(),vector1.end());
	ft_printint_vector(vector3,3);

	cout << "vector3 clear()\n";
	vector3.clear();
	ft_printint_vector(vector3,3);
	// insert
	cout << "insert tests\n";
	{
		cout << "create vector2, push_back(2)\n";
		LIB::vector<int> vector2(1,2);
		cout << "insert num 5 at pos begin()\n";
		vector2.insert(vector2.begin(), 5);
		cout << "insert 3 times 300 at pos begin()+1 \n";
		vector2.insert(vector2.begin() + 1, 3, 300);
		ft_printint_vector(vector2, 2);
		cout << "insert in vector2 at begin(), vector1.begin() till vector1.begin()+2 (0,1)\n";
		vector2.insert(vector2.begin(), vector1.begin(), vector1.begin() + 2);
		ft_printint_vector(vector2,2);
	}
	// erase
	cout << "erase position 4 test\n";
	{
		LIB::vector<int>::iterator pos4 = vector1.begin() + 4;
		vector1.erase(pos4);
		ft_printint_vector(vector1,1);
	}
	cout << "erase position (begin + 1) till (end - 1) test: \n";
	{
		LIB::vector<int>::iterator first = vector1.begin() + 2;
		LIB::vector<int>::iterator last = vector1.end() - 3;
		vector1.erase(first, last);
		ft_printint_vector(vector1,1);
	}
	cout << "pop_back\n";
	vector1.pop_back();
	ft_printint_vector(vector1,1);

	cout << "resize to size=3\n";
	vector1.resize(3);
	ft_printint_vector(vector1,1);
	LIB::vector<int> vector4;
	cout << "create vector4 and insert 5 times 4\n";
	vector4.insert(vector4.begin(), 5, 4);
	ft_printint_vector(vector4,4);

	cout << "swap vector1 & vector4\n";
	vector1.swap(vector4);
	cout << "vector1: ";
	ft_printint_vector(vector1,1);
	cout << "vector4: ";
	ft_printint_vector(vector4,4);

	cout << "\n///non-member funcitons tests///\n";
	LIB::vector<int> alice(3, 1);
    LIB::vector<int> bob(4, 7);
 
	cout << "create alice(3,1), bob(4,7)\n";
    cout << std::boolalpha;
    cout << "alice == bob returns " << (alice == bob) << '\n';
    cout << "alice != bob returns " << (alice != bob) << '\n';
    cout << "alice <  bob returns " << (alice < bob) << '\n';
    cout << "alice <= bob returns " << (alice <= bob) << '\n';
    cout << "alice >  bob returns " << (alice > bob) << '\n';
    cout << "alice >= bob returns " << (alice >= bob) << '\n';
	cout << '\n';

	LIB::vector<int> foo(3, 100); // three ints with a value of 100
	LIB::vector<int> bar(5, 200); // five ints with a value of 200

	std::cout << "before swap foo contains:";
	for (LIB::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	std::cout << "before swap bar contains:";
	for (LIB::vector<int>::iterator it = bar.begin(); it != bar.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	LIB::swap(bar, foo);

	std::cout << "after swap foo contains:";
	for (LIB::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "after swap bar contains:";
	for (LIB::vector<int>::iterator it = bar.begin(); it != bar.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	cout << "---end vector normal tests---\n";
}

static void ft_vector_string(std::ostream &cout)
{
	LIB::vector<std::string> tab;
	cout << "construct vector<string> tab\n";
	cout << "push back numerous elements\n";
	tab.push_back("hello");
	tab.push_back("how");
	tab.push_back("are");
	tab.push_back("you");
	tab.push_back("?");
	ft_printstr_vector(tab);

	cout << "erase tab[tab.begin() + 2]\n";
	LIB::vector<std::string>::iterator tabit = tab.begin() + 2;
	tab.erase(tabit);
	ft_printstr_vector(tab);
	cout << "pop_back()\n";
	tab.pop_back();
	ft_printstr_vector(tab);
	cout << "construct const vector<string> const_tab\n";
	const LIB::vector<std::string> const_tab(tab);
	ft_printstr_vector(const_tab);
}

void vector_test(std::ostream &cout)
{
	cout << "=== vector tests ===\n";
	LIB::vector<int> vector1;
	cout << "push_back 0, 1, 2, 3\n";
	vector1.push_back(0);
	vector1.push_back(1);
	vector1.push_back(2);
	vector1.push_back(3);

	cout << "capacity: " << vector1.capacity() << '\n';
	ft_printint_vector(vector1,1);
	{
		ft_vector_string(cout);
		ft_vector_iterator(cout, vector1);
		ft_reverse_iterator(cout, vector1);
		ft_vector_normaltest(cout, vector1);
	}
	cout << "===\n";
	cout << '\n';
}