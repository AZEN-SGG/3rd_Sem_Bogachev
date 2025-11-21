#ifndef TREE_H
#define TREE_H

#include "student.h"

#include <cstdio>

struct t_count;

class tree;

class tree_node : public student
{
	private:
		tree_node * down = nullptr;
		tree_node * level = nullptr;
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
		void erase_links () { down = nullptr; level = nullptr; }
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

        // Task 1
        static int get_count_subtree_with_k_children (const tree_node* curr, const int k);

        // Task 2
        static t_count get_count_nodes_in_subtree_less_k (const tree_node *curr, const int k);

        // Task 3
        static t_count get_count_nodes_in_subtree_less_k_levels (const tree_node *curr, const int k);

        // Task 4
        static int get_count_nodes_in_subtree_with_less_k_on_level (const tree_node *curr, const int k, const int c_level);
        static int get_count_nodes_on_level_subtree (const tree_node *curr, const int n, const int level);

        // Task 6
        static int get_count_nodes_in_branch_above_k (const tree_node *curr, const int k, const int level);

        // Task 7
        static int get_count_nodes_with_value_less_k (const tree_node *curr, const int k);
        static int delete_subtrees_with_value_less_k (tree_node *root, const int k);
        
		// Solves
		int t1_solve (const int k) const;
		int t2_solve (const int k) const;
		int t3_solve (const int k) const;
		int t4_solve (const int k) const;
		int t5_solve (const int k) const;
		int t6_solve (const int k) const;
		int t7_solve (const int k);
	private:
		static void delete_subtree (tree_node *curr)
		{
			if (curr == nullptr)
				return;
            tree_node *p, *next;
            for (p = curr->down ; p ; p = next)
            {
                next = p->level;
                delete_subtree(p);
            }
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
            for (tree_node *p = curr->down ; p ; p = p->level)
            {
                print_subtree(p, level + 1, r, fp);
            }
		}
		static void add_node_subtree (tree_node *curr, tree_node *x)
		{
            if (!curr->down)
            {
                curr->down = x;
                return;
            }

            if (*x < *curr)
            {
                if (*curr->down < *curr)
                    add_node_subtree(curr->down, x);
                else
                {
                    x->level = curr->down;
                    curr->down = x;
                }
            } else if (*x == *curr)
            {
                if (curr->down->level)
                {
                    x->level = curr->down->level;
                    curr->down->level = x;
                } else if (*curr->down < *curr)
                {
                    curr->down->level = x;
                } else
                {
                    x->level = curr->down;
                    curr->down = x;
                }
            } else
            {
                tree_node *p;
                for (p = curr->down ; p->level ; p = p->level);
                if  (*p > *curr)
                    add_node_subtree(p, x);
                else
                    p->level = x;
            }
        }
};

#endif // TREE_H
