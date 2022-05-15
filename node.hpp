#ifndef NODE_HPP
#define NODE_HPP


#include "utils.hpp"

namespace ft {
    template<class K, class V>
    struct node {
        typedef pair<const K, V> value_type;
        bool isred;
        bool isnil;
        node *left;
        node *right;
        node *parent;
        value_type *data;

        node() : left(NULL), right(NULL), parent(NULL), isred(false), isnil(true), data(NULL) {}

        node(K &key, V &value, node *nil = NULL, bool red = true, bool cond = false) : left(nil), right(nil), parent(nil), isred(red), isnil(cond) {
            data = new value_type(key, value);
        }

        node(ft::pair<K, V> init_data, node *nil = NULL, bool red = true, bool cond = false) : left(nil), right(nil), parent(nil), isred(red), isnil(cond) {
            data = new value_type(init_data.first, init_data.second);
        }

        ~node() {
            if (data)
                delete data;
        }
    };
}

#endif //NODE_HPP
