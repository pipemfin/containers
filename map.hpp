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
        typedef Compare key_compare;
        typedef typename allocator_type::size_type                                                              size_type;
        typedef typename allocator_type::difference_type                                                        difference_type;
        typedef typename allocator_type::pointer                                                                pointer;
        typedef typename allocator_type::const_pointer                                                          const_pointer;
        typedef typename allocator_type::reference                                                              reference;
        typedef typename allocator_type::const_reference                                                        const_reference;
        typedef typename ft::BidIt<Key, Val, pointer, reference, difference_type,allocator_type>                iterator;
        typedef typename ft::BidIt<Key, Val, const_pointer, const_reference, difference_type,allocator_type>    const_iterator;
        typedef typename ft::reverse_iterator<iterator>                                                         reverse_iterator;
        typedef const typename ft::reverse_iterator<const_iterator>                                             const_reverse_iterator;
        typedef pair<const key_type, mapped_type>                                                               value_type;
        typedef node<Key, Val, allocator_type>                                                                  node_type;

    public:
        size_type                          _sz;
        allocator_type                     _alloc;
        node_type                          *_root;
        node_type                          *_nil;
        Compare                            _key_compare;

        explicit map(const Compare& comp = Compare(), const allocator_type& alloc = allocator_type()) : _nil(NULL) {
//            std::cout << "default constr" << std::endl;
            _sz = 0;
            _root = NULL;
            _nil = new node_type();
            _nil->_root = &_root;
            _alloc = alloc;
            _key_compare = comp;
        }

        template <class InputIterator>
        map (InputIterator first, InputIterator last, const Compare& comp = Compare(), const allocator_type& alloc = allocator_type()) : _nil(NULL) {
//            std::cout << "insert constr" << std::endl;
            _sz = 0;
            _root = NULL;
            _nil = new node_type();
            _nil->_root = &_root;
            _alloc = alloc;
            _key_compare = comp;
            insert(first, last);
        }

        map (const map& x) {
//            std::cout << "copy constr" << std::endl;
            _sz = 0;
            _root = NULL;
            _nil = new node_type();
            _nil->_root = &_root;
            _alloc = x.get_allocator();
            _key_compare = x.key_comp();
            insert(x.begin(), x.end());
        }

        class value_compare : std::binary_function<value_type,value_type,bool>
        {
            friend class map;
        protected:
            key_compare _comp;
            value_compare (key_compare comp) : _comp(comp) {}
        public:
            bool operator() (const value_type& x, const value_type& y) const
            {
                return _comp(x.first, y.first);
            }
        };

        iterator begin() {
            iterator tmp = iterator(_nil);
            if (!_sz)
                return tmp;
            return tmp.minimum(_root);
        }

        const_iterator begin() const {
            const_iterator tmp = const_iterator(_nil);
            if (!_sz)
                return tmp;
            return tmp.minimum(_root);
        }

        iterator end() {
            return iterator(_nil);
        }

        const_iterator end() const {
            return const_iterator(_nil);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend() {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }


        void insert_fixup(node_type *x)
        {
            for (; x->parent->isred;) {
                if (x->parent == x->parent->parent->left) {
                    node_type *y = x->parent->parent->right;
                    if (y->isred) {
                        x->parent->isred = false;
                        y->isred = false;
                        x->parent->parent->isred = true;
                        x = x->parent->parent;
                    }
                    else {
                        if (x == x->parent->right) {
                            x = x->parent;
                            rotate_left(x);
                        }
                        x->parent->isred= false;
                        x->parent->parent->isred = true;
                        rotate_right(x->parent->parent);
                    }
                }
                else {
                    node_type *y = x->parent->parent->left;
                    if (y->isred) {
                        x->parent->isred = false;
                        y->isred = false;
                        x->parent->parent->isred = true;
                        x = x->parent->parent;
                    }
                    else {
                        if (x == x->parent->left) {
                            x = x->parent;
                            rotate_right(x);
                        }
                        x->parent->isred = false;
                        x->parent->parent->isred = true;
                        rotate_left(x->parent->parent);
                    }
                }
            }
            _root->isred = false;
        }

        pair<iterator,bool> insert (const value_type &val) {
            if (_sz == 0) {
                node_type *new_node = new node_type(val, _nil);
//                std::cout << "pointer val: " << &val << std::endl;
                iterator for_return(new_node);
                _root = new_node;
                new_node->parent = _nil;
//                std::cout << "before insert_fixup" << std::endl;
                insert_fixup(new_node);
//                std::cout << "after insert_fixup" << std::endl;
                ++_sz;
                return ft::make_pair(for_return, true);
            }
            node_type *start = _root;
            node_type *prev = NULL;
            while (!start->isnil) {
                if (val.first == start->data->first)
                    return ft::make_pair(iterator(start), false);
                prev = start;
                if (_key_compare(val.first, start->data->first)) {
                    start = start->left;
                }
                else {
                    start = start->right;
                }
            }
            node_type *tmp = new node_type(val, _nil);
            if (_key_compare(val.first, prev->data->first))
                prev->left = tmp;
            else
                prev->right = tmp;
            tmp->parent = prev;
//            std::cout << "before insert_fixup" << std::endl;
            insert_fixup(tmp);
//            std::cout << "after insert_fixup" << std::endl;
            ++_sz;
            iterator for_return(tmp);
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

        void delete_fixup(node_type *x)
        {
//            std::cout << "delete fixup" << std::endl;
            for (; x != _root && !x->isred;) {
//                std::cout << "delete fixup1" << std::endl;
                if (x == x->parent->left) {
                    node_type *w = x->parent->right;
                    if (w->isred) {
                        w->isred = false;
                        x->parent->isred = true;
                        rotate_left(x->parent);
                        w = x->parent->right;
                    }
                    if (!w->left->isred && !w->right->isred) {
                        w->isred = true;
                        x = x->parent;
                    } else {
                        if (!w->right->isred) {
                            w->left->isred = false;
                            w->isred = true;
                            rotate_right(w);
                            w = x->parent->right;
                        }
                        w->isred = x->parent->isred;
                        x->parent->isred = false;
                        w->right->isred = false;
                        rotate_left(x->parent);
                        x = _root;
                    }
                } else {
                    node_type *w = x->parent->left;
                    if (w->isred) {
                        w->isred = false;
                        x->parent->isred = true;
                        rotate_right(x->parent);
                        w = x->parent->left;
                    }
                    if (!w->right->isred && !w->left->isred) {
                        w->isred = true;
                        x = x->parent;
                    } else {
                        if (!w->left->isred) {
                            w->right->isred = false;
                            w->isred = true;
                            rotate_left(w);
                            w = x->parent->left;
                        }
                        w->isred = x->parent->isred;
                        x->parent->isred = false;
                        w->left->isred = false;
                        rotate_right(x->parent);
                        x = _root;
                    }
                }
            }
            if (!x->isnil)
                x->isred = false;
        }

        void rotate_left(node_type *x)
        {
//            std::cout << "start left rotate" << std::endl;
            node_type *y = x->right;
            x->right = y->left;
            if (!y->left->isnil)
                y->left->parent = x;
            y->parent = x->parent;
            if (x->parent->isnil) {
                _root = y;
            }
            else if (x == x->parent->left) {
                x->parent->left = y;
            }
            else {
                x->parent->right = y;
            }
            y->left = x;
            x->parent = y;
//            std::cout << "end left rotate" << std::endl;
        }

        void rotate_right(node_type *x)
        {
//            std::cout << "start right rotate" << std::endl;
            node_type *y = x->left;
            x->left = y->right;
            if (!y->right->isnil)
                y->right->parent = x;
            y->parent = x->parent;
            if (x->parent->isnil)
                _root = y;
            else if (x == x->parent->right)
                x->parent->right = y;
            else
                x->parent->left = y;
            y->right = x;
            x->parent = y;
//            std::cout << "end right rotate" << std::endl;
        }

        void transplant (node_type *first, node_type *second) {
            if (first->parent->isnil) {
                _root = second;
            }
            else if (first == first->parent->left) {
                first->parent->left = second;
            }
            else {
                first->parent->right = second;
            }
            second->parent = first->parent;
        }

        void erase (iterator position) {
            node_type *x;
            node_type *z = position.get_node();
            node_type *y = position.get_node();
            bool isred = y->isred;
            if (z->isnil){
                return ;
            }
            if (z->left->isnil) {
                x = z->right;
                transplant(z, z->right);
            }
            else if (z->right->isnil) {
                x = z->left;
                transplant(z, z->left);
            }
            else {
                node_type *y = position.minimum(z->right);
                isred = y->isred;
                x = y->right;
                if (y->parent == z) {
                    x->parent = y;
                }
                else {
                    transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->isred = z->isred;
            }
            if (!isred)
                delete_fixup(x);
            delete y;
            --_sz;
        }

        size_type erase (const key_type& k) {
            iterator elem = this->find(k);
            if (elem != end()) {
                erase(elem);
                return 1;
            }
            return 0;

        }

        void erase (iterator first, iterator last) {
//            std::cout << "erase clear" << std::endl;
//            int i = 0;
//            int size_z = size();
//            std::cout << "size" << size() << std::endl;
            iterator tmp;
            for (; first != last; ) {
                tmp = first;
                first++;
//                ++i;
//                std::cout << "size" << size_z << " erase elem" << i << std::endl;
                erase(tmp);
            }
        }

        void clear() {
            erase(begin(), end());
        }

        void swap (map& x) {
            size_type           _sz_tmp = x._sz;
            allocator_type      _alloc_tmp = x._alloc;
            node_type           *_nil_tmp = x._nil;
            node_type           *_root_tmp = x._root;
            Compare             _key_compare_tmp = x._key_compare;

            x._sz = this->_sz;
            x._alloc = this->_alloc;
            x._nil = this->_nil;
            x._root = this->_root;
            x._key_compare = this->_key_compare;

            this->_sz = _sz_tmp;
            this->_alloc = _alloc_tmp;
            this->_nil = _nil_tmp;
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

        allocator_type get_allocator() const {
            return _alloc;
        }

        iterator find (const Key& k) {
            if (_sz == 0)
                return this->end();
            node_type *start = _root;
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
                return this->end();
            node_type *start = _root;
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
            return this->end();
        }

        size_type count (const key_type& k) const {
            if (_sz == 0)
                return 0;
            if (find(k) != this->end())
                return 1;
            return 0;
        }

        key_compare key_comp() const {
            return _key_compare;
        }

        value_compare value_comp() const {
            return value_comp(Compare());
        }

        mapped_type& at (const key_type& k){
            iterator element = find(k);
            if (element == end())
                throw std::length_error("Index out of range");
            return element->second;
        }

        const mapped_type& at (const key_type& k) const {
            const_iterator element = find(k);
            if (element == end())
                throw std::length_error("Index out of range");
            return element->second;
        }

        //???????????? ??????????????, ?????????????? ???????????? ?????? ?????????? ????????????????
        iterator lower_bound (const key_type& k) {
            if (_sz == 0)
                return end();
            node_type *start = _root;
            node_type *prev = _nil;
            while (!start->isnil) {
                if (_key_compare(start->data->first, k)) {
                    start = start->right;
                }
                else {
                    prev = start;
                    start = start->left;
                }
            }
            return iterator(prev);
        }

        const_iterator lower_bound (const key_type& k) const {
            if (_sz == 0)
                return end();
            node_type *start = _root;
            node_type *prev = _nil;
            while (!start->isnil) {
                if (_key_compare(start->data->first, k)) {
                    start = start->right;
                }
                else {
                    prev = start;
                    start = start->left;
                }
            }
            return const_iterator(prev);
        }

        iterator upper_bound (const key_type& k) {
            if (_sz == 0)
                return end();
            node_type *start = _root;
            node_type *prev = _nil;
            while (!start->isnil) {
                if (_key_compare(k, start->data->first)) {
                    prev = start;
                    start = start->left;
                }
                else {
                    start = start->right;
                }
            }
            return iterator(prev);
        }

        const_iterator upper_bound (const key_type& k) const {
            if (_sz == 0)
                return end();
            node_type *start = _root;
            node_type *prev = _nil;
            while (!start->isnil) {
                if (_key_compare(k, start->data->first)) {
                    prev = start;
                    start = start->left;
                }
                else {
                    start = start->right;
                }
            }
            return const_iterator(prev);
        }

        ft::pair<iterator,iterator> equal_range(const key_type& k) {
            return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
        }

        ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const {
            return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
        }

        map& operator= (const map& x) {
//            std::cout << "operator=" << std::endl;
            if (this == &x)
                return *this;
            if (_sz)
                clear();
            if (x.size())
                insert(x.begin(), x.end());
            return *this;
        }

        mapped_type& operator[] (const key_type& k) {
            return (*((this->insert(make_pair(k,mapped_type()))).first)).second;
        }

        ~map() {
//            std::cout << "destruct" << std::endl;
            clear();
//            std::cout << "desctruct afterclear" << std::endl;
            if (_nil) {
////                std::cout << "delclear" << std::endl;
                delete _nil;
            }
//            std::cout << "endclear" << std::endl;
        }
    };

    template <class Key, class T, class Compare, class Alloc>
    bool operator== (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
        return (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator!= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
        return !(lhs==rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
        return !ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
        return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
        return !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class Key, class T, class Compare, class Alloc>
    void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) {
        x.swap(y);
    }
};

#endif //VECTOR_HPP
