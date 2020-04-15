#include <iostream>
#include "KLVersion.h"
#include "KW_Wrapper.hpp"

int main(void)
{
    std::cout << "Hello World" << '\n';
    std::cout << KL_VERSION_MAJOR_STR << ' ' << KL_VERSION_MINOR << '\n';
}