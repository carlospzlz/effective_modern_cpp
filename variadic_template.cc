#include <iostream>
#include <string>

template <class T>
class Container
{
  public:
    template<class... Args>
    void emplace_back(Args&&... args)
    {
      T(args...);
    }
};

class Item
{
  public:
    template<class... Args>
    Item(const std::string& s, const int& i)
    {
      std::cout << "Constructed Item: " << s << " " << i << std::endl;
    }
};

int main()
{
  Container<Item> c;
  c.emplace_back(std::string("Hello World"), 0);
  Item i("foo", 7);
  c.emplace_back(i);
  return 0;
}
