#include <iostream>

namespace stnd {

template <typename T>
class Swap {
public:
    Swap(T &l, T &r) {
        T temp;
        temp = l;
        l = r;
        r = temp;
    }
};

} // namespace stnd
