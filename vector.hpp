#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stddef.h>
#include <memory>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include "vector_iterator.hpp"

namespace ft {

    template<typename T, class allocator_type = std::allocator<T> >
    class vector{
    private:
        size_t                             _sz;
        size_t                             _cpcty;
        T*                                 _ptr;
        allocator_type                     _alloc;

    public:
        typedef typename ft::RandIt<T>              iterator;
        typedef const typename ft::RandIt<T>        const_iterator;

        vector (const allocator_type& alloc = allocator_type()) {
            _sz = 0;
            _cpcty = 0;
            _ptr = NULL;
            _alloc = alloc;
        }

        vector (size_t n, const T& val = T(), const allocator_type& alloc = allocator_type()){
            _sz = n;
            _cpcty = n;
            _alloc = alloc;
            _ptr = _alloc.allocate(n);
            for (size_t cnt = 0; cnt < _sz; cnt++) {
                _alloc.construct(&_ptr[cnt], val);
            }
        }
//
//        template <class InputIterator>
//        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {
//            size_t n = last - first;
//            _sz = n;
//            _cpcty = n;
//            _alloc = alloc;
//            _ptr = _alloc.allocate(n);
//            for (size_t cnt = 0; cnt < _sz; cnt++) {
//                _alloc.construct(&_ptr[cnt], first[cnt]);
//            }
//        }

        vector (const vector& x) {
            _alloc = x.get_allocator();
            _sz = x.size();
            _cpcty = x.capacity();
            _ptr = _alloc.allocate(_cpcty);
            for (size_t cnt = 0; cnt < _sz; cnt++) {
                _alloc.construct(&_ptr[cnt], x[cnt]);
            }
        }

        void clear() {
            if (_sz > 0) {
                for (; _sz > 0; --_sz) {
                    _alloc.destroy(&_ptr[_sz - 1]);
                }
            }
        }

        iterator begin(){
            return iterator(_ptr);
        }

        const_iterator begin() const {
            return const_iterator(_ptr);
        }

        iterator end() {
            return iterator(&_ptr[_sz]);
        }
        const_iterator end() const {
            return const_iterator(&_ptr[_sz]);
        }

//        reverse_iterator rbegin();
//        const_reverse_iterator rbegin() const;

//        reverse_iterator rend();
//        const_reverse_iterator rend() const;

        size_t size() const{
            return _sz;
        }

        size_t max_size() const{
            return _alloc.max_size();
        }

        size_t capacity() const {
            return _cpcty;
        }

        // изменяет вектор до нужных размеров
        void resize (size_t n, T val = T()) {
            if (n < _sz) {
                for (; _sz > n; _sz--)
                    _alloc.destroy(&_ptr[sizeof(T) * _sz]);
            }
            else if (n > _cpcty) {
                reserve(n);
            }
            else if (n > _sz)
                for(; _sz < n;++_sz)
                    _ptr[_sz - 1] = T(val);
        }

        // возвращает true, если вектор пуст, иначе - false
        bool empty() const {
            if (_sz == 0)
                return true;
            return false;
        }

        // + изменяет размер вектора до размера n, если текущий запас >= n, то ничего не делает, вроде норм написано
        void reserve (size_t n) {
            T* temp_ptr = NULL;
            T* for_del = NULL;
            size_t new_cpcty = _cpcty * 2;
            if (n > _cpcty) {
                if (n > new_cpcty) {
                    new_cpcty = n;
                }
                temp_ptr = _alloc.allocate(new_cpcty);
                for (size_t cnt = 0; cnt < this->_sz; cnt++) {
                    _alloc.construct(&temp_ptr[sizeof(T) * cnt], _ptr[sizeof(T) * cnt]);
                }
                for_del = _ptr;
                _ptr = temp_ptr;
                for (size_t cnt = this->_sz; cnt > 0; --cnt) {
                    this->_alloc.destroy(&for_del[sizeof(T) * _sz]);
                }
                this->_alloc.deallocate(for_del, _cpcty);
                this->_cpcty = new_cpcty;
            }
        }

        const T& operator[] (size_t n) const{
            return _ptr[n];
        }

        T& operator[] (size_t n) {
            return _ptr[n];
        }

        T& at (size_t n) {
            if (n >= _sz) {
                throw std::out_of_range("Index out of range");
            }
            return _ptr[n];
        }

        const T& at (size_t n) const {
            if (n >= _sz) {
                throw std::out_of_range("Index out of range");
            }
            return _ptr[n];
        }

        T& front(){
            return _ptr;
        }

        const T& front() const{
            return _ptr;
        }

        T& back(){
            return _ptr[_sz - 1];
        }

        const T& back() const{
            return _ptr[_sz - 1];
        }


        template <class InputIterator>
        void assign (InputIterator first, InputIterator last) {
            InputIterator temp = first;
            size_t n = last - first;
            if (n > _sz) {
                T *_nptr = _alloc.allocate(n);
                for (;temp!=last; ++temp)
                    _alloc(*temp, *temp);
                clear();
                _alloc.deallocate(_ptr, _cpcty);
                _ptr = _nptr;
            }
            else {
                this->resize(n);
                for (size_t tmp = 0; tmp < n; ++tmp) {
                    _alloc.destroy(&_ptr[tmp]);
                    _alloc.construct(&_ptr[tmp], *temp);
                }
            }
        }

        void assign (size_t n, const T& val) {
            if (n > _sz) {
                T *_nptr = _alloc.allocate(n);
                for (size_t cnt = 0; cnt < _sz; cnt++) {
                    _alloc.construct(&_nptr[cnt], val);
                }
                clear();
                _alloc.deallocate(_ptr, _cpcty);
                _ptr = _nptr;
            }
            else {
                this->resize(n);
                for (size_t tmp = 0; tmp < n; ++tmp) {
                    _alloc.destroy(&_ptr[tmp]);
                    _alloc.const  ruct(&_ptr[tmp], val);
                }
            }
        }

        // + вставляет элемент поданый в качестве аргумента в конец массива
        void push_back (const T& val) {
            if (_sz == _cpcty) {
                reserve(_cpcty + 1);
            }
            _ptr[_sz] = val;
            _sz++;
        }

        // + удаляет элемент с конца массива, уничтожая его
        void pop_back() {
            if (_sz > 0) {
                _alloc.destroy(&_ptr[--_sz]);
            }
        }

//        iterator insert (iterator position, const value_type& val) {
//            iterator end = --this->end();
//            if (this->_sz == this->_cpcty) {
//                reserve(this->_cpcty + 1);
//            }
//            for (;position_new!=position; --end) {
//
//            }
//        }
//
//        void insert (iterator position, size_type n, const value_type& val) {
//
//        }
//
//        template <class InputIterator>
//        void insert (iterator position, InputIterator first, InputIterator last) {
        allocator_type get_allocator() const {
            return _alloc;
        }

        ~vector() {
            clear();
            _alloc.deallocate(_ptr, _cpcty);
        }
    };

    template<typename T, class allocator_type >
    bool operator== (const vector<T,allocator_type>& lhs, const vector<T,allocator_type>& rhs) {
        return false;
    }
    template<typename T, class allocator_type >
    bool operator!= (const vector<T,allocator_type>& lhs, const vector<T,allocator_type>& rhs) {
        return false;
    }
    template<typename T, class allocator_type >
    bool operator<  (const vector<T,allocator_type>& lhs, const vector<T,allocator_type>& rhs) {
        return false;
    }
    template<typename T, class allocator_type >
    bool operator<= (const vector<T,allocator_type>& lhs, const vector<T,allocator_type>& rhs) {
        return false;
    }
    template<typename T, class allocator_type >
    bool operator>  (const vector<T,allocator_type>& lhs, const vector<T,allocator_type>& rhs) {
        return false;
    }
    template<typename T, class allocator_type >
    bool operator>= (const vector<T,allocator_type>& lhs, const vector<T,allocator_type>& rhs) {
        return false;
    }

    template <typename T, class allocator_type>
    void swap (vector<T,allocator_type>& x, vector<T,allocator_type>& y) {
        return;
    }
};

#endif //VECTOR_HPP
