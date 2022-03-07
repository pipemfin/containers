#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stddef.h>
#include <memory>
namespace ft {

    template<typename T, class allocator_type = std::allocator<T> >
    class vector{
    private:
        size_t sz;
        size_t cpcty;
        T* ptr;
        allocator_type alloc;

    public:
        vector (const allocator_type& alloc = allocator_type()) {
            this->sz = 0;
            this->cpcty = 0;
            this->ptr = NULL;
        }

        vector (size_t n, const T& val = T(),
                const allocator_type& alloc = allocator_type()) {
            this->sz = n;
            this->cpcty = n;
            this->ptr = alloc.allocate(n);
            alloc.construct(ptr, val);
        }

        template <class InputIterator>
        vector (InputIterator first, InputIterator last,
                const allocator_type& alloc = allocator_type());

        vector (const vector& x);

        size_t size() const{
            return this->sz;
        }

        size_t max_size() const{
            return 100;
        }

        size_t capacity() const {
            return this->cpcty;
        }

        void reserve (size_t n) {
            T* temp = NULL;
            T* for_del = NULL;
            if (n > this->cpcty) {
                temp = this->alloc.allocate(n);
                for(size_t cnt = 0; cnt < sz; cnt++)
                    temp[cnt](ptr[cnt]);
                for_del = this->ptr;
                this->ptr = temp;
                for(size_t cnt = sz; cnt > 0; --cnt)
                    for_del[cnt]->~T();
                delete[] for_del;
            }
        }

        void resize (size_t n, T val = T()) {
            if (n < this->sz)
                for(; this->sz > n;--(this->sz))
                    ptr[sz]->~T();
            else if (n > this->sz and n > this->cpcty) {
            }
            else if (n > this->sz)
                for(; this->sz < n;++(this->sz))
                    ptr[sz - 1] = T();
        }

        bool empty() const {
            if (this->sz == 0)
                return true;
            return false;
        }

        ~vector() {};
    };
}

#endif //VECTOR_HPP
