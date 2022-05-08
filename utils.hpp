#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {

    template<bool Cond, class T = void>
    struct enable_if {
    };

    template<class T>
    struct enable_if<true, T> {
        typedef T type;
    };

    template <bool is_integral, typename T>
    class is_integral_struct {
    public:
        typedef T type;
        static const bool value = is_integral;
    };

    template <typename>
    class is_integral : public is_integral_struct<false, bool> {};

    template <>
    class is_integral<bool> : public is_integral_struct<true, bool> {};

    template <>
    class is_integral<char> : public is_integral_struct<true, char> {};

    template <>
    class is_integral<signed char> : public is_integral_struct<true, signed char> {};

    template <>
    class is_integral<unsigned char> : public is_integral_struct<true, unsigned char> {};

    template <>
    class is_integral<wchar_t> : public is_integral_struct<true, wchar_t> {};

    template <>
    class is_integral<short> : public is_integral_struct<true, short> {};

    template <>
    class is_integral<unsigned short> : public is_integral_struct<true, unsigned short> {};

    template <>
    class is_integral<int> : public is_integral_struct<true, int> {};

    template <>
    class is_integral<long> : public is_integral_struct<true, long> {};

    template <>
    class is_integral<unsigned long> : public is_integral_struct<true, unsigned long> {};

    template <>
    class is_integral<float> : public is_integral_struct<false, float> {};

    template <>
    class is_integral<double> : public is_integral_struct<false, double> {};

    template <>
    class is_integral<long double> : public is_integral_struct<false, long double> {};



    template<class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
        while (first1 != last1) {
            if (!(*first1 == *first2))
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }

    template<class InputIterator1, class InputIterator2>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
        while (first1 != last1) {
            if (first2 == last2 || *first2 < *first1)
                return false;
            else if (*first1 < *first2)
                return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }

    template <class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) {
        while (first1 != last1) {
            if (first2 == last2 || comp(first2, first1))
                return false;
            else if comp(first1, first2)
                return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }

    template <class T1, class T2>
    struct pair {
        typedef T1 first_type;
        typedef T2 second_type;
        first_type first;
        second_type second;

        pair() {};


    };
    template <class T1, class T2>
    pair<T1,T2> make_pair (T1 x, T2 y)
    {
        return pair<T1,T2>(x,y);
    }
}

#endif //UTILS_HPP
