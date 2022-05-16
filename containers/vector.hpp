#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <string>
# include <string>
# include <sstream>
# include "../iterators/random_access_iterator.hpp"
# include "../iterators/reverse_iterator.hpp"
# include "../utils/type_traits.hpp"
# include "../utils/algorithm.hpp"

namespace ft
{

	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef T &reference;
		typedef const T &const_reference;
		typedef T *pointer;
		typedef const T *const_pointer;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;

		/* iterators */
		typedef typename ft::random_access_iterator<T> iterator;
		typedef typename ft::random_access_iterator<const T> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

		/* constructor, destructor, assignation
		 * default, fill, range, copy
		 */
		explicit vector(const allocator_type &alloc = allocator_type())
			: msize(0), mcapacity(0), mallo(alloc), marray(NULL) {}

		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type())
			: msize(n), mcapacity(n), mallo(alloc)
		{
			marray = mallo.allocate(n);
			for (size_type i = 0; i < msize; i++)
				mallo.construct(marray + i, val);
		}
		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
			   const allocator_type &alloc = allocator_type(),
			   typename ft::enable_if<!ft::is_integral<InputIterator>::value,
									  int>::type * = 0)
			: msize(0), mcapacity(0), mallo(alloc)
		{
			for (InputIterator it = first; it != last; it++)
				msize++;
			mcapacity = msize;
			marray = mallo.allocate(mcapacity);
			size_t i = 0;
			for (InputIterator it = first; it != last; it++)
				mallo.construct(marray + i++, *it);
		}
		vector(const vector &x)
		{
			msize = x.msize;
			mcapacity = x.mcapacity;
			mallo = x.mallo;
			marray = mallo.allocate(mcapacity);
			for (size_type i = 0; i < msize; i++)
				mallo.construct(marray + i, x.marray[i]);
		}

		~vector() { mallo.deallocate(marray, msize); }

		vector &operator=(const vector &x)
		{
			vector tmp(x);
			swap(tmp);
			return *this;
		}

		/* iterators */
		iterator begin() { return iterator(marray); }
		iterator end() { return iterator(marray + msize); }
		const_iterator begin() const { return const_iterator(marray); }
		const_iterator end() const { return const_iterator(marray + msize); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		/* capacity */
		size_type size() const { return msize; }
		size_type max_size() const { return mallo.max_size(); }
		// resize element to n, if bigger add val to free place
		void resize(size_type n, value_type val = value_type())
		{
			if (n < msize)
				erase(begin() + n, end());
			else
			{
				if (n + msize > mcapacity)
					realloCapa((n > mcapacity * 2) ? n : mcapacity * 2);
				insert(end(), n - msize, val);
			}
		}
		size_type capacity() const { return this->mcapacity; }
		bool empty() const { return !this->msize; }
		// resize capacity to n if bigger
		void reserve(size_type n)
		{
			if (n > mcapacity)
				realloCapa(n);
		}

		/* element access */
		reference operator[](size_type n) { return *(marray + n); }
		// return ref to ele at pos n
		const_reference operator[](size_type n) const { return *(marray + n); }

		reference at(size_type n)
		{
			if (n >= msize)
			{
				std::stringstream ss;
				ss << "vector::_M_range_check: __n (which is " << n << ")";
				ss << " >= this->size() (which is " << size() << ")";
				throw std::out_of_range(ss.str());
			}
			return *(marray + n);
		}
		// diff with [] is the check of out_of_range
		const_reference at(size_type n) const
		{
			if (n >= msize)
			{
				std::stringstream ss;
				ss << "vector::_M_range_check: __n (which is " << n << ")";
				ss << " >= this->size() (which is " << size() << ")";
				throw std::out_of_range(ss.str());
			}
			return *(marray + n);
		}

		reference front() { return *marray; }
		const_reference front() const { return *marray; }
		reference back() { return *(marray + msize - 1); }
		const_reference back() const { return *(marray + msize - 1); }

		T *data()
		{
			if (empty())
				return NULL;
			return marray;
		}
		const T *data() const
		{
			if (empty())
				return NULL;
			return marray;
		}
		/* modifiers */

		// delete old ele and put new ele
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, int>::type * = 0)
		{
			clear();
			insert(begin(), first, last);
		}
		void assign(size_type n, const value_type &val)
		{
			clear();
			insert(begin(), n, val);
		}

		void push_back(const value_type &val)
		{
			if (msize + 1 > mcapacity)
			{
				if (!msize)
					realloCapa(1);
				else
					realloCapa(msize * 2);
			}
			mallo.construct(marray + msize, val);
			msize++;
		}

		void pop_back()
		{
			if (msize > 0)
			{
				mallo.destroy(marray + msize - 1);
				msize--;
			}
		}

		// insert val at position
		iterator insert(iterator position, const value_type &val)
		{
			size_type pos = position - begin();
			if (msize + 1 > mcapacity)
				realloCapa(msize * 2);
			msize++;
			if (msize > 0)
			{
				for (size_type i = msize - 1; i > pos; i--)
					mallo.construct(marray + i, marray[i - 1]);
			}
			mallo.construct(marray + pos, val);
			return iterator(marray + pos);
		}
		// insert n times val
		void insert(iterator position, size_type n, const value_type &val)
		{
			size_type pos = position - begin();
			if (msize + n > mcapacity)
			{
				if (n > msize)
					realloCapa(msize + n);
				else
					realloCapa(mcapacity * 2);
			}
			msize += n;
			for (size_type i = msize - 1; i > pos + n - 1; i--)
				mallo.construct(marray + i, marray[i - n]);
			for (size_type i = pos; i < n + pos; i++)
				mallo.construct(marray + i, val);
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, int>::type * = 0)
		{
			size_type pos = position - begin();
			size_type n = 0;
			for (InputIterator it = first; it != last; it++)
				n++;
			if (msize + n > mcapacity)
			{
				if (n > msize)
					realloCapa(msize + n);
				else
					realloCapa(mcapacity * 2);
			}
			msize += n;
			for (size_type i = msize - 1; i > pos + n - 1; i--)
				mallo.construct(marray + i, marray[i - n]);
			size_t i = 0;
			for (InputIterator it = first; it != last; it++)
				mallo.construct(marray + pos + i++, *it);
		}

		// erase
		iterator erase(iterator position)
		{
			if (position == end())
				return end();
			size_type pos_index = position - begin();
			mallo.destroy(marray + pos_index);
			msize--;
			for (size_type i = pos_index; i < msize; i++)
				mallo.construct(marray + i, marray[i + 1]);
			return position; 
		}
		iterator erase(iterator first, iterator last)
		{
			if (first == last || first == end())
				return end();
			size_type n = 0;
			for (iterator it = first; it != last; it++)
				n++;
			size_type first_pos = 0;
			for (iterator it = begin(); it != first; it++)
				first_pos++;
			
			for (size_type i = first_pos; i < n; i++)
				mallo.destroy(marray + i);
			for (size_type i = first_pos; i + n < msize; i++)
			{
				mallo.construct(marray + i, marray[i + n]);
				mallo.destroy(marray + i + n);
			}
			msize -= n;
			return (iterator(begin() + first_pos));
		}

		void swap(vector &x)
		{
			size_type tmp_size = x.msize;
			size_type tmp_capacity = x.mcapacity;
			Alloc tmp_alloc = x.mallo;
			pointer tmp_array = x.marray;

			x.msize = msize;
			x.mcapacity = mcapacity;
			x.mallo = mallo;
			x.marray = marray;

			msize = tmp_size;
			mcapacity = tmp_capacity;
			mallo = tmp_alloc;
			marray = tmp_array;
		}

		void clear()
		{
			for (size_type i = 0; i < msize; i++)
				mallo.destroy(marray + i);
			msize = 0;
		}

		/* allocator */
		allocator_type get_allocator() const { return mallo; }

	private:
		void realloCapa(size_type n)
		{
			pointer new_array = mallo.allocate(n, &marray);
			for (size_type i = 0; i < msize; i++)
			{
				mallo.construct(new_array + i, marray[i]);
				mallo.destroy(marray + i);
			}
			mallo.deallocate(marray, mcapacity);
			marray = new_array;
			mcapacity = n;
		}

	private:
		size_type msize;
		size_type mcapacity;
		Alloc mallo;
		pointer marray;
	};

	/* non member function overloads */

	template <class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		return (lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		return !(lhs > rhs);
	}

	template <class T, class Alloc>
	bool operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Alloc>
	bool operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void swap(ft::vector<T, Alloc> &x, ft::vector<T, Alloc> &y)
	{
		x.swap(y);
	}

} // namespace ft

#endif