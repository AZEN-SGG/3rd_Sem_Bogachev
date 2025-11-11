#include "tree.h"

void tree::t1_solve ()
{
	family extr;

	for (tree_node *prev = nullptr, *curr = root ; (curr != nullptr) ; prev = curr, curr = curr->right)
	{
		extr = find_max();
		
		if (extr.parent != nullptr)
		{
			switch (extr.dir)
			{
				case 0:
					extr.parent->left = curr;
					break;
				case 1:
					extr.parent->right = curr;
					break;
			}

			extr.parent = curr->left; // Like temp
			curr->left = extr.child->left;
			extr.child->left = extr.parent;

			extr.parent = curr->right; // Again
			curr->right = extr.child->right;
			extr.child->right = extr.parent;

			if (prev == nullptr) // if curr = root
				root = extr.child;
			else
				prev->right = extr.child;

			curr = extr.child;
		} // else - root, not needed to change smth


		if (curr->left != nullptr)
		{
			tree temp;
			temp.root = curr->left;
			temp.t1_solve();
			temp.root = nullptr;
		}
	}
}
