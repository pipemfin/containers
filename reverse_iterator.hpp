#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator.hpp"
#include "iterator_traits.hpp"

namespace ft {
    template<class Iterator>
    class reverse_iterator : public iterator
            <typename iterator_traits<Iterator>::iterator_category,
                    typename iterator_traits<Iterator>::value_type,
                    typename iterator_traits<Iterator>::difference_type,
                    typename iterator_traits<Iterator>::pointer,
                    typename iterator_traits<Iterator>::reference> {
    private:
        typedef typename iterator_traits<Iterator>::difference_type Dist;
        typedef typename iterator_traits<Iterator>::pointer Ptr;
        typedef typename iterator_traits<Iterator>::reference Ref;

    protected:
        Iterator _current;

    public:
        typedef Iterator iterator_type;

        reverse_iterator() {
            _current = NULL;
        }

        explicit reverse_iterator(const Iterator &x) : _current(x) {}

        template<class U>
        reverse_iterator(const reverse_iterator<U> &x) {
            _current = x.base();
        }

        Iterator base() const {
            return _current;
        }

        Ref operator*() const{
            iterator_type copy(_current);
            return *(--copy);
        }

        Ptr operator->() const {
            return &**this;
        }

        reverse_iterator &operator++() {
            --_current;
            return (*this);
        }

        reverse_iterator operator++(int) {
            reverse_iterator copy(*this);
            --_current;
            return copy;
        }

        reverse_iterator &operator--() {
            ++_current;
            return *this;
        }

        reverse_iterator operator--(int) {
            reverse_iterator copy(*this);
            ++_current;
            return copy;
        }

        reverse_iterator &operator+=(Dist n) {
            _current = _current - n;
            return *this;
        }

        reverse_iterator &operator+(Dist n) {
            return reverse_iterator(*this) += n;
        }

        reverse_iterator &operator-=(Dist n) {
            _current = _current + n;
            return *this;
        }

        reverse_iterator &operator-(Dist n) {
            return reverse_iterator(*this) -= n;
        }

        Ref operator[](Dist n) const {
            return *(*this + n);
        }
    };
}


#endif //REVERSE_ITERATOR_HPP
