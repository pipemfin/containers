#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator.hpp"
#include "iterator_traits.hpp"

namespace ft {
    template<class RandIt>
    class reverse_iterator : public iterator
            <typename iterator_traits<RandIt>::iterator_category,
                    typename iterator_traits<RandIt>::value_type,
                    typename iterator_traits<RandIt>::difference_type,
                    typename iterator_traits<RandIt>::pointer,
                    typename iterator_traits<RandIt>::reference> {
    private:
        typedef typename iterator_traits<RandIt>::difference_type Dist;
        typedef typename iterator_traits<RandIt>::pointer Ptr;
        typedef typename iterator_traits<RandIt>::reference Ref;

    protected:
        RandIt _current;

    public:
        typedef RandIt iterator_type;

        reverse_iterator() {
            _current = NULL;
        }

        explicit reverse_iterator(RandIt x) {
            _current = x;
        }

        template<class U>
        reverse_iterator(const reverse_iterator<U> &x) {
            _current = x.base();
        }

        RandIt base() const {
            return _current;
        }

        Ref operator*() const {
            return *(_current - 1);
        }

        Ptr operator->() const {
            return &**this;
        }

        reverse_iterator &operator++() {
            --_current;
            return (*this);
        }

        reverse_iterator operator++(int) {
            reverse_iterator copy(this);
            --_current;
            return (copy);
        }

        reverse_iterator &operator--() {
            ++_current;
            return *this;
        }

        reverse_iterator operator--(int) {
            reverse_iterator copy(this);
            ++_current;
            return copy;
        }

        reverse_iterator &operator+=(Dist n) {
            _current = _current - n;
            return *this;
        }

        reverse_iterator &operator+(Dist n) const {
            return reverse_iterator(*this) += n;
        }

        reverse_iterator &operator-=(Dist n) {
            _current = _current + n;
            return *this;
        }

        reverse_iterator &operator-(Dist n) const {
            return reverse_iterator(*this) -= n;
        }

        Ref operator[](Dist n) const {
            return *(*this + n);
        }
    };
}


#endif //REVERSE_ITERATOR_HPP
