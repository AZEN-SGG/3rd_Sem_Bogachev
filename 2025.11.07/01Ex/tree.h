#ifndef TREE_H
#define TREE_H

class tree;
class tree_node : public student
{
	private:
		tree_node * left = nullptr;
		tree_node * right = nullptr;
	public:
		tree_node () = default;
		tree_node (const tree_node&) = delete;
		tree_node (tree_node&& x) : student ((student&&)x)
		{
			erase_links();
			x.erase_links();
		}
		~tree_node ()
		{
			erase_links();
		}
		
		tree_node& operator= (const tree_node&) = delete;
		tree_node& operator= (tree_node&& x)
		{
			if (this == &x)
				return *this;
			(student&&)*this = (student&&)x;

			erase_links();
			x.erase_links();

			return *this;
		}

		friend class tree;
	private:
		void erase_links () { left = nullptr; right = nullptr; }
};

class tree
{
	private:
		tree_node * root = nullptr;
	public:
		tree () = default;
		tree (const tree&) = delete;
		tree (tree&& x)
		{
			root = x.root;
			x.root = nullptr;
		}
		~tree ()
		{
			delete_subtree(root);
			root = nullptr;
		}

		tree& operator= (const tree&) = delete;
		tree& operator= (tree&& x)
		{
			if (this == &x)
				return *this;
			delete_subtree(root);
			root = x.root;
			x.root = nullptr;
			return *this;
		}

		void print (unsigned int r = 10, FILE *fp = stdout) const
		{
			print_subtree(root, 0, r, fp);
		}
		io_status read (FILE *fp = stdin, unsigned int max_read = -1);
	private:
		static void delete_subtree (tree_node *curr

#endif // TREE_H
