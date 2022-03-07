#include <iostream>
//#include "vector.hpp"
#include <vector>

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    std::vector<int> abc(3);
    std::vector<int> def(1);
    std::vector<int> def2(2);
    std::vector<int> def3(4);
    std::vector<int> def4(5);
    std::vector<int> def5(8);
    std::vector<int> def6(9);

    std::cout << "size:" << abc.size() << " ,capacity:" << abc.capacity() << std::endl;
    for(int i = 0; i < 10; ++i){
        abc.push_back(i);
        std::cout << "size:" << abc.size() << " ,capacity:" << abc.capacity() << std::endl;
    }
    std::cout << "size:" << abc.size() << " ,capacity:" << abc.capacity() << std::endl;
    std::cout << "size:" << def.size() << " ,capacity:" << def.capacity() << std::endl;
    std::cout << "size:" << def2.size() << " ,capacity:" << def2.capacity() << std::endl;
    std::cout << "size:" << def3.size() << " ,capacity:" << def3.capacity() << std::endl;
    std::cout << "size:" << def4.size() << " ,capacity:" << def4.capacity() << std::endl;
    std::cout << "size:" << def5.size() << " ,capacity:" << def5.capacity() << std::endl;
    std::cout << "size:" << def6.size() << " ,capacity:" << def6.capacity() << std::endl;
    return (0);
}