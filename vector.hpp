#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stddef.h>
#include <memory>
#include <cmath>
#include <iostream>
namespace ft {

    template<typename T, class allocator_type = std::allocator<T> >
    class vector{
    private:
        size_t                  sz;
        size_t                  cpcty;
        T*                      ptr;
        allocator_type          alloc;


    public:
        struct iterator {
        };

        vector (const allocator_type& alloc = allocator_type()) {
            this->sz = 0;
            this->cpcty = 0;
            this->ptr = NULL;
            this->alloc = alloc;
        }

        vector (size_t n, const T& val = T(), const allocator_type& alloc = allocator_type()) {
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
            return std::pow(2, (64-sizeof(T))) - 1;
        }

        size_t capacity() const {
            return this->cpcty;
        }

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

        bool empty() const {
            if (this->sz == 0)
                return true;
            return false;
        }

        // + изменяет размер вектора до размера n, если текущий размер >= n, то ничего не делает, вроде норм написано
        void reserve (size_t n) {
            T* temp_ptr = NULL;
            T* for_del = NULL;
            size_t new_cpcty = this->cpcty * 2;
            std::cout << "here11" << std::endl;
            if (n > this->cpcty) {
                if (n > new_cpcty) {
                    new_cpcty = n;
                }
                std::cout << "here12" << new_cpcty << std::endl;
                temp_ptr = this->alloc.allocate(new_cpcty);
                std::cout << "here121" << std::endl;
                for (size_t cnt = 0; cnt < this->sz; cnt++) {
                    std::cout << "here122" << std::endl;
                    this->alloc.construct(&temp_ptr[sizeof(T) * cnt], this->ptr[sizeof(T) * cnt]);
                }
                std::cout << "here13" << std::endl;
                for_del = this->ptr;
                this->ptr = temp_ptr;
                for (size_t cnt = this->sz; cnt > 0; --cnt) {
                    this->alloc.destroy(&for_del[sizeof(T) * sz]);
                }
                std::cout << "here14" << std::endl;
                this->alloc.deallocate(for_del, this->cpcty);
                std::cout << "here15" << std::endl;
                this->cpcty = new_cpcty;
            }
        }

        T operator[] (size_t n) {
            return ptr[sizeof(T) * n];
        }

        // + вставляет элемент поданный в качестве аргумента в конце массива
        void push_back (const T& val) {
            std::cout << "here" << std::endl;
            if (this->sz == this->cpcty) {
                reserve(this->cpcty + 1);
            }
            std::cout << "here1" << std::endl;
            this->ptr[sizeof(T) * this->sz] = val;
            this->sz++;
        }

        // + удаляет элемент с конца массива, уничтожая его
        void pop_back() {
            if (this->sz > 0) {
                this->alloc.destroy(&this->ptr[sizeof(T) * --this->sz]);
            }
        }

        ~vector() {};
    };
}

#endif //VECTOR_HPP
