#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft
{
	// True if the first range [first1, last1) is lexicographically less than the second range [first2, last2)
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			first1++;
			first2++;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (comp(*first2, *first1))
				return false;
			if (comp(*first1, *first2))
				return true;
			first1++;
			first2++;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1,
			   InputIterator2 first2, BinaryPredicate pred) // pred is a bool function
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2)) // if equal then true, else false
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class T>
	struct less
	{
		typedef bool result_type;
		typedef T first_argument_type;
		typedef T second_argument_type;
		bool operator()(const T &lhs, const T &rhs) const { return lhs < rhs; }
	};

	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

} // namespace ft

#endif
