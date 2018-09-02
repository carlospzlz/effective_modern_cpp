#include <iostream>
#include <string>

class X
{
 public:
  template <typename T>
  void setName(T&& newName)
  {
    std::cout << "y.setName by forwarding" << std::endl;
    m_name = std::forward<T>(newName);
  }
  std::string& getName() { return m_name; }
 private:
  std::string m_name;
};

class Y
{
 public:
  template <typename T>
  void setName(T&& newName)
  {
    std::cout << "y.setName by moving" << std::endl;
    m_name = std::move(newName);
  }
  std::string& getName() { return m_name; }
 private:
  std::string m_name;
};

int main()
{
  X x;
  std::string name("foo");
  std::cout << "name = " << name << std::endl;
  x.setName(name);
  std::cout << "x.name = " << x.getName() << std::endl;
  std::cout << "name = " << name << std::endl;
  std::cout << "--" << std::endl;
  Y y;
  std::cout << "name = " << name << std::endl;
  y.setName(name);
  std::cout << "y.name = " << y.getName() << std::endl;
  // name is gone.
  std::cout << "name = " << name << std::endl;
  return 0;
}
