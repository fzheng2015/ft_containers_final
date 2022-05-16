#ifndef MAP_HPP
#define MAP_HPP

#include "../iterators/reverse_iterator.hpp"
#include "../iterators/bidirectional_iterator.hpp"
#include "../utils/algorithm.hpp"
#include "../utils/pair.hpp"
#include "../utils/bstree.hpp"
#include <iostream>

namespace ft
{

	template <class Key,											// map::key_type
			  class T,												// map::mapped_type
			  class Compare = ft::less<Key>,						// map::key_compare
			  class Alloc = std::allocator<ft::pair<const Key, T> > // map::allocator_type
			  >
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

		typedef typename ft::bi_iter<value_type> iterator;
		typedef typename ft::bi_const_iter<value_type> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef size_t size_type;

	private:
		/* attributes */
		typedef ft::bstree<value_type> bstree;
		typename Alloc::template rebind<bstree>::other mnode;
		Compare mcomp;
		Alloc mallo;
		size_type msize;
		bstree *mroot;
		bstree *mend;

	public:
		/* member classe */
		class value_compare : public ft::binary_function<value_type, value_type, bool>
		{
			friend class map;

		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			bool operator()(const value_type &lhs, const value_type &rhs) const
			{
				return comp(lhs.first, rhs.first);
			}
		};

		/* constructor, destructor, operator= */
		map()
		{
			mcomp = Compare();
			mallo = Alloc();
			minitialization();
		}
		explicit map(const Compare &comp,
					 const Alloc &alloc = Alloc())
			: mcomp(comp), mallo(alloc)
		{
			minitialization();
		}
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type())
			: mcomp(comp), mallo(alloc)
		{
			minitialization();
			insert(first, last);
		}
		map(const map &x) : mcomp(x.mcomp), mallo(x.mallo)
		{
			minitialization();
			insert(x.begin(), x.end());
		}
		~map()
		{
			mcleartree(mroot);
		}

		map& operator=( const map& other )
		{
			if (this != &other)
			{
				clear();
				mcomp = other.mcomp;
				mallo = other.mallo;
				insert(other.begin(), other.end());
			}
			return *this;
		}

		/* element access */
		T &operator[](const Key &key)
		{
			iterator it = find(key);
			if (it == end())
				return insert(ft::make_pair(key, mapped_type())).first->second;
			return it->second;
		}

		/* iterators */
		iterator begin()
		{
			bstree *first_node = mroot;
			while (first_node->left)
				first_node = first_node->left;
			return iterator(first_node);
		}
		const_iterator begin() const
		{
			bstree *first_node = mroot;
			while (first_node->left)
				first_node = first_node->left;
			return const_iterator(first_node);
		}
		iterator end() { return iterator(mend); }
		const_iterator end() const { return const_iterator(mend); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		/* capacity */
		bool empty() const { return this->msize == 0; }
		size_type size() const { return this->msize; }
		size_type max_size() const { return mallo.max_size(); }

		/* modifiers */
		void clear() { erase(begin(), end()); }

		// insert
		pair<iterator, bool> insert(const value_type &value)
		{
			bstree *node = NULL;
			bool found = false;
			node = mnewnode(value);
			if (mroot->value.first == key_type() && mroot == mend)
			{
				mfreenode(mroot);
				mend = mnewnode(ft::make_pair(key_type(), mapped_type()));
				mroot = node;
				mend->parent = mroot;
				mroot->right = mend;
				mroot->color = blacknode;
				mend->color = blacknode;
				mend->left = NULL;
				mend->right = NULL;
				msize++;
				return ft::make_pair(iterator(node), true);
			}
			else
			{
				found = madd(mroot, node);
			}
			if (node == NULL || !found)
				return ft::make_pair(iterator(mroot), false);
			msize++;
			return ft::make_pair(iterator(node), true);
		}
		iterator insert(iterator hint, const value_type &value)
		{
			(void)hint;
			return insert(value).first;
		}
		template <class InputIt>
		void insert(InputIt first, InputIt last)
		{
			for (InputIt it = first; it != last; it++)
				insert(*it);
		}

		// erase
		void erase(iterator pos) { erase(pos.base()->value.first); }
		void erase(iterator first, iterator last)
		{
			key_type key_to_del = first->first;
			for (iterator it = first; it != last;)
			{
				key_type tmp;
				it = find(key_to_del);
				tmp = (++it)->first;
				erase(key_to_del);
				key_to_del = tmp;
			}
		}
		size_type erase(const Key &key)
		{
			if (count(key) == 0)
				return 0;
			mdeletenode(mroot, key);
			return 1;
		}

		void swap(map &other)
		{
			mswap(mroot, other.mroot);
			mswap(mend, other.mend);
			mswap(msize, other.msize);
			mswap(mcomp, other.mcomp);
			mswap(mallo, other.mallo);
		}

		/* lookup */
		size_type count(const Key &key) const { return find(key) != end(); }

		iterator find( const Key& key )
		{
			for (iterator it = begin(); it != end(); it++)
				if (it->first == key)
					return it;
			return end();
		}
		const_iterator find( const Key& key ) const
		{
			for (const_iterator it = begin(); it != end(); it++)
				if (it->first == key)
					return it;
			return end();
		}

		// returns iterator >= key
		iterator lower_bound(const Key &key)
		{
			for (iterator it = begin(); it != end(); it++)
			{
				if (it->first == key || !mcomp(it->first, key))
					return it;
			}
			return end();
		}
		const_iterator lower_bound(const Key &key) const
		{
			for (const_iterator it = begin(); it != end(); it++)
			{
				if (it->first == key || !mcomp(it->first, key))
					return it;
			}
			return end();
		}

		// returns iterator > key
		iterator upper_bound(const Key &key)
		{
			for (iterator it = begin(); it != end(); it++)
			{
				if (it->first != key && !mcomp(it->first, key))
					return it;
			}
			return end();
		}
		const_iterator upper_bound(const Key &key) const
		{
			for (const_iterator it = begin(); it != end(); it++)
			{
				if (it->first != key && !mcomp(it->first, key))
					return it;
			}
			return end();
		}

		ft::pair<iterator, iterator> equal_range(const Key &key)
		{
			return ft::make_pair(lower_bound(key), upper_bound(key));
		}
		ft::pair<const_iterator, const_iterator> equal_range(const Key &key) const
		{
			return ft::make_pair(lower_bound(key), upper_bound(key));
		}

		/* observers */
		key_compare key_comp() const { return mcomp; }
		value_compare value_comp() const { return value_compare(mcomp); }

		/* allocator */
		allocator_type get_allocator() const { return mallo; }

	private:
		/* methods */
		void minitialization()
		{
			mroot = mnewnode(ft::make_pair(key_type(), mapped_type()));
			mroot->color = blacknode;
			mroot->isleftchild = false;
			mend = mroot;
			msize = 0;
		}

		bstree *mgetnode(const Key &key)
		{
			if (count(key) == 0)
				return mend;
			bstree * node = mroot;
			while (node->value.first != key)
			{
				if (node->value.first > key)
					node = node->left;
				else
					node = node->right;
			}
			return node;
		}
		
		template<typename Type>
		void mswap(Type &a, Type &b)
		{
			Type tmp = a;
			a = b;
			b = tmp;
		}

		bstree *mfindsibling(bstree *p, bstree *node)
		{
			if (node == mroot)
				return NULL;
			if (p)
			{
				if (p->left == node)
					return p->right;
				if (p->right == node)
					return p->left;
			}
			return NULL;
		}

		void mreplacenode(bstree *root, bstree *child)
		{
			if (child != NULL)
				child->parent = root->parent;
			if (root == mroot && child != NULL)
			{
				mroot = child;
				child->color = blacknode;
			}
			else
			{
				if (root->isleftchild)
				{
					root->parent->left = child;
					if (child)
						child->isleftchild = true;
				}
				else
				{
					root->parent->right = child;
					if (child)
						child->isleftchild = false;
				}
			}
		}
		void mrelinkchildren(bstree *node, bstree *new_node)	
		{
			new_node->left = node->left;
			new_node->right = node->right;
			if (node->left)
				node->left->parent = new_node;
			if (node->right)
				node->right->parent = new_node;
		}

		void mdeletecase6(bstree *p, bstree *node)
		{
			bstree *sibling = mfindsibling(p, node);
			if (sibling)
			{
				if (sibling->parent)
				{
					sibling->color = sibling->parent->color;
					sibling->parent->color = blacknode;
				}
				if (p->left == node)
				{
					if (sibling->right)
						sibling->right->color = blacknode;
					mleftrotate(p);
				}
				else
				{
					if (sibling->left)
						sibling->left->color = blacknode;
					mrightrotate(p);
				}
				if (sibling->parent == NULL)
					mroot = sibling;
			}
		}
		void mdeletecase5(bstree *p, bstree *node)
		{
			bstree *sibling = mfindsibling(p, node);
			if (sibling && sibling->color == blacknode)
			{
				if (p->left == node)
				{
					// if sibling black && sibling left red && sibling right black
					if ((sibling->right == NULL ||
						 (sibling->right && sibling->right->color == blacknode)) &&
						(sibling->left && sibling->left->color == rednode))
					{
						mrightrotate(sibling);
						sibling->color = blacknode;
						p->color = rednode;
					}
				}
				else if (p->right == node)
				{
					// if sibling black && sibling left black && sibling right red
					if ((sibling->left == NULL ||
						 (sibling->left && sibling->left->color == blacknode)) &&
						(sibling->right && sibling->right->color == rednode))
					{
						mleftrotate(sibling);
						sibling->color = blacknode;
						p->color = rednode;
					}
				}
			}
			mdeletecase6(p, node);
		}
		void mdeletecase4(bstree *p, bstree *node)
		{
			bstree *sibling = mfindsibling(p, node);
			int valid_condition = 0;
			// both sibling && sibling children are blacknode
			if (sibling)
			{
				if (sibling->color == blacknode &&
					(sibling->left == NULL ||
					 (sibling->left && sibling->left->color == blacknode)) &&
					(sibling->right == NULL ||
					 (sibling->right && sibling->right->color == blacknode)))
					valid_condition = 1;
			}
			if (p->color == rednode && valid_condition)
			{
				sibling->color = rednode;
				p->color = blacknode;
				return;
			}
			else
				mdeletecase5(p, node);
		}
		void mdeletecase3(bstree *p, bstree *node)
		{
			bstree *sibling = mfindsibling(p, node);
			int valid_condition = 0;
			// both sibling && sibling children are blacknode
			if (sibling)
			{
				if (sibling->color == blacknode && (sibling->left == NULL ||
					 (sibling->left && sibling->left->color == blacknode)) &&
					(sibling->right == NULL || (sibling->right &&
												sibling->right->color == blacknode)))
					valid_condition = 1;
			}
			if (p->color == blacknode && valid_condition)
			{
				sibling->color = rednode;
				mdeletecase1(p->parent, p);
			}
			else
				mdeletecase4(p, node);
		}
		void mdeletecase2(bstree *p, bstree *node)
		{
			bstree *sibling = mfindsibling(p, node);
			if (sibling && sibling->color == rednode)
			{
				if (sibling->isleftchild)
				{
					mrightrotate(p);
					sibling->color = blacknode;
					p->color = rednode;
				}
				else
				{
					mleftrotate(p);
					sibling->color = blacknode;
					p->color = rednode;
				}
				if (sibling->parent == NULL)
				{
					mroot = sibling;
				}
			}
			mdeletecase3(p, node);
		}
		void mdeletecase1(bstree *p, bstree *node)
		{
			if (p == NULL)
			{
				mroot = node;
				node->color = blacknode;
				return;
			}
			mdeletecase2(p, node);
		}
		void mdeleteonechild(bstree *node)
		{
			bstree *child = NULL;
			bstree *parent = node->parent;
			if (node->left == NULL)
			{	
				if (node->right)
					child = node->right;
			}
			else
			{
				if (node->left)
					child = node->left;
			}
			mreplacenode(node, child);
			if (node->color == blacknode)
			{
				if (child && child->color == rednode)
				{
					child->color = blacknode;
				}
				else
				{
					mdeletecase1(parent, child);
				}
			}
			if (findmax(mroot) != mend)
			{
				bstree *max = findmax(mroot);
				max->right = mend;
				mend->parent = max;
			}
			mfreenode(node);
		}
		void mdeletenode(bstree *node, const Key &key)
		{
			if (node == NULL || node == mend)
				return;
			if (node->value.first == key)
			{
				// node has at least one null leaf
				if (node->left == NULL ||
					node->right == NULL || node->right == mend)
				{
					mdeleteonechild(node);
				}
				else
				{
					bstree *inorsuc = ft::findmin(node->right);
					bstree *repl_node = mnewnode(ft::make_pair(inorsuc->value.first, inorsuc->value.second));
					mreplacenode(node, repl_node);
					repl_node->color = node->color;
					mrelinkchildren(node, repl_node);
					mdeletenode(node->right, inorsuc->value.first);
					mfreenode(node);
					msize++;
				}
			}
			else
			{
				if (node->value.first < key)
					mdeletenode(node->right, key);
				else
					mdeletenode(node->left, key);
			}
		}

		bstree *mnewnode(const value_type &value)
		{
			bstree *node = mnode.allocate(1);
			mallo.construct(&node->value, value);
			node->left = NULL;
			node->right = NULL;
			node->parent = NULL;
			node->color = rednode;
			node->isleftchild = false;
			return node;
		}

		void mfreenode(bstree *node)
		{
			mallo.destroy(&node->value);
			mnode.deallocate(node, 1);
			node = NULL;
			if (msize)
				msize--;
		}

		void mcleartree(bstree *node)
		{
			if (node->left)
				mcleartree(node->left);
			if (node->right && node->right != mend)
				mcleartree(node->right);
			if (node == mroot && mroot != mend)
			{
				mfreenode(mend);
				msize++;
			}
			mfreenode(node);
		}

		bool madd(bstree* parent, bstree * new_node)
		{
			if (count((new_node->value).first))
			{
				mfreenode(new_node);
				msize++;
				return false;
			}
			// add to parent right side (if key_comp() == ft::less)
			if (key_comp()((parent->value).first, (new_node->value).first))
			{
				if (parent->right == NULL || parent->right == mend)
				{
					if (parent->right == mend)
					{
						new_node->right = mend;
						mend->parent = new_node;
					}
					parent->right = new_node;
					new_node->parent = parent;
					new_node->isleftchild = false;
					mcheckcolor(new_node);
					return true;
				}
				else
					madd(parent->right, new_node);
			}
			else // add to parent left side
			{
				if (parent->left == NULL)
				{
					parent->left = new_node;
					new_node->parent = parent;
					new_node->isleftchild = true;
					mcheckcolor(new_node);
					return true;
				}
				else
					madd(parent->left, new_node);
			}
			return true;
		}

		void mcorrecttree(bstree * node)
		{
			if (node->parent->isleftchild)
			{
				// if aunt is black
				if (node->parent->parent->right == NULL || node->parent->parent->right == mend || node->parent->parent->right->color == blacknode)
				{
					mrotate(node);
					return;
				}
				if (node->parent->parent->right != NULL)
				{
					// grandpa red, parent and aunt black
					if (node->parent->parent != mroot)
						node->parent->parent->color = rednode;
					node->parent->parent->right->color = blacknode;
					node->parent->color = blacknode;
					return;
				}
			}
			if (!node->parent->isleftchild)
			{
				if (node->parent->parent->left == NULL || node->parent->parent->left->color == blacknode)
				{
					mrotate(node);
					return;
				}
				if (node->parent->parent->left != NULL) 
				{
					// grandpa becomes rednode
					node->parent->parent->color = rednode;
					node->parent->parent->left->color = blacknode;
					node->parent->color = blacknode;
					return;
				}
			}
		}

		void mrightleftrotate(bstree *node)
		{
			mrightrotate(node->right);
			mleftrotate(node);
		}
		void mleftrightrotate(bstree *node)
		{
			mleftrotate(node->left);
			mrightrotate(node);
		}

		void mrightrotate(bstree *node)
		{
			bstree * tmp = node->left;
			node->left = tmp->right;
			if (node->left != NULL)
			{
				node->left->parent = node;
				node->left->isleftchild = true;
			}
			if (node->parent == NULL)
			{
				mroot = tmp;
				tmp->parent = NULL;
			}
			else
			{
				tmp->parent = node->parent;
				if (node->isleftchild)
				{
					tmp->isleftchild = true;
					tmp->parent->left = tmp;
				}
				else
				{
					tmp->isleftchild = false;
					tmp->parent->right = tmp;
				}
			}
			tmp->right = node;
			node->isleftchild = false;
			node->parent = tmp;
		}
		void mleftrotate(bstree *node)
		{
			bstree * tmp = node->right;
			node->right = tmp->left;
			if (node->right != NULL && node->right != mend)
			{
				node->right->parent = node;
				node->right->isleftchild = false;
			}
			if (node->parent == NULL)
			{
				mroot = tmp;
				tmp->parent = NULL;
			}
			else
			{
				tmp->parent = node->parent;
				if (node->isleftchild)
				{
					tmp->isleftchild = true;
					tmp->parent->left = tmp;
				}
				else
				{
					tmp->isleftchild = false;
					tmp->parent->right = tmp;

				}
			}
			tmp->left = node;
			node->isleftchild = true;
			node->parent = tmp;
		}

		void mrotate(bstree *node)
		{
			if (node->isleftchild)
			{
				// node left, parent left, right rotation
				if (node->parent->isleftchild) 
				{
					mrightrotate(node->parent->parent);
					node->parent->color = blacknode;
					node->color = rednode;
					if (node->parent->right != NULL)
						node->parent->right->color = rednode;
					return;
				}
				else // node left, parent right, right left rotation
				{
					mrightleftrotate(node->parent->parent);
					node->color = blacknode;	  // node becomes parent black
					node->right->color = rednode; // children become red
					node->left->color = rednode;
					return;
				}
			}
			if (!node->isleftchild)
			{
				// node right, parent right, left rotation
				if (!node->parent->isleftchild) 
				{
					mleftrotate(node->parent->parent);
					node->parent->color = blacknode;
					node->color = rednode;
					if (node->parent->left != NULL)
						node->parent->left->color = rednode;
					return;
				}
				else // node right, parent left, left right rotation
				{
					mleftrightrotate(node->parent->parent);
					node->color = blacknode;
					node->right->color = rednode;
					node->left->color = rednode;
					return;
				}
			}
		}

		void mcheckcolor(bstree *node)
		{
			if (node == mroot)
			{
				if (mroot->color == rednode)
					mroot->color = blacknode;
				return;
			}
			if (node->color == rednode && node->parent->color == rednode)
			{
				mcorrecttree(node);
				if (node == mroot) // after mcorrecttree node may be mroot
				{
					mcheckcolor(node);
					return;
				}
			}
			mcheckcolor(node->parent);
		}

	};

		/* non member functions */
		template <class Key, class T, class Compare, class Alloc>
		bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs,
						const ft::map<Key, T, Compare, Alloc> &rhs)
		{
			if (lhs.size() != rhs.size())
				return false;
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}
	
		template <class Key, class T, class Compare, class Alloc>
		bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs,
						const ft::map<Key, T, Compare, Alloc> &rhs)
		{
			return !(lhs == rhs);
		}
	
		template <class Key, class T, class Compare, class Alloc>
		bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs,
					   const ft::map<Key, T, Compare, Alloc> &rhs)
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}
	
		template <class Key, class T, class Compare, class Alloc>
		bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs,
						const ft::map<Key, T, Compare, Alloc> &rhs)
		{
			return !(rhs < lhs);
		}
	
		template <class Key, class T, class Compare, class Alloc>
		bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs,
					   const ft::map<Key, T, Compare, Alloc> &rhs)
		{
			return rhs < lhs;
		}
	
		template <class Key, class T, class Compare, class Alloc>
		bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs,
						const ft::map<Key, T, Compare, Alloc> &rhs)
		{
			return !(lhs < rhs);
		}
	
		template <class Key, class T, class Compare, class Alloc>
		void swap(ft::map<Key, T, Compare, Alloc> &lhs,
				  ft::map<Key, T, Compare, Alloc> &rhs)
		{
			lhs.swap(rhs);
		}

} // namespace ft

#endif