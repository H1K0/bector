#include "bector.hpp"

bector bector::operator&(const bector &rhs) const noexcept {
    bector temp;
    temp.resize(std::max(size(), rhs.size()));
    for (size_type c = 0; c < std::min(data_.size(), rhs.data_.size()); c++) {
        temp.data_[c] = data_[c] & rhs.data_[c];
    }

    return temp;
}

bector bector::operator|(const bector &rhs) const noexcept {
    bector temp;
    if (size() >= rhs.size()) {
        temp = *this;
    } else {
        temp = rhs;
    }
    for (size_type c = 0; c < std::min(data_.size(), rhs.data_.size()); c++) {
        temp.data_[c] = data_[c] | rhs.data_[c];
    }

    return temp;
}

bector bector::operator^(const bector &rhs) const noexcept {
    bector temp;
    if (size() >= rhs.size()) {
        temp = *this;
    } else {
        temp = rhs;
    }
    for (size_type c = 0; c < std::min(data_.size(), rhs.data_.size()); c++) {
        temp.data_[c] = data_[c] ^ rhs.data_[c];
    }

    return temp;
}

bector bector::operator<<(size_type shift) const noexcept {
    bector temp;
    temp.resize(size());
    if (!shift) {
        return *this;
    }
    if (shift >= size()) {
        return temp;
    }
    for (size_type b = shift; b < size(); b++) {
        if (data_[b / CELL_SIZE][b % CELL_SIZE]) {
            temp.set(b - shift);
        }
    }

    return temp;
}

bector bector::operator>>(size_type shift) const noexcept {
    bector temp;
    temp.resize(size());
    if (!shift) {
        return *this;
    }
    if (shift >= size()) {
        return temp;
    }
    for (size_type b = 0; b < size() - shift; b++) {
        if (data_[b / CELL_SIZE][b % CELL_SIZE]) {
            temp.set(b + shift);
        }
    }

    return temp;
}
