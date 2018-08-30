// http://thbecker.net/articles/rvalue_references/section_01.html

#include <iostream>

void foo(int& x)
{
    std::cout << "foo(int&)" << std::endl;
}

void foo(int&& x)
{
    std::cout << "foo(int&&)" << std::endl;
}

/// If we define this, calling foo will be ambigous.
/*
void foo(int x)
{
    std::cout << "foo(int)" << std::endl;
}
*/

void spam(const int& x)
{
    std::cout << "spam(const int&)" << std::endl;
}

class X
{
};

int main()
{
    int x {1};
    foo(x);
    foo(1);
    std::cout << "--" << std::endl;
    spam(x);
    spam(1);
    return 0;
}
