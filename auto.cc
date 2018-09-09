#include <cxxabi.h>
#include <cstdlib>
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

class Foo
{
};

int main()
{
  Foo x;
  auto&& y = x;
  std::cout << type_name<decltype(y)>() << std::endl;
  //auto&& z = std::move(x);
  auto&& z = std::move(x);
  std::cout << type_name<decltype(z)>() << std::endl;
  return 0;
}
