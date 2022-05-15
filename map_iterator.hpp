#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "iterator.hpp"
#include "utils.hpp"
#include "node.hpp"
#include <iostream>

namespace ft {
    template<typename K, typename V, typename Pt, typename Rt, typename Dtype>
class BidIt : public iterator<bidirectional_iterator_tag, node<K, V>, Dtype, Pt, Rt> {
    public:
        typedef node<K, V>                                                          Node;
        typedef BidIt<bidirectional_iterator_tag, Node, Pt, Rt, Dtype>              iterator;
//        typedef typename iterator::iterator_category                                iterator_category;
//        typedef typename Iterator::value_type                                       value_type;
//        typedef typename Iterator::difference_type                                  difference_type;
//        typedef typename Iterator::pointer                                          pointer;
//        typedef typename Iterator::reference                                        reference;

    private:
        Node    *_node;

    public:
        BidIt() : _node(NULL) {}

        BidIt(const BidIt &iter) : _node(iter._node) {}

        BidIt(Node *node) : _node(node) {}

        Node& operator=(const BidIt &iter) {
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

        Node& operator*() {
            return *_node;
        }

        Node* operator->() {
            return _node;
        }

        //a++;
        Node* operator++() {
            Next();
            return _node;
        }

        Node* operator++(int) {
            Node* temp = _node;
            _node++;
            return temp;
        }

        Node* operator--() {
            Prev();
            return _node;
        }

        Node* operator--(int) {
            Node* temp = _node;
            _node--;
            return temp;
        }

        Node* maximum(Node* node) {
            for ( ; !node->right->isnil; node = node->right)
                ;
            return node;
        }

        Node* minimum(Node* node) {
            std::cout << "1" << std::endl;
            for ( ; !node->left->isnil; node = node->left)
                std::cout << "2" << std::endl;;
            return node;
        }

        void Prev() {
            if (_node == NULL)
                ;
            else if (!_node->left->isnil)
                _node = maximum(_node->left);
            else {
                Node* tmp = _node->parent;
                while (!tmp->isnil && _node == tmp->left) {
                    _node = tmp;
                    tmp = tmp->parent;
                }
                _node = tmp;
            }
        }

        void Next() {
            if (_node == NULL)
                ;
            else if (!_node->right->isnil)
                _node = minimum(_node->right);
            else {
                Node* tmp = _node->parent;
                while (!tmp->isnil && _node == tmp->right) {
                    _node = tmp;
                    tmp = tmp->parent;
                }
                _node = tmp;
            }
        }

        ~BidIt() {};
    };

    template<typename K, typename V, typename Pt, typename Rt, typename Dtype>
    bool operator== (iterator<bidirectional_iterator_tag, node<const K, V>, Pt, Rt, Dtype> &left, iterator<bidirectional_iterator_tag, node<const K, V>, Pt, Rt, Dtype> &right) {
        return left.operator==(right);
    }

    template<typename K, typename V, typename Pt, typename Rt, typename Dtype>
    bool operator!= (iterator<bidirectional_iterator_tag, node<const K, V>, Pt, Rt, Dtype> &left, iterator<bidirectional_iterator_tag, node<const K, V>, Pt, Rt, Dtype> &right) {
        return !(left.operator==(right));
    }

}


#endif //MAP_ITERATOR_HPP
