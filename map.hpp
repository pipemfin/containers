#ifndef MAP_HPP
#define MAP_HPP

#include <stddef.h>
#include <memory>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include "node.hpp"
#include "iterator.hpp"
#include "map_iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"


namespace ft {

    template<class Key, class Val, class Compare = std::less<Key>, class allocator_type = std::allocator<pair<const Key, Val> > >
    class map{
    public:
        typedef Key key_type;
        typedef Val mapped_type;
        typedef typename allocator_type::size_type                                              size_type;
        typedef typename allocator_type::difference_type                                        difference_type;
        typedef typename allocator_type::pointer                                                pointer;
        typedef typename allocator_type::const_pointer                                          const_pointer;
        typedef typename allocator_type::reference                                              reference;
        typedef typename allocator_type::const_reference                                        const_reference;
        typedef typename ft::BidIt<Key, Val, pointer, reference, difference_type>               iterator;
        typedef typename ft::BidIt<Key, Val, const_pointer, const_reference, difference_type>   const_iterator;
        typedef typename ft::reverse_iterator<iterator>                                         reverse_iterator;
        typedef const typename ft::reverse_iterator<const_iterator>                             const_reverse_iterator;
        typedef pair<const key_type, mapped_type>                                               value_type;
        typedef node<Key, Val>                                                                  node_type;

    public:
        size_type                          _sz;
        allocator_type                     _alloc;
        node_type                          *_root;
        Compare                            _key_compare;

    public:
        explicit map(const Compare& comp = Compare(), const allocator_type& alloc = allocator_type()) {
            _sz = 0;
            _root = new node_type();
            _alloc = alloc;
        }

        template <class InputIterator>
        map (InputIterator first, InputIterator last, const Compare& comp = Compare(), const allocator_type& alloc = allocator_type());

        map (const map& x);

        iterator begin() {
            iterator tmp = iterator(_root);
            if (!_sz)
                return tmp;
            return tmp.minimum(_root->left);
        }

        const_iterator begin() const {
            const_iterator tmp = const_iterator(_root);
            if (!_sz)
                return tmp;
            return tmp.minimum(_root->left);
        }

        iterator end() {
            return iterator(_root);
        }

        const_iterator end() const {
            return const_iterator(_root);
        }

        reverse_iterator rbegin() {
            iterator tmp(_root);
            if (!_sz)
                return reverse_iterator(tmp);
            return reverse_iterator(tmp.minimum(_root->left));
        }

        const_reverse_iterator rbegin() const {
            const_iterator tmp(_root);
            if (!_sz)
                return reverse_iterator(tmp);
            return reverse_iterator(tmp.minimum(_root->left));
        }

        reverse_iterator rend() {
            iterator tmp(_root);
            if (!_sz)
                return reverse_iterator(tmp);
            return reverse_iterator(tmp.maximum(_root->left));
        }

        const_reverse_iterator rend() const {
            const_iterator tmp(_root);
            if (!_sz)
                return reverse_iterator(tmp);
            return reverse_iterator(tmp.maximum(_root->left));
        }

        pair<iterator,bool> insert (const value_type &val) {
            if (_sz == 0) {
                node_type *new_node = new node_type(val, _root);
                iterator for_return(new_node);
                _root->left = new_node;
                new_node->parent = _root;
                ++_sz;
                return ft::make_pair(for_return, true);
            }
            node_type *start = _root->left;
            node_type *prev = NULL;
//            std::cout << "start searching" << std::endl;
            while (!start->isnil) {
//                std::cout << "first iter" << std::endl;
                prev = start;
                if (_key_compare(start->data->first, val.first)) {
                    start = start->right;
                }
                else if (_key_compare(val.first, start->data->first)) {
                    start = start->left;
                }
                else {
                    return ft::make_pair(iterator(start), false);
                }
            }
//            std::cout << "creating node" << std::endl;
            node_type *tmp = new node_type(val, _root);
//            std::cout << "before compare" << std::endl;
            if (_key_compare(prev->data->first, val.first))
                prev->right = tmp;
            else
                prev->left = tmp;
            tmp->parent = prev;
            ++_sz;
            iterator for_return(tmp);
//            std::cout << "before exit" << std::endl;
            return ft::make_pair(for_return, true);
        }

        iterator insert (iterator position, const value_type &val) {
            return this->insert(val).first;
        }

        template <class InputIterator>
        void insert (InputIterator first, InputIterator last) {
            for (;first != last; ++first) {
                insert(*first);
            }
        }

        void clear() {
            for (iterator begin = begin(); begin != end(); begin++) {
                _alloc.destroy();
                _alloc.deallocate();
            }
        }

        void swap (map& x) {
            size_type           _sz_tmp = x._sz;
            allocator_type      _alloc_tmp = x._alloc;
            node_type           *_root_tmp = x._root;
            Compare             _key_compare_tmp = x._key_compare;

            x._sz = this->_sz;
            x._alloc = this->_alloc;
            x._root = this->_root;
            x._key_compare = this->_key_compare;

            this->_sz = _sz_tmp;
            this->_alloc = _alloc_tmp;
            this->_root = _root_tmp;
            this->_key_compare = _key_compare_tmp;
        }

        size_type size() const {
            return _sz;
        }

        bool empty() const {
            return _sz == 0;
        }

        size_t max_size() const {
            return _alloc.max_size();
        }

        mapped_type& operator[] (const key_type& k);

        allocator_type get_allocator() const {
            return _alloc;
        }

        iterator find (const Key& k) {
            if (_sz == 0)
                return this->end();
            node_type *start = _root->left;
            while (!start->isnil) {
                if (_key_compare(start->data->first, k)) {
                    start = start->right;
                }
                else if (_key_compare(k, start->data->first)) {
                    start = start->left;
                }
                else {
                    return iterator(start);
                }
            }
            return this->end();
        }

        const_iterator find (const Key& k) const {
            if (_sz == 0)
                return this->cend();
            node_type *start = _root->left;
            while (start) {
                if (_key_compare(start->data->first, k)) {
                    start = start->right;
                }
                else if (_key_compare(k, start->data->first)) {
                    start = start->left;
                }
                else {
                    return const_iterator(start);
                }
            }
            return this->cend();
        }

        size_type count (const Key& k) const {
            if (_sz == 0)
                return 0;
            if (find(k) != this->end())
                return 1;
            return 0;
        }

        ~map() {}

    };

    template <class Key, class T, class Compare, class Alloc>
    void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) {
        x.swap(y);
    }
};

#endif //VECTOR_HPP
