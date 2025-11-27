#ifndef TREE_NODE_H
#define TREE_NODE_H

#include "student.h"
#include "list.h"

#include <cstdio>

template <typename T>
class tree;

template <typename T>
class tree_node : public T
{
	private:
		tree_node * left = nullptr;
		tree_node * right = nullptr;
	public:
		tree_node () = default;
		tree_node (const tree_node&) = delete;
		tree_node (tree_node&& x) : T ((T&&)x)
		{
			erase_links();
			x.erase_links();
		}
		~tree_node () { erase_links(); }
		
		tree_node& operator= (const tree_node&) = delete;
		tree_node& operator= (tree_node&& x)
		{
			if (this == &x)
				return *this;
			(T&&)*this = (T&&)x;

			erase_links();
			x.erase_links();

			return *this;
		}

		friend class tree<T>;
	private:
		void erase_links () { left = nullptr; right = nullptr; }
};

extern template class tree_node<student>;
extern template class tree_node<list2<student>>;

#endif // TREE_NODE_H
