#include <iostream>

struct test
{
    void f() &
    {
        std::cout << "lvalue object" << std::endl;
    }

    void f() &&
    {
        std::cout << "rvalue object" << std::endl;
    }
};

int main()
{
    test t;
    t.f();
    test().f();
    return 0;
}
