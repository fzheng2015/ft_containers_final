#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "../iterators/iterator.hpp"

namespace ft
{

	template <typename T>
	class random_access_iterator
	{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef ft::random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef value_type &reference;
		typedef value_type *pointer;
		typedef random_access_iterator<T> iterator;
		typedef random_access_iterator<const T> const_iterator;


		/* X a, X b(a), b = a, ~X */
		random_access_iterator() : mptr(NULL) {}

		explicit random_access_iterator(pointer ptr) : mptr(ptr) {}
		random_access_iterator(const random_access_iterator &rhs) { *this = rhs; }
		random_access_iterator &operator=(const random_access_iterator &rhs)
		{
			if (this != &rhs)
				mptr = rhs.mptr;
			return *this;
		}
		~random_access_iterator() {}

		/* a == b, a != b */
		bool operator==(const iterator &rhs) const { return mptr == rhs.mptr; }
		bool operator!=(const iterator &rhs) const { return mptr != rhs.mptr; }

		/* *a, a->m, *a = t */
		reference operator*() const { return *mptr; }
		pointer operator->() const { return mptr; }

		/* ++a, a++, *a++ */
		iterator &operator++()
		{
			mptr++;
			return *this;
		}
		iterator operator++(int)
		{
			iterator tmp = *this;
			mptr++;
			return tmp;
		}

		/* --a, a--, *a-- */
		iterator &operator--()
		{
			mptr--;
			return *this;
		}
		iterator operator--(int)
		{
			iterator tmp = *this;
			mptr--;
			return tmp;
		}

		const pointer &base() const { return mptr; }

		/* a + n, n + a, a - n, a - b */
		iterator operator+(const difference_type &n) const { return iterator(mptr + n); }
		iterator operator-(const difference_type &n) const { return iterator(mptr - n); }
		difference_type operator-(const iterator &rhs) const { return (mptr - rhs.mptr); }

		/*a < b, a > b, a <= b, a >= b */
		/* done with non-member functions */

		/* a += n, a -= n */
		iterator &operator+=(int n)
		{
			mptr += n;
			return *this;
		}

		iterator &operator-=(int n)
		{
			mptr -= n;
			return *this;
		}

		/* a[n] */
		reference operator[](const difference_type n) const { return mptr[n]; }

		/* const convertion */
		operator const_iterator() const { return const_iterator(mptr); }

	private:
		pointer mptr;
	};

	template <typename T>
	ft::random_access_iterator<T> operator+(typename ft::random_access_iterator<T>::difference_type n, const ft::random_access_iterator<T> &it)
	{
		return ft::random_access_iterator<T>(it.base() + n);
	}
	template <typename T, typename T1>
	typename ft::random_access_iterator<T>::difference_type
	operator-(const ft::random_access_iterator<T> &lhs, const ft::random_access_iterator<T1> &rhs)
	{
		return lhs.base() - rhs.base();
	}

	template <class Iterator1, class Iterator2>
	bool operator==(const ft::random_access_iterator<Iterator1> &lhs,
					const ft::random_access_iterator<Iterator2> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class Iterator1, class Iterator2>
	bool operator!=(const ft::random_access_iterator<Iterator1> &lhs,
					const ft::random_access_iterator<Iterator2> &rhs)
	{
		bool res = lhs.base() != rhs.base();
		return res;
	}

	template <class Iterator1, class Iterator2>
	bool operator<(const ft::random_access_iterator<Iterator1> &lhs,
				   const ft::random_access_iterator<Iterator2> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <class Iterator1, class Iterator2>
	bool operator<=(const ft::random_access_iterator<Iterator1> &lhs,
					const ft::random_access_iterator<Iterator2> &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <class Iterator1, class Iterator2>
	bool operator>(const ft::random_access_iterator<Iterator1> &lhs,
				   const ft::random_access_iterator<Iterator2> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <class Iterator1, class Iterator2>
	bool operator>=(const ft::random_access_iterator<Iterator1> &lhs,
					const ft::random_access_iterator<Iterator2> &rhs)
	{
		return lhs.base() >= rhs.base();
	}

} // namespace ft

#endif