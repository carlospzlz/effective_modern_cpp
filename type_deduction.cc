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

int main()
{
  auto init_list = {1, 2, 3};
  const int& const_int_ref = 1;
  auto single_value {1};

  std::cout << type_name<decltype(nullptr)>() << std::endl;
  std::cout << type_name<decltype(0)>() << std::endl;
  std::cout << type_name<decltype("Hello World!")>() << std::endl;
  std::cout << type_name<decltype(init_list)>() << std::endl;
  std::cout << type_name<decltype(const_int_ref)>() << std::endl;
  std::cout << type_name<decltype(single_value)>() << std::endl;

  return 0;
}
