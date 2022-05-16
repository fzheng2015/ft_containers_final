#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "../iterators/iterator.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{

	public:
		typedef Iterator iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer pointer;
		typedef typename ft::iterator_traits<Iterator>::reference reference;

		/* member functions */
		reverse_iterator() : mcurrent() {}
		explicit reverse_iterator(iterator_type it) : mcurrent(it) {}
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &rev_it) : mcurrent(rev_it.base()) {}

		iterator_type base() const { return mcurrent; }

		template <class U>
		reverse_iterator &operator=(const reverse_iterator<U> &other)
		{
			mcurrent = other.base();
			return *this;
		}

		reference operator*() const
		{
			iterator_type tmp = mcurrent;
			tmp--;
			return *tmp;
		}

		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(base() - n);
		}

		reverse_iterator &operator++()
		{
			mcurrent.operator--();
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator temp = *this;
			++(*this);
			return temp;
		}

		reverse_iterator &operator+=(difference_type n)
		{
			mcurrent.operator-=(n);
			return *this;
		}

		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(base() + n);
		}

		reverse_iterator &operator--()
		{
			mcurrent.operator++();
			return *this;
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator temp = *this;
			--(*this);
			return temp;
		}

		reverse_iterator &operator-=(difference_type n)
		{
			mcurrent.operator+=(n);
			return *this;
		}

		pointer operator->() const { return &(operator*()); }

		reference operator[](difference_type n) const { return base()[-n - 1]; }

	protected:
		Iterator mcurrent;
	};

	/* non member function overloads */
	template <class Iterator1, class Iterator2>
	bool operator==(const ft::reverse_iterator<Iterator1> &lhs,
					const ft::reverse_iterator<Iterator2> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class Iterator1, class Iterator2>
	bool operator!=(const ft::reverse_iterator<Iterator1> &lhs,
					const ft::reverse_iterator<Iterator2> &rhs)
	{
		bool res = lhs.base() != rhs.base();
		return res;
	}

	template <class Iterator1, class Iterator2>
	bool operator<(const ft::reverse_iterator<Iterator1> &lhs,
				   const ft::reverse_iterator<Iterator2> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <class Iterator1, class Iterator2>
	bool operator<=(const ft::reverse_iterator<Iterator1> &lhs,
					const ft::reverse_iterator<Iterator2> &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <class Iterator1, class Iterator2>
	bool operator>(const ft::reverse_iterator<Iterator1> &lhs,
				   const ft::reverse_iterator<Iterator2> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <class Iterator1, class Iterator2>
	bool operator>=(const ft::reverse_iterator<Iterator1> &lhs,
					const ft::reverse_iterator<Iterator2> &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <class Iter>
	reverse_iterator<Iter>
	operator+(typename reverse_iterator<Iter>::difference_type n,
			  const reverse_iterator<Iter> &it)
	{
		return reverse_iterator<Iter>(it.base() - n);
	}

	template <class Iterator1, class Iterator2>
	typename ft::reverse_iterator<Iterator1>::difference_type
	operator-(const ft::reverse_iterator<Iterator1> &lhs,
			  const ft::reverse_iterator<Iterator2> &rhs)
	{
		return rhs.base() - lhs.base();
	}
	
} // namespace ft

#endif
