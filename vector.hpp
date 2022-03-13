#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stddef.h>
#include <memory>
#include <cmath>
#include <iostream>
#include <iterator>

namespace ft {

    template<typename T, class allocator_type = std::allocator<T> >
    class vector{

    private:
        size_t                  sz;
        size_t                  cpcty;
        T*                      ptr;
        allocator_type          alloc;

    public:

        class MyIterator : public std::iterator<std::random_access_iterator_tag, T>
        {
        private:
            T*                      p;
        public:
            MyIterator(int* x) :p(x) {}
            MyIterator(const MyIterator& mit) : p(mit.p) {}
            MyIterator& operator++() {++p;return *this;}
            MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
            bool operator==(const MyIterator& rhs) const {return p==rhs.p;}
            bool operator!=(const MyIterator& rhs) const {return p!=rhs.p;}
            int& operator*() {return *p;}
        };

        vector (const allocator_type& alloc = allocator_type()) : alloc(alloc){
            this->sz = 0;
            this->cpcty = 0;
            this->ptr = NULL;
            this->alloc = alloc;
        }

        vector (size_t n, const T& val = T(), const allocator_type& alloc = allocator_type()){// : alloc(alloc){
            this->sz = n;
            this->cpcty = n;
            this->alloc = alloc;
            this->ptr = this->alloc.allocate(n);
            for (size_t cnt = 0; cnt < sz; cnt++) {
                this->alloc.construct(&this->ptr[sizeof(T) * cnt], val);
            }
        }

//        template <class InputIterator>
//                vector (InputIterator first, InputIterator last,
//                        const allocator_type& alloc = allocator_type());

//        vector (const vector& x);

        size_t size() const{
            return this->sz;
        }

        size_t max_size() const{
            return alloc.max_size();
        }

        size_t capacity() const {
            return this->cpcty;
        }

        // изменяет вектор до нужных размеров
        void resize (size_t n, T val = T()) {
            if (n < this->sz) {
                for (; this->sz > n; this->sz--)
                    this->alloc.destroy(&ptr[sizeof(T) * this->sz]);
            }
            else if (n > this->cpcty) {
                reserve(n);
            }
            else if (n > this->sz)
                for(; this->sz < n;++this->sz)
                    ptr[sz - 1] = T(val);
        }

        // возвращает true, если вектор пуст, иначе - false
        bool empty() const {
            if (this->sz == 0)
                return true;
            return false;
        }

        // + изменяет размер вектора до размера n, если текущий запас >= n, то ничего не делает, вроде норм написано
        void reserve (size_t n) {
            T* temp_ptr = NULL;
            T* for_del = NULL;
            size_t new_cpcty = this->cpcty * 2;
            if (n > this->cpcty) {
                if (n > new_cpcty) {
                    new_cpcty = n;
                }
                temp_ptr = this->alloc.allocate(new_cpcty);
                for (size_t cnt = 0; cnt < this->sz; cnt++) {
                    this->alloc.construct(&temp_ptr[sizeof(T) * cnt], this->ptr[sizeof(T) * cnt]);
                }
                for_del = this->ptr;
                this->ptr = temp_ptr;
                for (size_t cnt = this->sz; cnt > 0; --cnt) {
                    this->alloc.destroy(&for_del[sizeof(T) * sz]);
                }
                this->alloc.deallocate(for_del, this->cpcty);
                this->cpcty = new_cpcty;
            }
        }

        const T& operator[] (size_t n) const{
            return ptr[sizeof(T) * n];
        }

        T& operator[] (size_t n) {
            return ptr[sizeof(T) * n];
        }

        // + вставляет элемент поданый в качестве аргумента в конец массива
        void push_back (const T& val) {
            if (this->sz == this->cpcty) {
                reserve(this->cpcty + 1);
            }
            this->ptr[this->sz] = val;
            this->sz++;
        }

        // + удаляет элемент с конца массива, уничтожая его
        void pop_back() {
            if (this->sz > 0) {
                this->alloc.destroy(&this->ptr[--this->sz]);
            }
        }

        void clear() {
            if (this->sz > 0) {
                for (; this->sz > 0; --this->sz) {
                    this->alloc.destroy(&this->ptr[sz - 1]);
                }
            }
        }

        ~vector() {
            this->clear();
            this->alloc.deallocate(this->ptr, this->cpcty);
        }
    };
};

#endif //VECTOR_HPP
