#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator.hpp"
#include <iostream>

namespace ft {
    template<typename T, typename Pt, typename Rt, typename Dtype>
    class RandIt : public iterator<random_access_iterator_tag, T, Dtype, Pt, Rt> {
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

        bool operator!= (const RandIt &right) const {
            return this->_ptr != right._ptr;
        }

        bool operator== (const RandIt &right) const {
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
            return temp;
        }

        RandIt operator+(int obj) {
            return _ptr + obj;
        }

        RandIt operator-(int obj) {
            return _ptr - obj;
        }

        int operator-(RandIt iter) {
            return _ptr - iter._ptr;
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
            int m = obj;
            if (m >= 0) {
                while (m--) ++(*this);
            }
            else {
                while (m++) --(*this);
            }
            return *this;
        }

//        RandIt& operator+=(int obj) {
//            _ptr += obj;
//            return *this;
//        }

        RandIt& operator-=(int obj) {
            _ptr -= obj;
            return *this;
        }

        T& operator[] (size_t n) {
            return _ptr[n];
        }

        ~RandIt() {};
    };

    template<typename T, typename Pt, typename Rt, typename Dtype>
    bool operator== (const RandIt<T, Pt, Rt, Dtype> &left, const RandIt<T, Pt, Rt, Dtype> &right) {
        return left.operator==(right);
    }

    template<typename T, typename Pt, typename Rt, typename Dtype>
    bool operator!= (const RandIt<T, Pt, Rt, Dtype> &left, const RandIt<T, Pt, Rt, Dtype> &right) {
        return !(left.operator==(right));
    }

}

#endif //CONTAINERS_VECTOR_ITERATOR_HPP
