#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "iterator.hpp"
#include <iostream>

namespace ft {
    template<typename T, typename K>
    class BidIt : public iterator<bidirectional_iterator_tag, T> {
    private:
        typedef Node<T,K>* NodePointer;
        NodePointer *_node;

    public:
        BidIt() {
            _node = NULL;
        }

        BidIt(const BidIt &iter) {
            _node = iter._node;
        }

        BidIt(Node *node) {
            _node = node;
        }

        BidIt& operator=(const BidIt &iter) {
            if (this == &iter) {
                return *this;
            }
            _node = iter._node;
            return *this;
        }

        bool operator!= (const BidIt &right) const {
            return this->_node != right._node;
        }

        bool operator== (const BidIt &right) const {
            return this->_node == right._node;
        }

        T& operator*() {
            return *_node;
        }

        T* operator->() {
            return _node;
        }

        //++a;
        T* operator++() {
            if ()
            return ++_node;
        }

        //a++;
        T* operator++(int) {
            T *temp = _node;
            _node++;
            return temp;
        }

        T* operator--() {
            return --_node;
        }

        T* operator--(int) {
            T *temp = _node;
            _node--;
            return temp;
        }

        next()
        ~BidIt() {};
    };

    template<typename T>
    bool operator== (const BidIt<T> &left, const BidIt<T> &right) {
        return left.operator==(right);
    }

    template<typename T>
    bool operator!= (const BidIt<T> &left, const BidIt<T> &right) {
        return !(left.operator==(right));
    }

}


#endif //MAP_ITERATOR_HPP
