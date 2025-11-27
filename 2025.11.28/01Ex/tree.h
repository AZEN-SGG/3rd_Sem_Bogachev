#ifndef TREE_H
#define TREE_H

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
		~tree_node ()
		{
			erase_links();
		}
		
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

template <typename T>
class tree
{
	private:
		tree_node<T> * root = nullptr;
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
		io_status read_file (char *filename, unsigned int max_read = -1)
		{
			FILE *fp = fopen(filename, "r");
			if (!fp)
				return io_status::open;
		
			io_status ret = read(fp, max_read);
		
			fclose(fp);
			return ret;
		}

        // Side
        int num_level (int level);
        int depth_tree (int *max_diff);
        int find_min ();
        int del_with_value (const int value);

        // Solves
        int t1_solve ();
        int t2_solve ();
        int t3_solve ();
        int t4_solve ();
        int t5_solve ();
        int t6_solve ();
	private:
		static void delete_subtree (tree_node<T> *curr)
        {
            if (curr == nullptr)
                return;
            delete_subtree(curr->left);
            delete_subtree(curr->right);
            delete curr;
        }
        static void print_subtree (tree_node<T> *curr, int level, int r, FILE *fp = stdout)
        {
            if ((!curr) || (level > r))
                return;
            curr->print(fp, level);

            print_subtree(curr->left, level + 1, r, fp);
			fprintf(fp, "\n");
            print_subtree(curr->right, level + 1, r, fp);
        }
        static void add_node_subtree (tree_node<T> *curr, tree_node<T> *x)
        {
            if (*x < *curr)
            {
                if (curr->left == nullptr)
                    curr->left = x;
                else
                    add_node_subtree(curr->left, x);
            } else
            {
                if (curr->right == nullptr)
                    curr->right = x;
                else
                    add_node_subtree(curr->right, x);
            }
        }
};

#endif // TREE_H
