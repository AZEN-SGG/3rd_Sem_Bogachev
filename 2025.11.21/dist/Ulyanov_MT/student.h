#include "io_status.h"
#ifndef student_H
#define student_H
#include <stdio.h>
#include <string.h>

class tree;

class student
    {
    private:
        char* name = nullptr;
        int value = 0;
        
    public:
        student() = default;
        student(const student& x) = delete;
        student(student&& x)
            {
            name = x.name;
            x.name = nullptr;
            value = x.value;
            x.value = 0;
            }
        ~student()  {erase();}
        student& operator= (const student&& x) = delete;
        student& operator= (student&& x)
            {
            if (this == &x) return *this;
            erase();
            name = x.name; x.name = nullptr;
            value = x.value; x.value = 0;
            return *this;
            }
        void print(FILE* fp) const  {fprintf(fp, "%s %d\n", name, value);}
        io_status read(FILE* fp)
            {
            const int LEN = 1234;
            char n[LEN];
            int v;
            if (fscanf(fp, "%s%d", n, &v) != 2)
                {
                if (!feof(fp))  return io_status::format;
                return io_status::eof;
                }
            erase();
            return init(n, v);
            }
        void set(int s, int n, int i);
        void put(const char* x_name, int x_val) {init(x_name, x_val);}
        int operator> (const student& x) const
            {return (cmp(x) > 0 ? 1 : 0);}
        int operator>= (const student& x) const
            {return (cmp(x) >= 0 ? 1 : 0);}
        int operator< (const student& x) const
            {return (cmp(x) < 0 ? 1 : 0);}
        int operator<= (const student& x) const
            {return (cmp(x) <= 0 ? 1 : 0);}
        int operator== (const student& x) const
            {return (cmp(x) == 0 ? 1 : 0);}
            
        int get_value() const {return value;}
        int name_str(const student& stud)
            {
            if (!strstr(this->name, stud.name)) return 0;
            else return 1;
            }
        
        private:
            io_status init(const char* n, int v)
                {
                value = v;
                if (n != nullptr)
                    {
                    size_t len = strlen(n);
                    name = new char [len + 1];
                    if (name != nullptr)
                        {
                        for (size_t i = 0; i <= len; i++)
                            name[i] = n[i];
                        }
                    else return io_status::memory;
                    }
                else name = nullptr;
                return io_status::success;
                }
            void erase()
                {
                value = 0;
                if (name != nullptr)
                    {
                    delete [] name;
                    name = nullptr;
                    }
                }
            int cmp(const student& x) const
                {
                if (name == nullptr)
                    {
                    if (x.name != nullptr)  return -1;
                    return value - x.value;
                    }
                if (x.name == nullptr) return 1;
                int res = strcmp(name, x.name);
                if (res) return res;
                return value - x.value;
                }
    };
    
#endif
