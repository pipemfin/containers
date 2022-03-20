#include <iostream>
#include "vector.hpp"
#include "stack.hpp"

//int main(int argc, char** argv)
//{
//    (void)argc;
//    (void)argv;
//    std::vector<int> abc(3);
//    std::vector<int> def(1);
//    std::vector<int> def2(2);
//    std::vector<int> def3(4);
//    std::vector<int> def4(5);
//    std::vector<int> def5(8);
//    std::vector<int> def6(9);
//
//    std::cout << "size:" << abc.size() << " ,capacity:" << abc.capacity() << std::endl;
//    for(int i = 0; i < 10; ++i){
//        abc.push_back(i);
//        std::cout << "size:" << abc.size() << " ,capacity:" << abc.capacity() << std::endl;
//    }
//    std::cout << "size:" << abc.size() << " ,capacity:" << abc.capacity() << std::endl;
//    std::cout << "size:" << def.size() << " ,capacity:" << def.capacity() << std::endl;
//    std::cout << "size:" << def2.size() << " ,capacity:" << def2.capacity() << std::endl;
//    std::cout << "size:" << def3.size() << " ,capacity:" << def3.capacity() << std::endl;
//    std::cout << "size:" << def4.size() << " ,capacity:" << def4.capacity() << std::endl;
//    std::cout << "size:" << def5.size() << " ,capacity:" << def5.capacity() << std::endl;
//    std::cout << "size:" << def6.size() << " ,capacity:" << def6.capacity() << std::endl;
//    return (0);
//}

//int main(int argc, char** argv)
//{
//    (void)argc;
//    (void)argv;
//    ft::vector<int> abc(2);
//
////    std::cout << "size:" << abc.size() << " ,capacity:" << abc.capacity() << std::endl;
////    for(int i = 0; i < 9; ++i)
////        std::cout << "i = |" << i << "|, value:" << abc[i] << std::endl;
////    std::cout << "Bullshit" << std::endl;
//    std::cout << "size:" << abc.size() << " ,capacity:" << abc.capacity() << std::endl;
//    abc.pop_back();
//    std::cout << "size:" << abc.size() << " ,capacity:" << abc.capacity() << std::endl;
//    abc.pop_back();
//    std::cout << "size:" << abc.size() << " ,capacity:" << abc.capacity() << std::endl;
//    abc.push_back(10);
//    abc.push_back(10);
//    std::cout << "size:" << abc.size() << " ,capacity:" << abc.capacity() << std::endl;
//    std::cout << "Bullshit" << std::endl;
//    std::cout << "size:" << abc.size() << " ,capacity:" << abc.capacity() << std::endl;
//    abc.push_back(10);
//    std::cout << "size:" << abc.size() << " ,capacity:" << abc.capacity() << std::endl;
//    std::cout << abc[8] << std::endl;
//    std::cout << "size:" << abc.size() << " ,capacity:" << abc.capacity() << std::endl;
//    abc.pop_back();
//    std::cout << "size:" << abc.size() << " ,capacity:" << abc.capacity() << std::endl;
//    return (0);
//}

//int main(int argc, char** argv)
//{
//    (void)argc;
//    (void)argv;
//    std::vector<int> abc(10, 5);
//
//    std::cout << *abc.end() << std::endl;
////    std::cout << "size:" << abc.size() << " ,capacity:" << abc.capacity() << std::endl;
//
////    for(int i = 0; i < 10; ++i){
////        abc.push_back(i);
////        std::cout << "size:" << abc.size() << " ,capacity:" << abc.capacity() << std::endl;
////    }
//
//    return (0);
//}

//int main(int argc, char** argv)
//{
//    (void)argc;
//    (void)argv;
//    ft::stack<int> mystack;
//    ft::stack<int> mystack2;
//
//    std::cout << mystack.empty() << std::endl;
//    std::cout << mystack.size() << std::endl;
//    mystack.push(10);
//    std::cout << mystack.size() << std::endl;
//    std::cout << mystack.empty() << std::endl;
//
//    std::cout << mystack.top() << std::endl;
////    mystack.pop();
////    std::cout << mystack.size() << std::endl;
//
//    bool a = mystack==mystack2;
//    std::cout << a << std::endl;
//    return (0);
//}

class newtype {
public:
    int first_elem;
    int second_elem;

    newtype() {
        first_elem = 666;
        second_elem = 666;
    }

    newtype(const newtype &a) {
        first_elem = a.first_elem;
        second_elem = a.second_elem;
    }
};
/*
int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    ft::vector<int> vect(10, 10);
    ft::vector<int>::iterator iter = vect.begin();
    ft::vector<int>::iterator iter_sec = vect.begin();
    ft::vector<int>::iterator iter2(iter);
    ft::vector<int>::iterator end = vect.end();
    bool eq = false;
    newtype structure;
    ft::vector<newtype> strict(10, structure);
    ft::vector<newtype>::iterator strict_iter = strict.begin();
    ft::vector<newtype>::iterator strict_end = strict.end();

    std::cout << "size:" << vect.size() << " ,capacity:" << vect.capacity() << std::endl;

    std::cout << "iterators" << std::endl;
    for (; iter != end; ++iter)
        std::cout << "value:" << *iter << std::endl;
    std::cout << "second iterator" << std::endl;
    for (; iter2 != end; ++iter2)
        std::cout << "value:" << *iter2 << std::endl;
    std::cout << "check ->:" << std::endl;
    for (; strict_iter != strict_end; ++strict_iter)
        std::cout << "value:" << strict_iter->first_elem << " and:" << strict_iter->first_elem  << std::endl;
    *iter_sec = 777;
    std::cout << "check *a=t " << *iter_sec << std::endl;

    iter = vect.begin();
    for (int i = 0; iter != end; ++iter, i++)
        *iter = i;

    iter = vect.begin();
    iter_sec = vect.begin();
    ++iter_sec;
    iter_sec++;
    std::cout << "check ++a (must be 1) = " << *(++iter) << std::endl;
    std::cout << "check a++ (must be 1) = " << *(iter++) << std::endl;

    eq = (iter == iter_sec);
    std::cout << "check *a++ == *b++ (must be 1) = " << eq << std::endl;


    iter = vect.end();
    iter_sec = vect.end();
    --iter_sec;
    iter_sec--;
    std::cout << "check ++a (must be 9) = " << *(--iter) << std::endl;
    std::cout << "check a++ (must be 9) = " << *(iter--) << std::endl;

    eq = false;
    eq = (iter == iter_sec);
    std::cout << "check *a++ == *b++ (must be 1) = " << eq << std::endl;


    iter = vect.begin();
    iter += 5;
    std::cout << "check a += n (must be 5) = " << *(iter) << std::endl;
    iter -= 2;
    std::cout << "check a -= n (must be 3) = " << *(iter) << std::endl;


    std::cout << "check a > b (must be 0) = " << (iter > end) << std::endl;
    std::cout << "check a < b (must be 1) = " << (iter < end) << std::endl;
    std::cout << "check a >= b (must be 1) = " << (iter >= end) << std::endl;
    std::cout << "check a <= b (must be 0) = " << (iter <= end) << std::endl;

    iter = vect.begin();
    std::cout << "check a[6] (must be 0) = " << iter[6] << std::endl;

    return (0);
}*/

int main(int argc, char** argv) {
    (void) argc;
    (void) argv;

    ft::vector<int> first_vect(10, 10);
    ft::vector<int> second_vect(first_vect);

    for (size_t a = 0; a < second_vect.size() ; ++a) {
        std::cout << "a = " << a << ", value:"<< second_vect[a] << std::endl;
    }

    std::cout << "Finish" << std::endl;
}