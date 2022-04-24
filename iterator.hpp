#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace  ft {

    struct output_iterator_tag {};
    struct input_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template<class C, class T, class Dist = ptrdiff_t, class Pt = T *, class Rt = T &>
    struct iterator {
        typedef C iterator_category;
        typedef T value_type;
        typedef Dist difference_type;
        typedef Pt pointer;
        typedef Rt reference;
    };
}

#endif //ITERATOR_HPP
