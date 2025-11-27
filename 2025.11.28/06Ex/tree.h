#ifndef TREE_H
#define TREE_H

#include "student.h"
#include "list.h"
#include "tree_node.h"

#include <cstdio>
#include <new>

// For the 4th task
struct t_count
{
	int len;
	int max;
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
			if (root)
				print_subtree(root, 0, r, fp);
		}

		io_status read (FILE *fp = stdin, unsigned int max_read = -1)
		{
			tree_node<T> x;
			io_status ret;

			if (x.read(fp) != (ret = io_status::success))
				return ret;

			root = new tree_node<T>((tree_node<T>&&)x);
			if (!root)
				return io_status::memory;

			unsigned int readed = 1;
			while ((readed < max_read) && (x.read(fp) == io_status::success))
			{
				tree_node<T> *curr = new tree_node<T>((tree_node<T>&&)x);
				if (!curr)
				{
					delete_subtree(root);
					return io_status::memory;
				}

				add_node_subtree(root, curr);
				readed++;
			} if ((!feof(fp)) && (readed < max_read))
			{
				delete_subtree(root);
				return io_status::format;
			}

			return io_status::success;
		}

		io_status read_file (char *filename, unsigned int max_read = -1)
		{
			FILE *fp = fopen(filename, "r");
			if (!fp)
				return io_status::open;
		
			io_status ret = read(fp, max_read);
		
			fclose(fp);
			return ret;
		}

		// Task 1
		static int number_leaves_in_subtree (const tree_node<T> * curr)
		{
			int count = 0,
				is_end = 0;

			const tree_node<T> *prev = nullptr;
			for (; curr ; prev = curr, curr = curr->right)
			{
				is_end = 0;
		
				tree_node<T> *left = curr->left;
				if (left)
					count += number_leaves_in_subtree(left);
				else
					is_end++;
			}
		
			if (is_end)
				count += prev->get_length();
		
			return count;
		}

        int t1_solve () const
		{
			return number_leaves_in_subtree(root);
		}
		
		// Task 2
		static int max_number_elem_in_branch_subtree (const tree_node<T> *curr)
		{
			int max_len = 0,
				len = 0;

			for (; curr ; curr = curr->right)
			{
				len += curr->get_length();

				tree_node<T> *left = curr->left;
				if (left)
				{
					int temp_len = len + max_number_elem_in_branch_subtree(left);
					max_len = (max_len < temp_len) ? temp_len : max_len;
				}
			}

			max_len = (max_len < len) ? len : max_len;

			return max_len;
		}

        int t2_solve () const
		{
			return max_number_elem_in_branch_subtree(root);
		}

		// Task 3
		static int num_level_subtree (const tree_node<T> *curr, int level)
		{
			int now = 0,
				number = 0;

			for (now = 1 ; (curr != nullptr) && (now < level) ; curr = curr->right, now++)
				number += num_level_subtree(curr->left, level - now);

			if ((curr != nullptr) && (level == now))
				number += curr->get_length();

			return number;
		}

        int t3_solve () const
		{
			int max_len = 0,
				len = 0,
				n = 1; // level

			if (root == nullptr)
				return 0;
			
			len = root->get_length();
			max_len = len;

			while (len != 0)
			{
				n++;
				len = num_level_subtree(root, n);
				max_len = (max_len < len) ? len : max_len;
			}

			return max_len;
		}

		// Task 4
		static t_count max_diff_between_subtrees_of_subtree (const tree_node<T> *curr)
		{
			t_count answer = {},
					temp = {};

			if (curr->left)
			{
				temp = max_diff_between_subtrees_of_subtree(curr->left);
				answer.max = temp.max;
				answer.len += temp.len;
			}

			int diff = temp.len;

			if (curr->right)
			{
				temp = max_diff_between_subtrees_of_subtree(curr->right);
				answer.max = (answer.max < temp.max) ? temp.max : answer.max;
				answer.len += temp.len;

				diff -= temp.len;
				diff = (diff < 0) ? -diff : diff;
			}
			
			answer.max = (answer.max < diff) ? diff : answer.max;

			answer.len += curr->get_length();

			return answer;
		}

		int t4_solve () const
		{
			if (!root)
				return 0;

			return max_diff_between_subtrees_of_subtree(root).max;
		}

		// Task 5
		static int get_length_all_nodes_with_1_child_in_subtree (const tree_node<T> *curr)
		{
			int count = 0;
			
			tree_node<T> *child = nullptr;
			for (; curr ; curr = child)
			{
				tree_node<T> *right = curr->right;

				child = curr->left;
				if (child && right)
				{
					count += get_length_all_nodes_with_1_child_in_subtree(child);
					child = right;
				} else if (child)
					count += curr->get_length();
				else if (right)
				{
					count += curr->get_length();
					child = right;
				}
			}

			return count;
		}

		int t5_solve () const
		{
			return get_length_all_nodes_with_1_child_in_subtree(root);
		}

		// Task 6
		// curr is non-nullptr
		static int find_min_value_subtree (const tree_node<T> *curr)
		{
			int min_val = curr->get_min_value();

			if (curr->left)
			{
				int temp_min = find_min_value_subtree(curr->left);
				min_val = (temp_min < min_val) ? temp_min : min_val;
			}

			for (curr = curr->right; curr ; curr = curr->right)
			{
				int temp_min = find_min_value_subtree(curr);
				min_val = (temp_min < min_val) ? temp_min : min_val;

				tree_node<T> *left = curr->left;
				if (left)
				{
					temp_min = find_min_value_subtree(curr->left);
					min_val = (temp_min < min_val) ? temp_min : min_val;
				}
			}

			return min_val;
		}

		int del_with_value (const int value)
		{
			int deleted = 0;

			tree_node<T> *parent = nullptr,
					  *curr = nullptr,
					  *child = nullptr;
			for (curr = root ; (curr != nullptr) ; parent = curr, curr = child)
			{
				child = nullptr;

				if (curr->has_elem_equal_n(value))
				{
					deleted++;
					delete_subtree(curr);
					if (parent == nullptr)
						root = nullptr;
					else
						parent->right = nullptr;
				} else
				{
					child = curr->left;
					if (child != nullptr)
					{
						tree<T> tmp;
						tmp.root = child;
						deleted += tmp.del_with_value(value);
						if (tmp.root == nullptr)
							curr->left = nullptr;
						else
							tmp.root = nullptr;
					}

					child = curr->right;
				}
			}

			return deleted;
		}

		int t6_solve ()
		{
			int deleted = 0;

			if (root == nullptr)
				return 0;

			int min_val = find_min_value_subtree(root);
			deleted = del_with_value(min_val);

			return deleted;
		}
	private:
		static void delete_subtree (tree_node<T> * curr)
        {
            if (curr == nullptr)
                return;
            delete_subtree(curr->left);
            delete_subtree(curr->right);
            delete curr;
        }
        static void print_subtree (tree_node<T> * curr, int level, int r, FILE *fp = stdout)
        {
            curr->print(fp, level);
			
			if (level + 1 > r)
				return;

			if (curr->left)
				print_subtree(curr->left, level + 1, r, fp);

			if (curr->right)
			{
				if (curr->left)
					fprintf(fp, "\n");
				print_subtree(curr->right, level + 1, r, fp);
			}
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

extern template class tree<student>;
extern template class tree<list2<student>>;

#endif // TREE_H
