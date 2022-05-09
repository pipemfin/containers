#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "iterator.hpp"
#include "node.hpp"
#include <iostream>

namespace ft {
    template<typename Key, typename T>
    class BidIt : public iterator<bidirectional_iterator_tag, node<T,K> > {
    private:
        typedef node<T,K> Node;
        Node *_node;

    public:
        typedef BidIt<typename Key, typename T>  Iter;
        typedef typename Iter::iterator_category iterator_category;
        typedef typename Iter::value_type        value_type;
        typedef typename Iter::difference_type   difference_type;
        typedef typename Iter::pointer           pointer;
        typedef typename Iter::reference         reference;

        BidIt() {
            _node = NULL;
        }

        BidIt(const BidIt &iter) {
            _node = iter._node;
        }

        BidIt(Node *node) {
            _node = node;
        }

        reference operator=(const BidIt &iter) {
            if (this == &iter) {
                return *this;
            }
            _node = iter._node;
            return *this;
        }

        bool operator!= (const BidIt &right) const {
            return _node != right._node;
        }

        bool operator== (const BidIt &right) const {
            return _node == right._node;
        }

        reference operator*() {
            return *_node;
        }

        pointer operator->() {
            return _node;
        }

        //a++;
        pointer operator++() {
            Next();
            return _node;
        }

        pointer operator++(int) {
            pointer temp = _node;
            _node++;
            return temp;
        }

        pointer operator--() {
            Prev();
            return _node;
        }

        pointer operator--(int) {
            pointer temp = _node;
            _node--;
            return temp;
        }

        pointer maximum(pointer node) {
            for ( ; node->right->type != nil; node = node->right)
                return node
        }

        pointer minimum(pointer node) {
            for ( ; node->left->type != nil; node = node->left)
                return node
        }

        void Prev() {
            if (_node == NULL)
                ;
            else if (!left->isnil)
                _node = maximum(left);
            else {
                pointer tmp = _node->parent;
                while (!tmp->isnil && _node == tmp.left) {
                    _node = tmp;
                    tmp = tmp->parent;
                }
                _node = tmp;
            }
        }

        void Next() {
            if (_node == NULL)
                ;
            else if (!right->isnil)
                _node = minimum(right);
            else {
                pointer tmp = _node->parent;
                while (!tmp->isnil && _node == tmp.right) {
                    _node = tmp;
                    tmp = tmp->parent;
                }
                _node = tmp;
            }
        }

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
