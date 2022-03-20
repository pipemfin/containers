//
// Created by Johnna Jerrod on 3/20/22.
//

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include "iterator.hpp"

template<class iterator>
struct iterator_traits {
    typedef typename ft::iterator::iterator_category iterator_category;
    typedef typename ft::iterator::value_type value_type;
    typedef typename ft::iterator::difference_type difference_type;
    typedef typename ft::iterator::pointer pointer;
    typedef typename ft::iterator::reference reference;
};

template<class T>
struct iterator_traits<T *> {
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T *pointer;
    typedef T &reference;
};

template<class T>
struct iterator_traits<const T *> {
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef const T *pointer;
    typedef const T &reference ;
};

#endif //ITERATOR_TRAITS_HPP
