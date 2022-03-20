#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {
    template<typename T>
    class RandIt : ft::iterator<ft::random_access_iterator_tag, T> {
    private:
        T *_ptr;

    public:
        RandIt() {
            _ptr = NULL;
        }

        RandIt(const RandIt &iter) {
            _ptr = iter._ptr;
        }

        RandIt(T *ptr) {
            _ptr = ptr;
        }

        RandIt& operator=(const RandIt &iter) {
            if (this == &iter) {
                return *this;
            }
            _ptr = iter._ptr;
            return *this;
        }

        bool operator!=(RandIt &right) {
            return this->_ptr != right._ptr;
        }

        bool operator==(RandIt &right) {
            return this->_ptr == right._ptr;
        }

        T& operator*() {
            return *_ptr;
        }

        T* operator->() {
            return _ptr;
        }

        //++a;
        T* operator++() {
            return ++_ptr;
        }

        //a++;
        T* operator++(int) {
            T *temp = _ptr;
            _ptr++;
            return temp;
        }

        T* operator--() {
            return --_ptr;
        }

        T* operator--(int) {
            T *temp = _ptr;
            _ptr--;
            return (temp);
        }

        RandIt& operator+(int obj) {
            _ptr += obj;
            return *this;
        }

        RandIt& operator-(int obj) {
            _ptr -= obj;
            return *this;
        }

        bool operator>(RandIt iter){
            return _ptr > iter._ptr;
        }

        bool operator<(RandIt iter){
            return _ptr < iter._ptr;
        }

        bool operator>=(RandIt iter){
            return _ptr >= iter._ptr;
        }

        bool operator<=(RandIt iter){
            return _ptr <= iter._ptr;
        }

        RandIt& operator+=(int obj) {
            _ptr += obj;
            return *this;
        }

        RandIt& operator-=(int obj) {
            _ptr -= obj;
            return *this;
        }

        T& operator[] (size_t n) {
            return _ptr[n];
        }

        ~RandIt() {};
    };
}

#endif //CONTAINERS_VECTOR_ITERATOR_HPP
