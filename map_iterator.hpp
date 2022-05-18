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
        typedef node<K, V>                                                          node;
        typedef BidIt<bidirectional_iterator_tag, node, Pt, Rt, Dtype>              iterator;
        typedef pair<const K, V>                                                    value_type;
//        typedef typename iterator::iterator_category                                iterator_category;
//        typedef typename Iterator::value_type                                       value_type;
//        typedef typename Iterator::difference_type                                  difference_type;
//        typedef typename Iterator::pointer                                          pointer;
//        typedef typename Iterator::reference                                        reference;

    private:
        node    *_node;

    public:
        BidIt() : _node(NULL) {}

        BidIt(const BidIt &iter) : _node(iter._node) {}

        BidIt(node *node) : _node(node) {}

        node& operator=(const BidIt &iter) {
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

        value_type& operator*() {
            return *_node->data;
        }

        node *get_node() {
            return _node;
        }

        value_type* operator->() {
            return _node->data;
        }

        //a++;
        node* operator++() {
            std::cout << "++operator" << std::endl;
            Next();
            return _node;
        }

        node* operator++(int) {
            node* temp = _node;
            _node++;
            return temp;
        }

        node* operator--() {
            std::cout << "--operator" << std::endl;
            Prev();
            return _node;
        }

        node* operator--(int) {
            node* temp = _node;
            std::cout << "operator--" << std::endl;
            _node--;
            return temp;
        }

        node* maximum(node* node) {
            for ( ; !node->right->isnil; node = node->right)
                ;
            return node;
        }

        node* minimum(node* node) {
            for ( ; !node->left->isnil; node = node->left)
                ;
            return node;
        }

        void Prev() {
            if (_node == NULL) {
                std::cout << "lol" << std::endl;
            }
            else if (!_node->left->isnil) {
                std::cout << "first path" << std::endl;
                _node = maximum(_node->left);
            }
            else {
                std::cout << "second path" << std::endl;
                std::cout << "parent node data=" << _node->parent << std::endl;
                node* tmp = _node->parent;
                while (!tmp->isnil && _node == tmp->left) {
                    _node = tmp;
                    tmp = tmp->parent;
                }
                _node = tmp;
            }
        }

        void Next() {
            if (_node == NULL || _node->isnil) {
                std::cout << "lol" << std::endl;
            }
            else if (!_node->right->isnil) {
                std::cout << "first path" << std::endl;
                _node = minimum(_node->right);
            }
            else {
                std::cout << "second path" << std::endl;
                std::cout << "parent node data=" << _node->parent << std::endl;
                node* tmp = _node->parent;
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
