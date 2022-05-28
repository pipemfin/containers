#ifndef NODE_HPP
#define NODE_HPP


#include "utils.hpp"

namespace ft {
    template<class K, class V, class Alloc = std::allocator<pair<const K, V> > >
    struct node {
        typedef pair<const K, V> value_type;
        bool isred;
        bool isnil;
        node *left;
        node *right;
        node *parent;
        node **_root;
        value_type *data;
        Alloc alloc;

        node() : left(NULL), right(NULL), parent(NULL), isred(false), isnil(true), data(NULL), alloc(Alloc()) {}

        node(K &key, V &value, node *nil = NULL, bool red = true, bool cond = false) : left(nil), right(nil), parent(nil), isred(red), isnil(cond), data(NULL), alloc(Alloc()) {
            data = alloc.allocate(1);
            alloc.construct(data, value_type(key, value));
        }

        node(ft::pair<K, V> init_data, node *nil = NULL, bool red = true, bool cond = false) : left(nil), right(nil), parent(nil), isred(red), isnil(cond), data(NULL), alloc(Alloc()) {
            data = alloc.allocate(1);
            alloc.construct(data, value_type(init_data.first, init_data.second));
        }

        ~node() {
            if (data) {
                alloc.destroy(data);
                alloc.deallocate(data, 1);
            }
        }
    };
}

#endif //NODE_HPP
