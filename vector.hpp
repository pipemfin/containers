#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stddef.h>
#include <memory>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include "iterator.hpp"
#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"

namespace ft {

    template<typename T, class allocator_type = std::allocator<T> >
    class vector{
    public:
        size_t                             _sz;
        size_t                             _cpcty;
        T*                                 _ptr;
        allocator_type                     _alloc;

    public:
        typedef typename ft::RandIt<T>                              iterator;
        typedef const typename ft::RandIt<T>                        const_iterator;
        typedef typename ft::reverse_iterator<iterator>             reverse_iterator;
        typedef const typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

        vector (const allocator_type& alloc = allocator_type()) {
            _sz = 0;
            _cpcty = 0;
            _ptr = NULL;
            _alloc = alloc;
        }

        vector (size_t n, const T& val = T(), const allocator_type& alloc = allocator_type()) {
            _sz = n;
            _cpcty = n;
            _alloc = alloc;
            _ptr = _alloc.allocate(n);
            for (size_t cnt = 0; cnt < _sz; cnt++) {
                _alloc.construct(&_ptr[cnt], val);
            }
        }

        template <class InputIterator>
        vector (typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator_type& alloc = allocator_type()) {
            size_t n = last - first;
            _sz = n;
            _cpcty = n;
            _alloc = alloc;
            _ptr = _alloc.allocate(n);
            for (size_t cnt = 0; cnt < _sz; cnt++) {
                _alloc.construct(&_ptr[cnt], first[cnt]);
            }
        }

        vector (const vector& x) {
            _alloc = x.get_allocator();
            _sz = x.size();
            _cpcty = x.capacity();
            _ptr = _alloc.allocate(_cpcty);
            for (size_t cnt = 0; cnt < _sz; cnt++) {
                _alloc.construct(&_ptr[cnt], x[cnt]);
            }
        }

        vector& operator= (const vector& x) {
            if (this == &x)
                return *this;
            resize(x.size());
            assign(x.begin(), x.end());
            return *this;
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

        reverse_iterator rbegin() {
            return reverse_iterator(iterator(&_ptr[_sz - 1]));
        }

        const_reverse_iterator rbegin() const {
            return reverse_iterator(const_iterator(&_ptr[_sz - 1]));
        }

        reverse_iterator rend() {
            return reverse_iterator(iterator(_ptr));
        }

        const_reverse_iterator rend() const {
            return reverse_iterator(const_iterator(_ptr));
        }

        size_t size() const {
            return _sz;
        }

        size_t max_size() const {
            return _alloc.max_size();
        }

        size_t capacity() const {
            return _cpcty;
        }

        // изменяет вектор до нужных размеров
        void resize (size_t n, T val = T()) {
            if (n < _sz) {
                for (; _sz > n; _sz--)
                    _alloc.destroy(&_ptr[_sz]);
            }
            else if (n > _cpcty) {
                reserve(n);

            }
            for(; _sz < n;++_sz)
                _ptr[_sz - 1] = T(val);
        }

        // возвращает true, если вектор пуст, иначе - false
        bool empty() const {
            return _sz == 0;
        }

        // + изменяет размер вектора до размера n, если текущий запас >= n, то ничего не делает, вроде норм написано
        void reserve (size_t n) {
            T* temp_ptr = NULL;
            T* for_del = NULL;
            size_t new_cpcty = _cpcty * 2;
            if (n >= _alloc.max_size()) {
                throw std::length_error("Index out of range");
            }
            if (n > _cpcty) {
                if (n > new_cpcty) {
                    new_cpcty = n;
                }
                temp_ptr = _alloc.allocate(new_cpcty);
                for (size_t cnt = 0; cnt < this->_sz; cnt++) {
                    _alloc.construct(&temp_ptr[cnt], _ptr[cnt]);
                }
                for_del = _ptr;
                _ptr = temp_ptr;
                for (size_t cnt = this->_sz; cnt > 0; --cnt) {
                    _alloc.destroy(&for_del[_sz]);
                }
                _alloc.deallocate(for_del, _cpcty);
                _cpcty = new_cpcty;
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
            return *_ptr;
        }

        const T& front() const{
            return *_ptr;
        }

        T& back(){
            return _ptr[_sz - 1];
        }

        const T& back() const{
            return _ptr[_sz - 1];
        }

        template <class InputIterator>
        void assign (typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {
            size_t n = last - first;
            if (n > _cpcty) {
                reserve(n);
            }
            clear();
            for (size_t tmp = 0; first != last; ++first, ++tmp) {
                _alloc.construct(&_ptr[tmp], *first);
            }
            _sz = n;
        }

        void assign (size_t n, const T& val) {
            if (n > _cpcty) {
                reserve(n);
            }
            clear();
            for (size_t tmp = 0; tmp < n; ++tmp) {
                _alloc.construct(&_ptr[tmp], val);
            }
            _sz = n;
        }

        // + вставляет элемент поданый в качестве аргумента в конец массива
        void push_back (const T& val) {
            if (_sz == _cpcty) {
                reserve(_cpcty + 1);
            }
            _alloc.construct(&_ptr[_sz++], val);
        }

        // + удаляет элемент с конца массива, уничтожая его
        void pop_back() {
            if (_sz > 0) {
                _alloc.destroy(&_ptr[--_sz]);
            }
        }

        iterator insert (iterator position, const T& val) {
            size_t pos = position - begin();
            if (_sz == _cpcty) {
                reserve(_cpcty + 1);
            }
            for (iterator end_el = end(); end_el != &_ptr[pos]; --end_el) {
                _alloc.construct(&(*end_el), *(end_el - 1));
//                _alloc.destroy(&*(end_el - 1));
            }
            _alloc.construct(&_ptr[pos], val);
            ++_sz;
            return &_ptr[pos];
        }

        void insert (iterator position, size_t n, const T& val) {
            size_t pos = position - begin();
            std::cout << pos << std::endl;
            if (_sz + n > _cpcty) {
                reserve(_sz + n);
            }
//            std::cout << "here" << std::endl;
//            std::cout << "else" << *(end() + n - 1) << std::endl;
            for (iterator end_el = end() + n - 1; end_el != &_ptr[pos]; --end_el) {
                _alloc.construct(&(*end_el), *(end_el - n));
//                _alloc.destroy(&*(end_el - n));
            }
//            std::cout << "here1 " << n << std::endl;
            iterator beg_el = begin() + pos;
            iterator end_el = beg_el + n;
            for (; beg_el != end_el; ++beg_el) {
//                std::cout << val << std::endl;
                _alloc.construct(&(*beg_el), val);
            }
//            std::cout << "here2" << std::endl;
            _sz += n;
        }

        template <class InputIterator>
        void insert (iterator position, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {
            size_t n = last - first;
            size_t pos = position - begin();
            std::cout << "abc" << std::endl;
            if (_sz + n > _cpcty) {
                reserve(_sz + n);
            }
//            std::cout << "abc:" << n << std::endl;
//            std::cout << "abc:" << pos << std::endl;
//            std::cout << "size:" << size() << std::endl;
//            std::cout << "cpcty:" << capacity() << std::endl;
            for (iterator end_el = end() - 1; end_el != &_ptr[pos]; --end_el) {
//                std::cout << "1" << std::endl;
                _alloc.construct(&(*end_el), *(end_el - n));
//                std::cout << "2" << std::endl;
//                _alloc.destroy(&*(end_el - n));
//                std::cout << "3" << std::endl;
            }
//            std::cout << "abc" << std::endl;
            iterator beg_el = begin() + pos;
            iterator end_el = beg_el + n;
            for (; beg_el != end_el; ++beg_el, ++first) {
                _alloc.construct(&(*beg_el), *first);
            }
            _sz += n;
        }

//        template <class InputIterator>
//        void insert (iterator position, InputIterator first, InputIterator last);

        iterator erase (iterator position) {
            iterator tmp(position);
//            _alloc.destroy(&(*position));
            for (iterator end_it = end(); position != end_it; ++position) {
                _alloc.construct(&(*position), *(position + 1));
            }
            _sz--;
            return tmp;
        }

        iterator erase (iterator first, iterator last) {
            iterator tmp(first);
            size_t n = last - first;
            iterator copy(first);
            for ( ; first != last; ++first) {
                _alloc.destroy(&(*first));
            }
            for ( ; first != end(); ++first, ++copy) {
                _alloc.construct(&(*copy), *(first));
            }
            _sz -= n;
            return tmp;
        }

        void swap (vector& x) {
            size_t          tmp_sz = _sz;
            size_t          tmp_cpcty = _cpcty;
            T*              tmp_ptr = _ptr;
            allocator_type  tmp_alloc = _alloc;

            if (this == &x)
                return ;

            _sz = x._sz;
            _cpcty = x._cpcty;
            _ptr = x._ptr;
            _alloc = x._alloc;

            x._sz = tmp_sz;
            x._cpcty = tmp_cpcty;
            x._ptr = tmp_ptr;
            x._alloc = tmp_alloc;
        }

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
        return (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template<typename T, class allocator_type >
    bool operator!= (const vector<T,allocator_type>& lhs, const vector<T,allocator_type>& rhs) {
        return !(lhs == rhs);
    }

    template<typename T, class allocator_type >
    bool operator<  (const vector<T,allocator_type>& lhs, const vector<T,allocator_type>& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    template<typename T, class allocator_type >
    bool operator<= (const vector<T,allocator_type>& lhs, const vector<T,allocator_type>& rhs) {
        return !ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());

    }
    template<typename T, class allocator_type >
    bool operator>  (const vector<T,allocator_type>& lhs, const vector<T,allocator_type>& rhs) {
        return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
    }
    template<typename T, class allocator_type >
    bool operator>= (const vector<T,allocator_type>& lhs, const vector<T,allocator_type>& rhs) {
        return !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <typename T, class allocator_type>
    void swap (vector<T,allocator_type>& x, vector<T,allocator_type>& y) {
        x.swap(y);
    }
};

#endif //VECTOR_HPP
