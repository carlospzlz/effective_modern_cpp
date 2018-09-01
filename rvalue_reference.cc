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

void moo(int&& x)
{
    std::cout << "moo(int&&)" << std::endl;
}

void spam(const int& x)
{
    std::cout << "spam(const int&)" << std::endl;
}

class IntWrapper
{
  public:
    IntWrapper(int x) {
      std::cout << "IntWrapper(int)" << std::endl;
    }
};

void foo_intWrapper(IntWrapper&& x) { }

int main()
{
    int x {1};
    foo(x);
    foo(1);
    std::cout << "--" << std::endl;
    spam(x);
    spam(1);
    std::cout << "--" << std::endl;
    moo(1.1);
    std::cout << "--" << std::endl;
    //IntWrapper w(5);
    //foo_intWrapper(w);
    //foo_intWrapper(std::move(w));
    foo_intWrapper(7);
    return 0;
}
