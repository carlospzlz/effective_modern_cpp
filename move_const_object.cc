#include <iostream>
using namespace std;

class X
{
public:
    X(){};
    X(const X&) { cout << "copy" << endl; };
    X(X&&)      { cout << "move" << endl; };
};

int main()
{
    const X x1;
    X x2 = std::move(x1);
}
