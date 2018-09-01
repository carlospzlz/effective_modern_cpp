#include <cassert>
#include <iostream>
#include <vector>

class Widget
{
 public:
  Widget(const std::vector<int>& _v1, const std::vector<int>& _v2)
      : v1(_v1), v2(_v2)
  {
    std::cout << "[" << this << "] Custom constructor called" << std::endl;
    cachedSumOfSizes = v1.size() + v2.size();
    cacheIsUpToDate = true;
  }
  /*
  Widget(const Widget& other)
  {
    std::cout << "[" << this << "] Copy constructor called" << std::endl;
  }
  Widget(const Widget&& other)
  {
    std::cout << "[" << this << "] Move constructor called" << std::endl;
  }
  */
  ~Widget()
  {
    std::cout << "[" << this << "] Destructor called" << std::endl;
    std::cout << " `- v1.size " << v1.size() << std::endl;
    std::cout << " `- v2.size " << v2.size() << std::endl;
    std::cout << " `- cacheIsUpToDate " << cacheIsUpToDate << std::endl;
    std::cout << " `- cachedSumOfSizes " << cachedSumOfSizes << std::endl;
    checkInvariant();
  }

 private:
  void checkInvariant()
  {
    assert(!cacheIsUpToDate || cachedSumOfSizes == v1.size() + v2.size());
  }

 private:
  std::vector<int> v1;
  std::vector<int> v2;
  mutable std::size_t cachedSumOfSizes;
  mutable bool cacheIsUpToDate;
};

int main()
{
  Widget w1({1}, {1, 2});
  // Widget w2 = w1;
  // Compiler constructs in return value directly, no move happens.
  // Widget w3(Widget({1}, {1, 2}));
  Widget w4(std::move(w1));
  return 0;
}
