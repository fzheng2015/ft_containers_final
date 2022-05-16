#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

# include "../iterators/iterator.hpp"
# include "../utils/bstree.hpp"

namespace ft
{

	template <typename T>
	class bi_iter
	{

	public:
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef ft::bstree<value_type> bstree;
		typedef bstree *iterator_type;
		typedef ft::bidirectional_iterator_tag iterator_category;
		typedef bi_iter<T> iterator;

	public:
		iterator_type mnode;

	public:
		bi_iter() : mnode(NULL) {}
		explicit bi_iter(iterator_type node) : mnode(node) {}
		bi_iter(const bi_iter &rhs) { *this = rhs; }
		bi_iter &operator=(const bi_iter &rhs)
		{
			if (this != &rhs)
				mnode = rhs.base();
			return *this;
		}
		~bi_iter() {}
		bstree *base() const { return mnode; }

		/* a == b, a != b */
		friend bool operator==(const bi_iter &lhs, const bi_iter &rhs) { return lhs.base() == rhs.mnode; }
		friend bool operator!=(const bi_iter &lhs, const bi_iter &rhs) { return lhs.base() != rhs.mnode ; }

		/* *a, *a = t, a->m */
		reference operator*() const { return mnode->value; }
		pointer operator->() const { return &(mnode->value); }

		/* ++a, a++, *a++ */
		iterator &operator++()
		{
			mnode = findnext(mnode);
			return *this;
		}
		iterator operator++(int)
		{
			iterator tmp = *this;
			++(*this);
			return tmp;
		}
		/* --a, a--, *a-- */
		iterator &operator--()
		{
			mnode = findprev(mnode);
			return *this;
		}
		iterator operator--(int)
		{
			iterator tmp = *this;
			--(*this);
			return tmp;
		}

	};

	template <typename T>
	class bi_const_iter
	{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef const T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef ft::bstree<T> bstree;
		typedef ft::bidirectional_iterator_tag iterator_category;
		typedef ft::bi_const_iter<T> iterator;

		bi_const_iter() : mnode(NULL) {}
		bi_const_iter(const bi_const_iter &rhs) { *this = rhs; }
		bi_const_iter(bstree *node) : mnode(node) {}
		bi_const_iter(const bi_iter<T> &rhs): mnode(rhs.mnode) {}
		bi_const_iter &operator=(const bi_const_iter &rhs)
		{
			if (this != &rhs)
				this->mnode = rhs.mnode;
			return *this;
		}
		~bi_const_iter() {}
		bstree *base() const { return mnode; }

		/* a == b, a != b */
		friend bool operator==(const iterator &lhs, const iterator &rhs) { return lhs.base() == rhs.base(); }
		friend bool operator!=(const iterator &lhs, const iterator &rhs) { return lhs.base() != rhs.base(); }

		/* *a, *a = t, a->m */
		reference operator*() const { return mnode->value; }
		pointer operator->() const { return &(mnode->value); }

		/* ++a, a++, *a++ */
		iterator &operator++()
		{
			mnode = findnext(mnode);
			return *this;
		}
		iterator operator++(int)
		{
			iterator tmp = *this;
			++(*this);
			return tmp;
		}
		/* --a, a--, *a-- */
		iterator &operator--()
		{
			mnode = findprev(mnode);
			return *this;
		}
		iterator operator--(int)
		{
			iterator tmp = *this;
			--(*this);
			return tmp;
		}

	public:
		bstree *mnode;
	};

}

#endif