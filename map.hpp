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
        typedef pair<const Key, Val>                                                            value_type;
        typedef node<const Key, Val>                                                            node_type;

    private:
        size_type                          _sz;
        allocator_type                     _alloc;
        node<const Key, Val>               *_root;
        Compare                            _key_compare;

    public:
        explicit map(const Compare& comp = Compare(), const allocator_type& alloc = allocator_type()) {
            _sz = 0;
            _root = new node<const Key, Val>();
            _alloc = alloc;
        }

        template <class InputIterator>
        map (InputIterator first, InputIterator last, const Compare& comp = Compare(), const allocator_type& alloc = allocator_type());

        map (const map& x);

        iterator begin() {
            iterator tmp(_root);
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
            iterator tmp = iterator(_root);
            if (!_sz)
                return tmp;
            return tmp.maximum(_root->left);
        }

        const_iterator end() const {
            const_iterator tmp = const_iterator(_root);
            if (!_sz)
                return tmp;
            return tmp.maximum(_root->left);
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

        pair<iterator,bool> insert (const value_type& val) {
            node_type *start = _root->left;
            node_type *prev = NULL;
            while (start){
                prev = start;
                if (_key_compare(start->data->first, val.first)) {
                    start = start->left;
                }
                else if (_key_compare(val.first, start->data->first)) {
                    start = start->right;
                }
                else {
                    return make_pair(iterator(start), false);
                }
            }
            node_type tmp = new node_type(val);
            if (prev != NULL) {
                if (_key_compare(start->data->first, val.first))
                    prev->left = tmp;
                else
                    prev->right = tmp;
            }
            else
                _root->left = tmp;
            ++_sz;
            return make_pair(tmp, true);
        }

//        iterator insert (iterator position, const value_type& val);
//
//        template <class InputIterator>
//        void insert (InputIterator first, InputIterator last);

        size_type size() const {
            return _sz;
        }

        bool empty() const {
            return _sz == 0;
        }

        size_t max_size() const {
            return _alloc.max_size();
        }

        allocator_type get_allocator() const {
            return _alloc;
        }



        ~map() {}

    };
};

#endif //VECTOR_HPP
