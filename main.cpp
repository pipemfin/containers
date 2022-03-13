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

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    ft::stack<int> mystack;
    ft::stack<int> mystack2;

    std::cout << mystack.empty() << std::endl;
    std::cout << mystack.size() << std::endl;
    mystack.push(10);
    std::cout << mystack.size() << std::endl;
    std::cout << mystack.empty() << std::endl;

    std::cout << mystack.top() << std::endl;
//    mystack.pop();
//    std::cout << mystack.size() << std::endl;

    bool a = mystack==mystack2;
    std::cout << a << std::endl;
    return (0);
}
