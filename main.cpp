#include <iostream>
#include <vector>
#include "vector.hpp"
//#include "stack.hpp"
#include "utils.hpp"

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

//class newtype {
//public:
//    int first_elem;
//    int second_elem;
//
//    newtype() {
//        first_elem = 666;
//        second_elem = 666;
//    }
//
//    newtype(const newtype &a) {
//        first_elem = a.first_elem;
//        second_elem = a.second_elem;
//    }
//};
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

//int main(int argc, char** argv) {
//    (void) argc;
//    (void) argv;
//
//    ft::vector<int> first_vect(10, 10);
//
//    std::cout << first_vect.size() << std::endl;
//    first_vect.pop_back();
//    std::cout << first_vect.size() << std::endl;
//    std::cout << "Finish" << std::endl;
//}

//int main(int argc, char** argv) {
//    (void) argc;
//    (void) argv;
//
//    ft::vector<int> first_vect;
////    ft::vector<int> sec_vect(first_vect.begin(), first_vect.end());
////    first_vect.assign(10, 5);
//    first_vect.push_back(1);
//    first_vect.push_back(2);
//    first_vect.push_back(3);
//    first_vect.push_back(4);
//    first_vect.push_back(5);
//    first_vect.push_back(6);
//
//    ft::vector<int>::iterator end = first_vect.end() - 1;
//    ft::vector<int>::iterator begin = first_vect.begin();
//    std::cout << first_vect.capacity() << std::endl;
//    std::cout << *end << std::endl;
//    std::cout << first_vect._ptr[first_vect._sz - 1]<< std::endl;
//    std::cout << *begin << std::endl;
//    first_vect.erase(begin, end);
////    std::cout << "HERE" << std::endl;
//    for (ft::vector<int>::iterator start = first_vect.begin(); start != first_vect.end(); ++start) {
//        std::cout << *start << std::endl;
//    }
//}

//operators
//int main(int argc, char** argv) {
//    (void) argc;
//    (void) argv;
//
//    ft::vector<int> first_vect(10, 10);
//    ft::vector<int> second_vect(15, 10);
//    ft::vector<int> third_vect(10, 11);
//    ft::vector<int> fourd_vect(10, 10);
//
//    std::cout << "\noperator =\n" << std::endl;
//    std::cout << (first_vect == second_vect) << std::endl;
//    std::cout << (first_vect == third_vect) << std::endl;
//    std::cout << (first_vect == fourd_vect) << std::endl;
//
//    std::cout << "operator !=" << std::endl;
//    std::cout << (first_vect != second_vect) << std::endl;
//    std::cout << (first_vect != third_vect) << std::endl;
//    std::cout << (first_vect != fourd_vect) << std::endl;
//
//    std::cout << "operator >" << std::endl;
//    std::cout << (first_vect > second_vect) << std::endl;
//    std::cout << (first_vect > third_vect) << std::endl;
//    std::cout << (first_vect > fourd_vect) << std::endl;
//
//    std::cout << "operator >=" << std::endl;
//    std::cout << (first_vect >= second_vect) << std::endl;
//    std::cout << (first_vect >= third_vect) << std::endl;
//    std::cout << (first_vect >= fourd_vect) << std::endl;
//
//    std::cout << "operator <" << std::endl;
//    std::cout << (first_vect < second_vect) << std::endl;
//    std::cout << (first_vect < third_vect) << std::endl;
//    std::cout << (first_vect < fourd_vect) << std::endl;
//
//    std::cout << "operator <=" << std::endl;
//    std::cout << (first_vect <= second_vect) << std::endl;
//    std::cout << (first_vect <= third_vect) << std::endl;
//    std::cout << (first_vect <= fourd_vect) << std::endl;
//}

//swap test
//int main(int argc, char** argv) {
//    (void) argc;
//    (void) argv;
//
//    ft::vector<int> first_vect(10, 10);
//    ft::vector<int> second_vect(20, 20);;
//
//    first_vect.erase(first_vect.begin());
//    ft::swap(first_vect, second_vect);
//    std::cout << "First vector " << first_vect.size() << std::endl;
//    std::cout << "Second vector " << second_vect.size() << std::endl;
//
//    second_vect.swap(first_vect);
//    std::cout << "First vector " << first_vect.size() << std::endl;
//    std::cout << "Second vector " << second_vect.size() << std::endl;
//}

//#include <cstddef>
//#include <cstdint>
//#include <numeric>
//

int main()
{
    ft::vector<int> vect;
//    ft::vector<int> copy;
//    ft::vector<int>::iterator pos;

    vect.push_back(666);
    vect.push_back(666);
    vect.push_back(666);
    vect.push_back(666);
//    for (int i = 0; i < 10; ++i) {
//        copy.push_back(i);
//    }
    vect.insert(vect.end(), 1, 10);
    for (int i = 0; i < vect.size(); ++i) {
        std::cout << vect[i] << std::endl;
    }
    std::cout << "size:" << vect.size() << "cpcty:" << vect.capacity() << std::endl;
//    std::cout << "Позиция:" << *pos << std::endl;
}

//int main()v
//{
//    ft::vector<int> vect(5, 10);
//
////        vect.insert(vect.end(), 2);
////        vect.insert(vect.end() - 1, 2);
//        vect.insert(vect.begin() + 1, 2);
////    vect.insert(vect.begin(), 2);
//
//    for (int i = 0; i < vect.size(); ++i) {
//        std::cout << "-->" << vect[i] << "<--" << std::endl;
//    }
//}

//int main()
//{
//    ft::vector<int> vect(10, 10);
//
//    //    vect.insert(vect.end(), 2, 11);
//    //    vect.insert(vect.end() - 1, 2, 11);
//    //    vect.insert(vect.begin(), 2, 11);
//    vect.insert(vect.begin() + 1, 2, 11);
//
//    for (int i = 0; i < vect.size(); ++i) {
//        std::cout << "-->" << vect[i] << "<--" << std::endl;
//    }
//}

//int main()
//{
//    ft::vector<int> vect(4, 10);
//    ft::vector<int> vect2(10, 11);
//
////    vect.insert(vect.end(), 2, 11);
////    vect.insert(vect.end() - 1, 2, 11);
////    vect.insert(vect.begin(), 2, 11);
////    vect.insert(vect.begin() + 1, 2, 11);
//
//    for (int i = 0; i < vect.size(); ++i) {
//        std::cout << "-->" << vect[i] << "<--" << std::endl;
//    }
//}

//int main()
//{
//    ft::vector<int> vect(10);
//    ft::vector<int> vect2(3, 3);
//
//    vect.insert(vect.begin(), vect2.begin(), vect2.end());
//
//    for (int i = 0; i < vect.size(); ++i) {
//        std::cout << vect[i] << std::endl;
//    }
//}

class B {
public:
    char *l;
    int i;
    B():l(nullptr), i(1) {};
    B(const int &ex) {
        this->i = ex;
        this->l = new char('a');
    };
    virtual ~B() {
        delete this->l;
        this->l = nullptr;
    };
};

class A : public B {
public:
    A():B(){};
    A(const B* ex){
        this->l = new char(*(ex->l));
        this->i = ex->i;
        if (ex->i == -1) throw "n";
    }
    ~A() {
        delete this->l;
        this->l = nullptr;
    };
};

//int main()
//{
//    int _ratio = 400;
//    ft::vector<int> vector(10,10);
//    ft::vector<int> v;
//    vector.assign(2600 * _ratio, 1);
//    v.push_back(*(vector.insert(vector.end() - 800 * _ratio, 44)));
//    v.push_back(vector.size());
//    v.push_back(vector.capacity());
//    std::unique_ptr<B> k2(new B(3));
//    std::unique_ptr<B> k3(new B(4));
//    std::unique_ptr<B> k4(new B(-1));
//    ft::vector<A> vv;
//    ft::vector<B*> v1;
//
//    v1.push_back(&(*k2));
//    v1.push_back(&(*k3));
//    v1.push_back(&(*k4));
//    for (int i = 0;i < 3; ++i){
//        std::cout << v1[i]->i << std::endl;
//    }
//    std::cout << "before call 'insert'" << std::endl;
//    try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
//    catch (...) {
//        v.push_back(vv.size());
//        v.push_back(vv.capacity());
//        std::cout << vv.size() << std::endl;
//        for (int i = 0; i < vv.size(); ++i){
//            std::cout << vv[i].i << std::endl;
//        }
//    }
//}

//int main()
//{
//    std::vector<A>   vect;
//    std::vector<B*> copy;
//    char *first;
//    char *second;
//    std::unique_ptr<B> k2(new B(3));
//    std::unique_ptr<B> k3(new B(4));
//    std::unique_ptr<B> k4(new B(-1));
//    copy.push_back(&(*k2));
//    copy.push_back(&(*k3));
//    copy.push_back(&(*k4));
////    vect.pop_back();
////    vect.pop_back();
//    try {
//        vect.insert(vect.begin(), copy.begin(), copy.end());
//    }
//    catch (...){
//        std::cout << "size -->" << vect.size() << "<--" << std::endl;
//        std::cout << "cpcty -->" << vect.capacity() << "<--" << std::endl;
//    }
////    for (int i = 0; i < vect.size(); ++i) {
////        std::cout << "-->" << vect[i] << "<--" << std::endl;
////    }
//}