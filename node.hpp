#ifndef NODE_HPP
#define NODE_HPP


#include "utils.hpp"

template <class K, class V>
struct node {
    typedef ft::pair<const K, V>    value_type;
    bool                            isred;
    bool                            isnil;
    node                            *left;
    node                            *right;
    node                            *parent;
    value_type                      *data;

    node() : left(NULL), right(NULL), parent(NULL), isred(true), isnil(true) {}

    node(K key, V value) : left(NULL), right(NULL), parent(NULL), isred(true), isnil(false) {
        data = ft::make_pair(key, value);
    }
};


#endif //NODE_HPP
