#ifndef BTREE_H
#define BTREE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io_status.h"

template <class T> class b_tree_node;
template <class T> class b_tree;

template <class T>
class b_tree_node
{
    friend class b_tree<T>;
    private:
        T* values = nullptr; // 2*m elements array
        int size = 0; // number of children
        b_tree_node** children = nullptr; // 2*m+1 elements array
    
    public:
        b_tree_node () = default;
        ~b_tree_node ()  {delete_node ();}

        b_tree_node (const b_tree_node& x) = delete;
        b_tree_node (b_tree_node&& x)
        {
            values = x.values;
            children = x.children;
            size = x.size;
            x.erase_links ();
        }
       
        b_tree_node& operator= (const b_tree_node& x) = delete;
        b_tree_node& operator= (b_tree_node&& x)
        {
            if (this == &x)
                return *this;
            delete_node ();
            
            values = x.values;
            children = x.children;
            size = x.size;
            x.erase_links ();
            return *this;
        }
        
        void print (int p = 0,FILE *fp = stdout)const
        {
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < p; j++)
                    printf(" ");
                printf ("values[%2d] ", i + 1);
                values[i].print (fp);
            }
        }
        
        // Look for position for insert
        int bin_search (const T& x) const
        {
            int l = 0, r = size, m;
            while (l != r)
            {
                m = (l + r) * 0.5;
                if (values[m] < x) l = m + 1;
                else r = m;
            }
            return l;
        }
    
    private:
        void erase_links ()
        {
            values = nullptr;
            children = nullptr;
            size = 0;
        }
        void delete_node ()
        {
            if (values != nullptr)
                delete[] values; // destructor for each value[i]
            
            if (children != nullptr)// each children[i] is T* - standard type
                delete[] children;
            erase_links ();
        }
        
        io_status init (int m)
        {
            // default constructor for T is called
            values = new T[2 * m];
            if (values == nullptr)
            {
                return io_status::memory;
            }
            
            children = new b_tree_node*[2*m + 1];
            if (children == nullptr)
            {
                delete[] values;
                values = nullptr;
                return io_status::memory;
            }
            
            for (int i = 0; i < 2 * m + 1; ++i) // there is no default constructor for T*
            {
                children[i] = nullptr;
            }
            size = 0;
            return io_status::success;
        }
        
        // Insert value ’x’ with children ’down’ at position ’index’
        // into the node (assuming enough space)
        void add_value (T& x, b_tree_node<T>* down, int index)
        {
            for (int i = size; i > index; i--)
            {
                values[i] = static_cast<T&&>(values[i - 1]);
                children[i + 1] = children[i];
            }
            values[index] = static_cast<T&&>(x);
            children[index + 1] = down;
            size++;
        }
};

template <class T>
class b_tree
{
    private:
        int m = 0; // B-tree base
        b_tree_node<T> * root = nullptr;
    
    public:
        b_tree (int i = 0) {m = i;}
        ~b_tree()
        {
            delete_subtree (root);
            erase_links ();
        }

        io_status read (FILE * fp = stdin, unsigned int max_read = -1)
        {
            delete_subtree(root);
            root = nullptr;
            
            T tmp; io_status r;
            unsigned int i=0;
            while(i<max_read && tmp.read(fp)==io_status::success)
            {
                r = add_value(tmp);
                if(r!=io_status::success)
                {
                    delete_subtree(root);
                    erase_links();
                    return r;
                } i++;
            }

            if((!feof(fp)) && i<max_read) 
            {
                delete_subtree(root);
                erase_links();
                return io_status::format;
            }
            return io_status::success;
        }
        void print (int r, FILE * fp = stdout) const  {print_subtree (root, 0, r, fp);}
        

    private:
        void erase_links ()
        {
            m = 0;
            root = nullptr;
        }
        
        static void delete_subtree (b_tree_node<T> * curr)
        {
            if (curr == nullptr)
                return;
            for (int i = 0; i <= curr->size; i++)
                delete_subtree (curr->children[i]);
            delete curr;
        }
        
        static void print_subtree (b_tree_node<T> * curr, int level, int r, FILE * fp = stdout)
        {
            if (curr == nullptr || level > r)
                return;
            
            curr->print (level, fp);
            for (int i = 0; i <= curr->size; i++)
            {
                if (curr->children[i] && level + 1 <= r)
                {
                    for (int j = 0; j < level; j++)
                        fprintf (fp, " ");
                    fprintf (fp, "children[%2d]\n", i);
                    print_subtree (curr->children[i], level + 1, r, fp);
                }
            }
        }
        
        // Add element x to tree
        io_status add_value (T& x)
        {
            if (root == nullptr)
            {
                root = new b_tree_node<T>();
                if (root == nullptr)
                    return io_status::memory;
                
                if (root->init(m) != io_status::success)
                {
                    delete root;
                    return io_status::memory;
                }
                root->values[0] = static_cast<T&&>(x);
                root->size = 1;
                return io_status::success;
            }
            
            b_tree_node<T> *curr = root, *down = nullptr;
            io_status r = add_value_subtree (curr, down, x, m);
            if (r == io_status::memory)
                return io_status::memory;
            if (r == io_status::success)
                return io_status::success;
            
            // иначе r == io_status::create и был создан новый узел
            // который возвращается в ’down’
            // Создаем новый корень с одним значением ’x’
            // и двумя потомками ’curr’ and ’down’
            b_tree_node<T>* p = new b_tree_node<T>();
            if (p == nullptr)
                return io_status::memory;
            
            if (p->init (m) != io_status::success)
            {
                delete p;
                return io_status::memory;
            }
            
            p->values[0] = static_cast<T&&>(x);
            p->children[0] = curr;
            p->children[1] = down;
            p->size = 1;
            root = p;
            return io_status::success;
        }
        
        // Insert value ’x’ with children ’down’ at subtree ’curr’
        static io_status add_value_subtree (b_tree_node<T>*& curr, b_tree_node<T>*& down, T& x, int m)
        {
            int index = curr->bin_search (x);
            b_tree_node<T>* p = curr->children[index];
            
            if (p != nullptr)
            {   // Есть потомок 
                io_status r = add_value_subtree (p, down, x, m);
                if (r == io_status::memory)
                    return io_status::memory;
                if (r == io_status::success)
                    return io_status::success;
                
                // иначе r == io_status::create
                // и был создан новый узел,
                // который возвращается в ’down’
            }
            else down = nullptr;
            
            if (curr->size < 2 * m)
            { // Есть свободное место в текущем узле
                curr->add_value (x, down, index);
                return io_status::success;
            }
            else
            {   // Создаем новый узел
                b_tree_node<T>* p = new b_tree_node<T>();
                if (p == nullptr)
                    return io_status::memory;
                
                if (p->init (m) != io_status::success)
                {
                    delete p;
                    return io_status::memory;
                }
                
                if (index == m)
                { // ’x’ ровно посередине.
                  // Перемещаем вторую половину в новый узел
                    for (int i = 1; i <= m; i++)
                    {
                        p->values[i - 1] = static_cast<T&&>(curr->values[i + m - 1]);
                        p->children[i] = curr->children[i + m];
                        curr->children[i + m] = nullptr;
                    }
                    p->children[0] = down; // меньше всех
                }
                
                if (index < m)
                {   // ’x’ в первой половине.
                    // Перемещаем вторую половину в новый узел
                    for (int i = 0; i < m; i++)
                    {
                        p->values[i]
                        = static_cast<T&&>(curr->values[i + m]);
                        p->children[i] = curr->children[i + m];
                        curr->children[i + m] = nullptr;
                    }
                    
                    p->children[m] = curr->children[2 * m];
                    curr->children[2 * m] = nullptr;
                    
                    // сдвигаем элементы вправо
                    // и вставляем ’x’ в позицию ’index’
                    for (int i = m; i > index; i--)
                    {
                        curr->values[i] = static_cast<T&&> (curr->values[i - 1]);
                        curr->children[i + 1] = curr->children[i];
                    }
                    
                    curr->children[index + 1] = down;
                    curr->values[index] = static_cast<T&&>(x);
                    x = static_cast<T&&> (curr->values[m]);
                    // новый ’x’ - максимальный
                }
                
                if (index > m)
                {   // ’x’ во второй половине.
                    // Перемещаем вторую половину до ’index’
                    // в новый узел
                    p->children[0] = curr->children[m + 1];
                    curr->children[m + 1] = nullptr;
                    
                    for (int i = 1 ; i < index - m; i++)
                    {
                        p->values[i - 1] = static_cast<T&&> (curr->values[i + m]);
                        p->children[i] = curr->children[i + m + 1];
                        curr->children[i + m + 1] = nullptr;
                    }
                    
                    // Вставляем ’x’ в нужную позицию
                    p->values[index - m - 1] = static_cast<T&&> (x);
                    p->children[index - m] = down;
                    
                    // Перемещаем остаток второй половины в новый узел
                    for (int i = index - m + 1; i <= m; i++)
                    {
                        p->values[i - 1]
                        = static_cast<T&&> (curr->values[i + m - 1]);
                        p->children[i] = curr->children[i + m];
                        curr->children[i + m] = nullptr;
                    }
                    x = static_cast<T&&> (curr->values[m]);
                    // новый ’x’ - максимальный
                }
                down = p;
                p->size = m;
                curr->size = m;
                return io_status::create;
                // создан новый узел, он возвращается в ’down’
            }
        return io_status::success;
    }

public: //solutions
    
    /*кол-во элементов Student у узлов, имеющих ровно k потомков*/
    int solve_1(int k)
    {
        if(k<0) return 0;//CHECK
        return answ1(k,root);
    }
    
    static int answ1(int k, b_tree_node<T> * rootie)
    {
        if(rootie==nullptr) return 0;
        int count = 0, i;
        
        for(i=0; i<(1+rootie->size) && rootie->children[i]; i++) 
            count+=answ1(k,rootie->children[i]);

        return count + (i==k?rootie->size:0);
    }

    /*кол-во элементов Student в поддеревьях с <=k вершинами*/
    int solve_2(int k)
    {
        if(k<=0) return 0; //CHECK
        int answ = 0;
        answ2(k,&answ,root);
        return answ;
    }
    
    static int answ2(int k, int *answ, b_tree_node<T> * rootie)
    {
        //нашли все поддеревья с не более к узлами
        //посчитали все элты в таких поддеревьях
        //идем вниз до упору
        if(rootie==nullptr) return 0;
        
        int cd = 1, i;
        for(i=0; i<(1+rootie->size) && rootie->children[i]; i++) cd+=answ2(k,answ,rootie->children[i]);

        if(cd<=k) (*answ)+=rootie->size;
        return cd; 
    }

    /*кол-во элементов Student в поддеревьях с <=k уровнями */
    int solve_3(int k)
    {
        if(k<=0) return 0; //CHECK
        int answ = 0;
        answ3(k,&answ,root);
        return answ;
    }

    static int answ3(int k, int *answ, b_tree_node<T> * rootie)
    {
        //нашли все поддеревья с не более чем k уровнями
        //посчитали все элементы в таких поддеревьях
        if(rootie==nullptr) return 0;
        
        int nw = 2, depth = 0;
        
        for(int i=0; i<(1+rootie->size) && nw!=1; i++) //nw==1 <=> nw = 1 + 0 (т.е. след. нет)
        {
            nw = 1 + answ3(k,answ,rootie->children[i]);
            if(nw>depth) depth = nw;
        }

        if(depth<=k) (*answ)+=rootie->size; 
        return depth;
    }

    /*кол-во эл-в Student в поддеревьях с <=k узлами каждого ур-ня*/
    int solve_4(int k) 
    {
        if(k<=0) return 0;
        int answ = 0;
        answ4(k,&answ,root);
        return answ;
    }
    
    static int width_pass (int k, int level, b_tree_node<T> * rootie)
    {
        if (rootie == nullptr) return 0;
        if(level==0) return 1;

        int count = 0, tmp=0;
        for(int i=0; i<(1+rootie->size) && rootie->children[i]; i++)
        {
            tmp=width_pass(k,level-1,rootie->children[i]);
            if(count>k || tmp==-1) return -1;
            count+=tmp;
        }
        if(count>k || tmp==-1) return -1;
        return count;
    }

    static int answ4(int k, int *answ, b_tree_node<T> * rootie)
    {
        if(rootie==nullptr) return 1;//у ничего правильное число узлов в уровнях (0<=k)
        int i=0, tmp = 0, status = 1;
        //printf("weare looking at");rootie->print();printf("\n");
        for(i=0; i<(1+rootie->size) && rootie->children[i]; i++) 
        {   //смотрим детей rootie
            tmp = answ4(k,answ,rootie->children[i]);
            if(tmp==0) //если хоть у одного неправильное число узлов в урне, то у rootie тоже
            {
                status = 0;
                break;                                
            }
        }
        for(i=i+1; i<(1+rootie->size) && rootie->children[i]; i++) answ4(k,answ,rootie->children[i]);//досматриваем
        
        if(i>(k+1) || status==0) return 0;//если потомков больше к то rootie не подходит

        tmp = 1;
        for(i=2; tmp!=0; i++)// с корнем всё хорошо + проверили что след (1й) урнь ок
        {//если tmp = 0, то количество элв в этом урне 0, то есть посмотрели всё дерево
            tmp = width_pass(k,i,rootie);
            if(tmp == -1) return 0;
        }
        
        (*answ)+=rootie->size;
       // printf("counted:");rootie->print();printf("\n");
        return 1;
    }
    

    
    /*кол-во эл-в Student в k-м ур-не*/
    int solve_5(int k)
    {
        if(k<0) return 0; //CHECK
        if(k==0) //CHECK
        {
            if(root==nullptr) return 0;
            return root->size;
        }
        return answ5(k,root);
    }

    int answ5(int level, b_tree_node<T> * rootie)
    {
        if(rootie == nullptr) return 0;
        if(level==0) return rootie->size; //нужный ур-нь

        int count = 0;
        for(int i=0; i<(1+rootie->size) && rootie->children[i]; i++) 
            count+=answ5(level-1,rootie->children[i]);

        return count;
    }


    /*кол-во эл-в Student во всех ветвях длины k , начиная с корня*/
    int solve_6(int k)
    {
        if(k<=0) return 0;
        int answ = 0;
        answ6(k,1,&answ,root);
        return answ;
    }

    //суммарное количество эл-в во всех ветви длины k начиная с корня
    static int answ6(int k, int cur_height, int *answ, b_tree_node<T> * rootie)
    {
        if(rootie == nullptr) return 0; //длина=cur_height+1+элты ниже
        
        int tmp_depth = 0, i=0;
        for(i=0; i<(1+rootie->size) && rootie->children[i]; i++) 
        {
            tmp_depth = answ6(k,cur_height+1,answ,rootie->children[i]);
            if(cur_height+tmp_depth==k)
            {
                (*answ)+=rootie->size;
                break;
            }
        }
        for(i = i + 1;i<(1+rootie->size) && rootie->children[i]; i++) answ6(k,cur_height+1,answ,rootie->children[i]);
        
        return tmp_depth;
    }
};
#endif
