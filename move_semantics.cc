#include <iostream>
#include <vector>

class Foo
{
 public:
  Foo(int x) : m_value(x)
  {
    std::cout << "Constructed Foo with default constructor at " << this
              << std::endl;
  }
  Foo(const Foo& other)
  {
    std::cout << "Constructed Foo with copy constructor at " << this
              << std::endl;
  }
  Foo(Foo&& other)
  {
    std::cout << "Constructed Foo with move constructor at " << this
              << std::endl;
  }

  int getValue() { return m_value; }

 private:
  int m_value;
};

class Spam
{
 public:
  Spam()
  {
    std::cout << "Constructed Spam with default constructor at " << this
              << std::endl;
  }
  Spam(const Spam&& other)
  {
    std::cout << "Constructed Spam with move constructor at " << this
              << std::endl;
  }
};

void doSomething(const Foo&& foo)
{
  Foo other_foo = foo;
}

int main()
{
  // With int's you don't move as there's no indirection.
  int x = 7;
  int y = std::move(x);
  std::cout << "x = " << x << std::endl;
  std::cout << "y = " << y << std::endl;
  x = 9;
  std::cout << "x = " << x << std::endl;
  std::cout << "y = " << y << std::endl;
  std::cout << "--" << std::endl;

  // Let's try with objets.
  Foo foo_x{7};
  Foo foo_y = foo_x;
  Foo foo_z = std::move(foo_x);
  std::cout << "--" << std::endl;

  // What about containers?
  std::vector<Spam> spams;
  spams.push_back(Spam());
  std::cout << "--" << std::endl;

  // Which constructor gets called?
  Foo foo {9};
  // doSomething(foo); // error: cannot bind rvalue reference to lvalue
  doSomething(Foo(11)); // surprise, suprise
  std::cout << "--" << std::endl;

  // wtf?
  const Foo a {13};
  Foo b = std::move(a);

  return 0;
}
