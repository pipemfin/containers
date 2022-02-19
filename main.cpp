#include <iostream>
#include <string>

template <typename T>
void printing(T argue, int count)
{
    for(int i = 0; i < count; i++)
        std::cout << argue << std::endl;
}

int main(int argc, char** argv)
{
    std::string lol = "sadb";

    printing(lol, 10);
    return (0);
}