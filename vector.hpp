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
        typedef typename allocator_type::size_type                                      size_type;
        typedef typename allocator_type::difference_type                                difference_type;
        typedef typename allocator_type::pointer                                        pointer;
        typedef typename allocator_type::const_pointer                                  const_pointer;
        typedef typename allocator_type::reference                                      reference;
        typedef typename allocator_type::const_reference                                const_reference;
        typedef typename ft::RandIt<T, pointer, reference, difference_type>             iterator;
        typedef typename ft::RandIt<T, const_pointer, const_reference, difference_type> const_iterator;
        typedef typename ft::reverse_iterator<iterator>                                 reverse_iterator;
        typedef const typename ft::reverse_iterator<const_iterator>                     const_reverse_iterator;

    private:
        size_type                          _sz;
        size_type                          _cpcty;
        T*                                 _ptr;
        allocator_type                     _alloc;

    public:
        vector (const allocator_type& alloc = allocator_type()) {
            _sz = 0;
            _cpcty = 0;
            _ptr = NULL;
            _alloc = alloc;
        }

        vector (size_type n, const T& val = T(), const allocator_type& alloc = allocator_type()) {
            _sz = n;
            _cpcty = n;
            _alloc = alloc;
            _ptr = _alloc.allocate(n);
            for (size_type cnt = 0; cnt < _sz; cnt++) {
                _alloc.construct(&_ptr[cnt], val);
            }
        }

        template <class InputIterator>
        vector (typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator_type& alloc = allocator_type()) {
            size_type n = last - first;
            _sz = n;
            _cpcty = n;
            _alloc = alloc;
            _ptr = _alloc.allocate(n);
            for (size_type cnt = 0; cnt < _sz; cnt++) {
                _alloc.construct(&_ptr[cnt], first[cnt]);
            }
        }

        vector (const vector& x) {
            _alloc = x.get_allocator();
            _sz = x.size();
            _cpcty = x.capacity();
            _ptr = _alloc.allocate(_cpcty);
            for (size_type cnt = 0; cnt < _sz; cnt++) {
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

        size_type size() const {
            return _sz;
        }

        size_type max_size() const {
            return _alloc.max_size();
        }

        size_type capacity() const {
            return _cpcty;
        }

        // изменяет вектор до нужных размеров
        void resize (size_type n, T val = T()) {
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
        
        size_type get_new_cpcty(size_type n, size_type cpcty) {
            if (n > cpcty) {
                size_type new_cpcty = cpcty * 2;
                if (n > new_cpcty) {
                    new_cpcty = n;
                }
                return new_cpcty;
            }
            return cpcty;
        }

        // + изменяет размер вектора до размера n, если текущий запас >= n, то ничего не делает, вроде норм написано
        T* get_reserved_memory (size_type new_cpcty) {
            T* temp_ptr = NULL;
            if (new_cpcty >= _alloc.max_size()) {
                throw std::length_error("Index out of range");
            }
            temp_ptr = _alloc.allocate(new_cpcty);
            return temp_ptr;
        }

        void reserve (size_type n) {
            T* temp_ptr = NULL;
            T* for_del = NULL;

            if (n > _cpcty) {
                size_type new_cpcty = get_new_cpcty(n, _cpcty);
                temp_ptr = get_reserved_memory(new_cpcty);
                for (size_type cnt = 0; cnt < this->_sz; cnt++) {
                    _alloc.construct(&temp_ptr[cnt], _ptr[cnt]);
                }
                for_del = _ptr;
                _ptr = temp_ptr;
                for (size_type cnt = this->_sz; cnt > 0; --cnt) {
                    _alloc.destroy(&for_del[_sz]);
                }
                _alloc.deallocate(for_del, _cpcty);
                _cpcty = new_cpcty;
            }
        }

//        void reserve (size_type n) {
//            T* temp_ptr = NULL;
//            T* for_del = NULL;
//            size_type new_cpcty = _cpcty * 2;
//            if (n >= _alloc.max_size()) {
//                throw std::length_error("Index out of range");
//            }
//            if (n > _cpcty) {
//                if (n > new_cpcty) {
//                    new_cpcty = n;
//                }
//                temp_ptr = _alloc.allocate(new_cpcty);
//                for (size_type cnt = 0; cnt < this->_sz; cnt++) {
//                    _alloc.construct(&temp_ptr[cnt], _ptr[cnt]);
//                }
//                for_del = _ptr;
//                _ptr = temp_ptr;
//                for (size_type cnt = this->_sz; cnt > 0; --cnt) {
//                    _alloc.destroy(&for_del[_sz]);
//                }
//                _alloc.deallocate(for_del, _cpcty);
//                _cpcty = new_cpcty;
//            }
//        }

        const T& operator[] (size_type n) const{
            return _ptr[n];
        }

        T& operator[] (size_type n) {
            return _ptr[n];
        }

        T& at (size_type n) {
            if (n >= _sz) {
                throw std::out_of_range("Index out of range");
            }
            return _ptr[n];
        }

        const T& at (size_type n) const {
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
            size_type n = last - first;
            if (n > _cpcty) {
                reserve(n);
            }
            clear();
            for (size_type tmp = 0; first != last; ++first, ++tmp) {
                _alloc.construct(&_ptr[tmp], *first);
            }
            _sz = n;
        }

        void assign (size_type n, const T& val) {
            if (n > _cpcty) {
                reserve(n);
            }
            clear();
            for (size_type tmp = 0; tmp < n; ++tmp) {
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

        void init(iterator where, iterator begin, iterator end) {
            for (;begin != end; ++begin, ++where) {
                _alloc.construct(&*where, *begin);
            }
        }

        void destroy(iterator begin, iterator end) {
            difference_type size = end - begin;
            T *tmp = &*begin;
            for (;begin != end; ++begin) {
                _alloc.destroy(&*begin);
            }
            _alloc.deallocate(tmp, size);
        }

        void copy_back(iterator from, iterator to, size_type n) {
            iterator from_cp(from);
            iterator to_cp(to);

            for (int i = 0; i < n; ++i, --from, --to) {
                _alloc.construct(&(*to), *(from));
            }
        }

        void copy_construct(iterator from, iterator to, size_type n) {
            iterator from_cp(from);
            iterator to_cp(to);

            for (int i = 0; i < n; ++i, ++from, ++to) {
                _alloc.construct(&(*to), *(from));
            }
        }

        iterator insert (iterator position, const T& val) {
            size_type pos = position - begin();
            insert(position, 1, val);
            return iterator(_ptr + pos);
        }
        
        void insert (iterator position, size_type n, const T& val) {
            difference_type pos = position - begin();
            difference_type ost = end() - position;
            if (_sz + n > _cpcty) {
                size_type new_cpcty = get_new_cpcty(_sz + n, _cpcty);
                T *new_ptr = get_reserved_memory(new_cpcty);
                if (_sz > 0) {
                    if (pos < _sz) {
                        copy_construct(this->begin(), new_ptr, pos);
                        copy_construct(this->begin() + pos, new_ptr + n + pos, ost);
                    } else {
                        copy_construct(this->begin(), new_ptr, _sz);
                    }
                }
                iterator beg_el = iterator(new_ptr) + pos;
                iterator end_el = beg_el + n;
                for (; beg_el != end_el; ++beg_el) {
                    _alloc.construct(&(*beg_el), val);
                }
                size_type new_size = _sz + n;
                clear();
                _alloc.deallocate(_ptr, _cpcty);
                _sz = new_size;
                _cpcty = new_cpcty;
                _ptr = new_ptr;
            }
            else {
                if (pos < _sz) {
                    iterator end_el = iterator(&_ptr[pos + n + ost - 1]);
                    iterator from = end_el - n;
                    copy_back(from, end_el, ost);
                }
                iterator beg_el = begin() + pos;
                iterator end_el = beg_el + n;
                for (; beg_el != end_el; ++beg_el) {
                    _alloc.construct(&(*beg_el), val);
                }
                _sz += n;
            }
        }

        template <class InputIterator>
        void insert (iterator position, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {
            difference_type n = last - first;
            difference_type pos = position - begin();
            difference_type ost = end() - position;
            if (_sz + n > _cpcty) {
                size_type new_cpcty = get_new_cpcty(_sz + n, _cpcty);
                T *new_ptr = get_reserved_memory(new_cpcty);
                if (pos < _sz) {
                    copy_construct(this->begin(), new_ptr, pos);
                    copy_construct(this->begin() + pos, new_ptr + n + pos, ost);
                }
                else {
                    copy_construct(this->begin(), new_ptr,_sz);
                }
                iterator beg_el = new_ptr + pos;
                iterator end_el = beg_el + n;
                for (; beg_el != end_el; ++beg_el, ++first) {
                    _alloc.construct(&(*beg_el), *first);
                }
                size_type new_size = _sz + n;
                clear();
                _alloc.deallocate(_ptr, _cpcty);
                _sz = new_size;
                _cpcty = new_cpcty;
                _ptr = new_ptr;
            }
            else {
                if (pos < _sz) {
                    iterator end_el = iterator(&_ptr[pos + n + ost - 1]);
                    iterator from = end_el - n;
                    copy_back(from, end_el, ost);
                }
                iterator beg_el = begin() + pos;
                iterator end_el = beg_el + n;
                for (; beg_el != end_el; ++beg_el, ++first) {
                    _alloc.construct(&(*beg_el), *first);
                }
                _sz += n;
            }
        }

        iterator erase (iterator position) {
            difference_type pos = position - begin();
            for (size_type i = 0; i < _sz; ++i) {
                _alloc.construct(_ptr + pos + i, *(_ptr + pos + i + 1));
            }
            _sz--;
            return _ptr + pos;
        }

        iterator erase (iterator first, iterator last) {
            iterator tmp(first);
            difference_type n = last - first;
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
            size_type           tmp_sz = _sz;
            size_type           tmp_cpcty = _cpcty;
            T*                  tmp_ptr = _ptr;
            allocator_type      tmp_alloc = _alloc;

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
