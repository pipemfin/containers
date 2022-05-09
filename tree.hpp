//
// Created by Johnna Jerrod on 5/9/22.
//

#ifndef TREE_HPP
#define TREE_HPP

#ifndef MAP_HPP
#define MAP_HPP

#include <stddef.h>
#include <memory>
#include <cmath>
#include <iostream>
#include <stdexcept>


namespace ft {
    template <class Key, class T, class Compare = less<Key>, class Alloc = allocator<pair<const Key,T> >
    class map{
    public:
        size_type                          _sz;
        allocator_type                     _alloc;
        node                               _root;
        Compare                            _key_compare;

    public:
        typedef pair<const Key, T>         value_type;

        explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
            _sz = 0;
            _root = new Node;
            _alloc = alloc;
        }

        template <class InputIterator>
        map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

        map (const map& x);

        size_type size() const {
            return _sz;
        }

        bool empty() const {
            return _sz == 0;
        }

        size_t max_size() const {
            return _alloc.max_size();
        }

        Alloc get_allocator() const {
            return _alloc;
        }

        ~map();
    };
};

#endif //VECTOR_HPP


#endif //CONTAINERS_TREE_HPP
