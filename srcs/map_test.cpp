#include "../includes/map_test.hpp"
#include "../containers/map.hpp"
#include <map>

static void ft_printint_map(LIB::map<int, int> map, std::string i)
{
	std::cout << "print the map " << i << "\n";
	std::cout << "map size: " << map.size() << '\n';
	if (map.size() == 0)
		return;
	std::cout << i << " (first, second): ";
	for (LIB::map<int, int>::iterator it = map.begin(); it != map.end(); it++)
		std::cout << '(' << it->first << ", " << it->second << ") ";
	std::cout << '\n';
}

static void map_nonmemberfunctions(std::ostream &cout)
{
	cout << "\n///non-member functions tests///\n";
	{
		LIB::map<int, char> alice;
		alice[1] = 'a';
		alice[2] = 'b';
		alice[3] = 'c';
		LIB::map<int, char> bob;
		bob[7] = 'Z';
		bob[8] = 'Y';
		bob[9] = 'X';
		bob[10] = 'W';
		LIB::map<int, char> eve;
		eve[1] = 'a';
		eve[2] = 'b';
		eve[3] = 'c';

		cout << std::boolalpha;

		// Compare non equal containers
		cout << "alice == bob returns " << (alice == bob) << '\n';
		cout << "alice != bob returns " << (alice != bob) << '\n';
		cout << "alice <  bob returns " << (alice < bob) << '\n';
		cout << "alice <= bob returns " << (alice <= bob) << '\n';
		cout << "alice >  bob returns " << (alice > bob) << '\n';
		cout << "alice >= bob returns " << (alice >= bob) << '\n';

		cout << '\n';

		// Compare equal containers
		cout << "alice == eve returns " << (alice == eve) << '\n';
		cout << "alice != eve returns " << (alice != eve) << '\n';
		cout << "alice <  eve returns " << (alice < eve) << '\n';
		cout << "alice <= eve returns " << (alice <= eve) << '\n';
		cout << "alice >  eve returns " << (alice > eve) << '\n';
		cout << "alice >= eve returns " << (alice >= eve) << '\n';

		cout << "\n-SWAP-\n";
		// Print state before swap
		std::cout << "alice (first, second): ";
		for (LIB::map<int, char>::iterator it = alice.begin(); it != alice.end(); it++)
			cout << '(' << it->first << ", " << it->second << ") ";
		std::cout << "\nbob (first, second): ";
		for (LIB::map<int, char>::iterator it = bob.begin(); it != bob.end(); it++)
			cout << '(' << it->first << ", " << it->second << ") ";
		std::cout << '\n';

		std::cout << "-- SWAP\n";
		std::swap(alice, bob);

		// Print state after swap
		std::cout << "alice (first, second): ";
		for (LIB::map<int, char>::iterator it = alice.begin(); it != alice.end(); it++)
			cout << '(' << it->first << ", " << it->second << ") ";
		std::cout << "\nbob (first, second): ";
		for (LIB::map<int, char>::iterator it = bob.begin(); it != bob.end(); it++)
			cout << '(' << it->first << ", " << it->second << ") ";
		std::cout << '\n';
	}
}

static void map_int(std::ostream &cout)
{
	cout << "\n///constructor///\n";
	LIB::map<int, int> hell;
	LIB::map<int, int> lleh;
	int size = 11;
	cout << "assign 1-10 to map<int, int> hell\n";
	for (int i = 1; i < size; i++)
		hell[i] = i;
	cout << "construct lleh = hell\n";
	lleh = hell;
	{
		cout << "construct lelh(hell)\n";
		LIB::map<int, int> lelh(hell);
		ft_printint_map(lelh, "lelh");
		cout << "construct ellh(hell.begin(), hell.end())\n";
		LIB::map<int, int> ellh(hell.begin(), hell.end());
		ft_printint_map(ellh, "ellh");
	}

	cout << "\n///element access///\n";
	cout << "access hell[1]: " << hell[1] << '\n';

	cout << "\n///iterators///\n";
	LIB::map<int, int>::iterator be = hell.begin();
	LIB::map<int, int>::reverse_iterator rbe = hell.rbegin();
	LIB::map<int, int>::iterator en = hell.end();
	LIB::map<int, int>::reverse_iterator ren = hell.rend();
	{
		LIB::map<int, int>::const_iterator cbe = hell.begin();
		LIB::map<int, int>::const_reverse_iterator crbe = hell.rbegin();
		LIB::map<int, int>::const_iterator cen = hell.end();
		LIB::map<int, int>::const_reverse_iterator cren = hell.rend();
		en--;
		ren--;
		cen--;
		cren--;
		cout << "begin() (first, second): (" << be->first << ", " << be->second << ")\n";
		cout << "rbegin() (first, second): (" << rbe->first << ", " << rbe->second << ")\n";
		cout << "end() - 1 (first, second): (" << en->first << ", " << en->second << ")\n";
		cout << "rend() - 1 (first, second): (" << ren->first << ", " << ren->second << ")\n";
		cout << "const begin() (first, second): (" << cbe->first << ", " << cbe->second << ")\n";
		cout << "const rbegin() (first, second): (" << crbe->first << ", " << crbe->second << ")\n";
		cout << "const end() - 1 (first, second): (" << cen->first << ", " << cen->second << ")\n";
		cout << "const rend() - 1 (first, second): (" << cren->first << ", " << cren->second << ")\n";

		cout << "\n///capacity///\n";
		cout << "hell is empty? " << std::boolalpha << hell.empty() << '\n';
		cout << "hell size? " << hell.size() << '\n';
		cout << "max_size? " << hell.max_size() << '\n';
	}

	cout << "\n///modifiers///\n";
	// clear
	{
		ft_printint_map(lleh, "lleh");
		cout << "lleh clear() test\n";
		lleh.clear();
		ft_printint_map(lleh, "lleh");
	}
	// insert
	{
		cout << "lleh insert() (1,1)(2,2)(3,3) test\n";
		lleh.insert(LIB::make_pair(1, 1));
		lleh.insert(LIB::make_pair(2, 2));
		lleh.insert(LIB::make_pair(3, 3));
		cout << "lleh insert() with hint = begin(), pair(4,4) test\n";
		lleh.insert(lleh.begin(), LIB::make_pair(4, 4));
		ft_printint_map(lleh, "lleh");
		cout << "lleh insert() hell.begin(), hell.end() test\n";
		lleh.insert(hell.begin(), hell.end());
		ft_printint_map(lleh, "lleh");
	}
	LIB::map<int, int> m1;
	// erase
	{
		cout << "lleh erase() test\n";
		cout << "lleh erase(++lleh.begin()):\n";
		lleh.erase(++lleh.begin());
		ft_printint_map(lleh, "lleh");
		cout << "lleh erase(3):\n";
		lleh.erase(3);
		ft_printint_map(lleh, "lleh");
		m1 = lleh;
		cout << "lleh erase(lleh.begin(), lleh.end()):\n";
		lleh.erase(lleh.begin(), lleh.end());
		ft_printint_map(lleh, "lleh");
	}
	// swap
	{
		cout << "before swap:\n";
		ft_printint_map(m1, "m1");
		ft_printint_map(hell, "hell");
		LIB::swap(m1, hell);
		cout << "after swap:\n";
		ft_printint_map(m1, "m1");
		ft_printint_map(hell, "hell");
	}
	cout << "\n///lookup///\n";
	// count
	cout << "hell.count(3): " << hell.count(3) << '\n';
	cout << "m1.count(3): " << m1.count(3) << '\n';

	// find
	{
		ft_printint_map(m1, "m1");
		LIB::map<int, int>::iterator find_it;
		LIB::map<int, int>::const_iterator find_cit;
		cout << "m1.find(3) returns iterator find_it\n";
		find_it = m1.find(3);
		if (find_it != m1.end())
			cout << "find_it->first: " << find_it->first << '\n';
		cout << "m1.find(4) returns const_iterator find_cit\n";
		find_cit = m1.find(4);
		if (find_cit != m1.end())
			cout << "find_cit->first: " << find_cit->first << '\n';
	}
	
	// lower_bound upper_bound equal_range
	{
		LIB::map<int, int>::iterator it;
		LIB::map<int, int>::const_iterator cit;
		it = hell.lower_bound(9);
		std::cout << "hell lower_bound(9): " << it->first << '\n';
		it = hell.upper_bound(9);
		std::cout << "hell upper_bound(9): " << it->first << '\n';

		cit = hell.lower_bound(9);
		std::cout << "hell const lower_bound(9): " << cit->first << '\n';
		cit = hell.upper_bound(9);
		std::cout << "hell const upper_bound(9): " << cit->first << '\n';

		std::cout << "equal_range(9) test:\n";
		LIB::pair<LIB::map<int, int>::iterator, LIB::map<int, int>::iterator> ret;
		LIB::pair<LIB::map<int, int>::const_iterator, LIB::map<int, int>::const_iterator> cret;
		ret = hell.equal_range(9);
		cret = hell.equal_range(9);
		std::cout << "lower bound points to: ";
		std::cout << ret.first->first << " => " << ret.first->second << '\n';
		std::cout << "const lower bound points to: ";
		std::cout << ret.first->first << " => " << ret.first->second << '\n';
		std::cout << "upper bound points to: ";
		std::cout << ret.second->first << " => " << ret.second->second << '\n';
		std::cout << "const upper bound points to: ";
		std::cout << ret.second->first << " => " << ret.second->second << '\n';
	}
	cout << "\n///observers///\n";
	// key_comp
	{
		std::cout << "key_comp test:\n";
		LIB::map<char, int> mymap;

		LIB::map<char, int>::key_compare mycomp = mymap.key_comp();

		mymap['a'] = 100;
		mymap['b'] = 200;
		mymap['c'] = 300;

		std::cout << "mymap contains:\n";

		char highest = mymap.rbegin()->first; // key value of last element

		LIB::map<char, int>::iterator it = mymap.begin();
		do
		{
			std::cout << it->first << " => " << it->second << '\n';
		} while (mycomp((*it++).first, highest));

		std::cout << '\n';
	}
	// value_comp
	{
		std::cout << "value_comp test:\n";
		LIB::map<char, int> mymap;

		mymap['x'] = 1001;
		mymap['y'] = 2002;
		mymap['z'] = 3003;

		std::cout << "mymap contains:\n";

		LIB::pair<char, int> highest = *mymap.rbegin(); // last element

		LIB::map<char, int>::iterator it = mymap.begin();
		do
		{
			std::cout << it->first << " => " << it->second << '\n';
		} while (mymap.value_comp()(*it++, highest));
	}
}

static void map_string(std::ostream &cout)
{
	LIB::map<std::string, int> hell;
	cout << "create map<std::string, int> hell\n";
	cout << "size(): " << hell.size() << '\n';
	cout << "empty(): " << hell.empty() << '\n';

	LIB::map<std::string, int>::const_iterator cit;
	cout << "---\n";
	hell.insert(LIB::make_pair("one", 1));
	cout << "size(): " << hell.size() << '\n';
	cout << "---\n";
	cout << "print element: |-" << hell["one"] << "-|\n";
	hell.insert(LIB::make_pair("two", 2));
	cout << "print element: |-" << hell["two"] << "-|\n";
	hell.insert(LIB::make_pair("three", 3));
	cout << "print element: |-" << hell["three"] << "-|\n";
	hell.insert(LIB::make_pair("four", 4));
	cout << "print element: |-" << hell["four"] << "-|\n";
	hell["five"] = 5;
	cout << "print element: |-" << hell["five"] << "-|\n";
	hell["six"] = 6;
	cout << "print element: |-" << hell["six"] << "-|\n";
	hell["seven"] = 7;
	cout << "print element: |-" << hell["seven"] << "-|\n";
	hell["eight"] = 8;
	cout << "print element: |-" << hell["eight"] << "-|\n";
	hell["nine"] = 9;
	cout << "print element: |-" << hell["nine"] << "-|\n";
	hell["ten"] = 10;
	cout << "print element: |-" << hell["ten"] << "-|\n";
	cout << "erase ten\n";
	cout << "erase nine\n";
	cout << "erase eight\n";
	hell.erase("ten");
	hell.erase("nine");
	hell.erase("eight");
	cit = hell.begin();
	cout << "print hell (first, second): ";
	for (; cit != hell.end(); cit++)
		cout << '(' << cit->first << ", " << cit->second << ") ";
	cout << '\n';
	cout << "size(): " << hell.size() << '\n';
	cout << "empty(): " << hell.empty() << '\n';
}

void map_test(std::ostream &cout)
{
	cout << "=== map tests ===\n";
	map_string(cout);
	map_int(cout);
	map_nonmemberfunctions(cout);
	cout << "===\n\n";
}