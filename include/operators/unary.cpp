#include "bector.hpp"

bector bector::operator~() const noexcept {
    if (!size()) {
        return *this;
    }
    bector temp(*this);
    temp.flip();

    return temp;
}
