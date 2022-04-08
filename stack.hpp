#ifndef STACK_HPP
#define STACK_HPP

#include <vector>
namespace ft {
    template<class T, class Container = vector <T> >
    class stack {
        protected:
            Container cntr_;
        public:
            explicit stack(const Container &cntr = Container()) : cntr_(cntr) {};

            bool empty() const {return cntr_.empty();}

            size_t size() const {return cntr_.size();}

            T &top() {return cntr_.back();}

            const T &top() const {return cntr_.back();}

            void push(const T &val) {cntr_.push_back(val);}

            void pop() {cntr_.pop_back();}

            bool Eq(const stack<T,Container>& rhs) const {return (cntr_ == rhs.cntr_);}

            bool Less(const stack<T,Container>& rhs) const {return (cntr_ < rhs.cntr_);}
    };

            template <class T, class Container>
            inline bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs.Eq(rhs);}

            template <class T, class Container>
            inline bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return !(lhs.Eq(rhs));}

            template <class T, class Container>
            inline bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs.Less(rhs);}

            template <class T, class Container>
            inline bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return (lhs.Less(rhs) or lhs.Eq(rhs));}

            template <class T, class Container>
            bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return (!lhs.Less(rhs) and !lhs.Eq(rhs));}

            template <class T, class Container>
            bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return (!lhs.Less(rhs));}

};
#endif
