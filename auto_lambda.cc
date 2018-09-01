#include <iostream>

int main()
{
  const int a = 10;
  const int b = 7;
  auto f =
    [a, b](int x) { return x*a + b; };
  std::cout << f(1) << std::endl;
  std::cout << f(2) << std::endl;
  std::cout << typeid(f).name() << std::endl;
  return 0;
}
