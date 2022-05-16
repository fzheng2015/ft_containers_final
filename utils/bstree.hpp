#ifndef BSTREE_HPP
#define BSTREE_HPP

namespace ft
{
	enum nodeColor
	{
		rednode = true,
		blacknode = false
	};

	template <typename T>
	struct bstree
	{
		T value;
		nodeColor color;
		bstree *parent;
		bstree *left;
		bstree *right;
		bool isleftchild;
	};

	template <class T>
	bstree<T> *findmin(bstree<T> *node)
	{
		if (!node)
			return NULL;
		while (node->left)
			node = node->left;
		return node;
	}

	template <class T>
	bstree<T> *findmax(bstree<T> *node)
	{
		if (!node)
			return NULL;
		while (node->right)
			node = node->right;
		return node;
	}

	template <class T>
	bstree<T> *findnext(bstree<T> *node)
	{
		if (node->right)
			return findmin(node->right);
		bstree<T> *parent = node->parent;
		while (parent && node == parent->right)
		{
			node = parent;
			parent = parent->parent;
		}
		return parent;
	}

	template <class T>
	bstree<T> *findprev(bstree<T> *node)
	{
		if (node->left)
			return findmax(node->left);
		bstree<T> *parent = node->parent;
		while (parent && node == parent->left)
		{
			node = node->parent;
			parent = parent->parent;
		}
		return parent;
	}

} // namespace ft

#endif
