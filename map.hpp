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
        size_t                             _sz;
        T*                                 _ptr;
        allocator_type                     _alloc;

    public:
        typedef typename allocator_type::size_type                  size_type;
        typedef typename allocator_type::difference_type            difference_type;
        typedef typename ft::RandIt<T>                              iterator;
        typedef typename ft::RandIt<T>                              const_iterator;
        typedef typename ft::reverse_iterator<iterator>             reverse_iterator;
        typedef const typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

        explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

        template <class InputIterator>
        map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

        map (const map& x);

        size_type size() const {

        }

        bool empty() const {
            return _sz == 0;
        }

        size_t max_size() const {
            return _alloc.max_size();
        }

        ~map();

    };
};

#endif //VECTOR_HPP
