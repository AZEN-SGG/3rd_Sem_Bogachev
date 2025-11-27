#include "io_status.h"
#include "student.h"
#ifndef list_H
#define list_H
#include <stdio.h>
#include <string.h>

class list2;

class list2_node : public student
    {
    private:
        list2_node* next = nullptr;
        list2_node* prev = nullptr;
    public:
        list2_node() = default;
        list2_node(const list2_node&) = delete;
        list2_node(list2_node&& r):student((student&&) r)
            {
            next = r.next; r.next = nullptr;
            prev = r.prev; r.prev = nullptr;
            }
        ~list2_node() {next = nullptr; prev = nullptr;}
        list2_node& operator= (const list2_node&) = delete;
        list2_node& operator= (list2_node&& r)
            {
            *(student*)(this) = (student&&) r;
            next = r.next; r.next = nullptr;
            prev = r.prev; r.prev = nullptr;
            return *this;
            }
        list2_node* get_next() const {return next;}
        list2_node* get_prev() const {return prev;}
        void set_next(list2_node* r) {next = r;}
        void set_prev(list2_node* r) {prev = r;}
        list2_node* delete_node(int* flag, int i = 0);
        int is_max(int);
        friend class list2;
    };
    
class list2
    {
    private:
        list2_node* head = nullptr;
        static int m;
        static int r;
    public:
        list2() = default;
        list2(const list2& x) = delete;
        list2(list2&& x) {head = x.head; x.head = nullptr;}
        ~list2()
            {
            delete_list();
            head = nullptr;
            }
        list2& operator= (const list2& x) = delete;
        list2& operator= (list2&& x)
            {
            if (this == &x) return *this;
            this->delete_list();
            head = x.head; x.head = nullptr;
            return *this;
            }
            
        static void set_m (int m) {list2::m = m;}
        static void set_r (int r) {list2::r = r;}
        
        io_status read(FILE* fp = stdin)
            {
            unsigned int len = 0;
            unsigned int max_read = m;
            list2_node buf;
            list2_node* curr;
            list2_node* tail;
            io_status ret;
            if (max_read == 0) return io_status::success;
            len++;
            if ((ret = buf.read(fp)) != io_status::success) return io_status::format;
            head = new list2_node;
            if (head == nullptr) return io_status::memory;
            *head = (list2_node&&) buf;
            curr = head;
            while ((len < max_read) && (buf.read(fp) == io_status::success))
                {
                tail = new list2_node;
                if (tail == nullptr)
                    {
                    this->delete_list();
                    return io_status::memory;
                    }
                *tail = (list2_node&&) buf;
                curr->set_next(tail);
                tail->set_prev(curr);
                curr = tail;
                len++;
                }
            if ((!feof(fp)) && (len < max_read))
                {
                this->delete_list();
                return io_status::format;
                }
            return io_status::success;
            }
            
        void print(FILE* fp = stdout, int spaces = 0) const
            {
            int i = 0;
            const list2_node* curr;
            for (curr = head; curr != nullptr; curr = curr->get_next())
                {
                if (i >= r) break;
                for (int j = 0; j < spaces; j++) printf(" ");
                curr->print(fp);
                i++;
                }
            }
        int get_length() const
            {
            int count = 0;
            list2_node* curr;
            for (curr = head; curr; curr = curr->get_next()) count++;
            return count;
            }
            
        int get_value() const
            {
            int min = head->get_value();
            list2_node* curr;
            for (curr = head; curr; curr = curr->get_next()) {if (curr->get_value() < min) min = curr->get_value();}
            return min;
            }
            
        int operator< (const list2& b) const
            {
            if ((head == nullptr) && (b.head == nullptr)) return 1;
            if (head == nullptr) return 0;
            if (b.head == nullptr) return 0;
            if (*head < *(b.head)) return 1;
            return 0;
            }
        void delete_list()
            {
            list2_node* curr;
            list2_node* next;
            for (curr = head; curr; curr = next)
                {
                next = curr->get_next();
                delete curr;
                }
            }
    };
#endif
