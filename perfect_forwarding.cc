#include <cstdlib>
#include <cxxabi.h>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>

template <class T>
std::string type_name()
{
  typedef typename std::remove_reference<T>::type TR;
  std::unique_ptr<char, void (*)(void*)> own(
      abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr),
      std::free);
  std::string r = own != nullptr ? own.get() : typeid(TR).name();
  if (std::is_const<TR>::value) r += " const";
  if (std::is_volatile<TR>::value) r += " volatile";
  if (std::is_lvalue_reference<T>::value)
    r += "&";
  else if (std::is_rvalue_reference<T>::value)
    r += "&&";
  return r;
}

class Widget
{
 public:
  template <typename T>
  void setName(T&& newName)
  {
    std::cout << "setName(" << type_name<T>() << " && newName)" << std::endl;
    //std::string name = std::forward<T>(newName);
    std::string name = std::move(newName);
  }
};

class X
{
 public:
  X() {}
  // copy constructor.
  X(const X& other)
  {
    std::cout << "X's copy constructor [X(const X& other)]" << std::endl;
  }
  // move constructor.
  X(X&& other)
  {
    std::cout << "X's move constructor [X(const X&& other)]" << std::endl;
  }
};

int main()
{
  Widget w;
  std::string name("foo");
  w.setName(name);
  w.setName(std::string("spam"));
  std::cout << name << std::endl;
  std::cout << "--" << std::endl;
  //w.setName(X());
  X x;
  //w.setName(x);
  return 0;
}
