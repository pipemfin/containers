#ifndef MAP_HPP
#define MAP_HPP

#include <stddef.h>
#include <memory>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include "node.hpp"
#include "iterator.hpp"


namespace ft {

    template <class Key, class Val, class Compare = std::less<Key>, class allocator_type = std::allocator<pair<const Key, Val> >
    class map {
    public:
        typedef typename allocator_type::size_type                                      size_type;
        typedef typename allocator_type::difference_type                                difference_type;
        typedef typename allocator_type::pointer                                        pointer;
        typedef typename allocator_type::const_pointer                                  const_pointer;
        typedef typename allocator_type::reference                                      reference;
        typedef typename allocator_type::const_reference                                const_reference;
        typedef typename ft::RandIt<T, pointer, reference, difference_type>             iterator;
        typedef typename ft::RandIt<T, const_pointer, const_reference, difference_type> const_iterator;
        typedef typename ft::reverse_iterator<iterator>                                 reverse_iterator;
        typedef const typename ft::reverse_iterator<const_iterator>                     const_reverse_iterator;
        typedef pair<const Key, Val>                                                    value_type;

    private:
        size_type                          _sz;
        allocator_type                     _alloc;
        node                               _root;
        Compare                            _key_compare;

    public:


        explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
            _sz = 0;
            _root = new Node();
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
}

#endif //VECTOR_HPP
