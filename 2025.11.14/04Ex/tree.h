#ifndef TREE_H
#define TREE_H

#include "student.h"

#include <cstdio>

class tree;
class family;
class level_adds;

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
		io_status read_file (char *filename, unsigned int max_read = -1);

		// Side
		int num_level (int level) const;
		int depth_tree (int *max_diff) const;
		int find_min () const; // by field value
		int del_with_value (const int value) const;

		static int get_count_total_subtree (tree_node *curr);
		int get_count_leaf () const;
		int get_count_1 () const;
		int get_count_2 () const;
		int get_height () const;
		int get_width () const;
		int get_balance () const;
	
		void print_stat (const char *executor, const int task, const double t = -1) const;
	
        // Task 1
		static family find_max_subtree (tree_node *root);

        // Task 2
		static family find_min_level_subtree (tree_node *curr, level_adds adds);
        family get_index_node (int n, int level) const;
        
        // Task 3
        static family find_absolute_left_subtree (tree_node *curr);
        static tree_node * balance_to_left_subtree (tree_node *root);

        // Task 4
        static family find_absolute_right_subtree (tree_node *curr);
        static tree_node * balance_to_right_subtree (tree_node *root);
		
		// Solves
		void t1_solve ();
		void t2_solve ();
		void t3_solve ();
		void t4_solve ();
		int t5_solve ();
		int t6_solve ();
	private:
		static void delete_subtree (tree_node *curr)
		{
			if (curr == nullptr)
				return;
			delete_subtree(curr->left);
			delete_subtree(curr->right);
			delete curr;
		}
		static void print_subtree (tree_node *curr, int level, int r, FILE *fp = stdout)
		{
			if ((curr == nullptr) || (level > r))
				return;
			int spaces = level << 1;
			for (int i = 0 ; i < spaces ; i++)
				fprintf(fp, " ");
			curr->print(fp);
			print_subtree(curr->left, level + 1, r, fp);
			print_subtree(curr->right, level + 1, r, fp);
		}
		static void add_node_subtree (tree_node *curr, tree_node *x)
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

class family
{
	tree_node *parent;
	tree_node *child;
	int dir;

	friend class tree;
};

#endif // TREE_H
