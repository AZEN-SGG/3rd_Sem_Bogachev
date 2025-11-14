#include "solve_07.h"

family tree::get_node_by_index (bin_pos pos) const
{
    pos.index -= 1 << pos.level;
    pos.level--;

    int dir = 0;
    tree_node *curr = root,
              *prev = nullptr;
    while (pos.level >= 0 && curr != nullptr)
    {
        prev = curr;

        if (pos.index < (1 << pos.level))
        {
            curr = curr->left;
            dir = 0;
        } else
        {
            curr = curr->right;
            dir = 1;
            pos.index -= (1 << pos.level);
        }

        pos.level--;
    }

    family node;
    node.parent = prev;
    node.child = curr;
    node.dir = dir;

    return node;
}

void tree::delete_seq (sequence *seq)
{
    for (int i = seq->from ; i <= seq->to ; ++i)
    {
        bin_pos pos {
            i,
            31 - __builtin_clz(i),
        };

        family to_del = get_node_by_index(pos);
        if (to_del.child != nullptr)
        {
            delete_subtree(to_del.child);
            if (to_del.parent != nullptr)
            {
                if (to_del.dir)
                    to_del.parent->right = nullptr;
                else
                    to_del.parent->left = nullptr;
            } else
            {
                root = nullptr;
                return;
            }
        }
    }
}

int tree::delete_seq_longer_k_on_level (tree_node *curr, bin_pos pos, int on_level, sequence *seq, const student& x)
{
    int deleted = 0;

    for (; (pos.level < on_level) && (curr != nullptr) ; curr = curr->right, 
            pos.index = (pos.index << 1) + 1, pos.level++)
    {
        if (curr->left != nullptr)
        {
            bin_pos left_pos {
                pos.index << 1,
                pos.level + 1,
            };

            deleted += delete_seq_longer_k_on_level(curr->left, left_pos, on_level, seq, x);
            if (deleted >= (1 << (on_level)))
                return deleted;
        }
    }

    if (curr != nullptr)
    {
        if (strstr(curr->name, x.name) == nullptr)
        {
            if (seq->from > 0)
            {
                seq->to = pos.index - 1;
                deleted += (seq->to - seq->from + 1);
                if (seq->len >= x.value)
                    return 1 << on_level;
                seq->from = -1;
                seq->len = 0;
            } 
        } else
        {
            if (seq->from < 0)
            {
                seq->from = pos.index;
                seq->len = 1;
            } else
                seq->len++;
        }
    } else
        deleted++;

    return deleted;
}

void tree::t7_solve (const student& x)
{
    sequence seq {
        -1,
        -1,
        0,
    };

    int level = 0, deleted = 0; 
    do {
        bin_pos pos {
            1,
            0,
        };
        
        deleted = delete_seq_longer_k_on_level(root, pos, level, &seq, x);
        if (seq.from > 0)
        {
            if ((seq.len) >= x.value)
            {
                seq.from = 1 << level;
                seq.to = (1 << (level + 1)) - 1;
                delete_seq(&seq);
            }
            seq.from = -1;
            seq.len = 0;
        }

        level++;
    } while (deleted < (1 << (level - 1)));
}
