#include "bector.hpp"

bool bector::operator[](size_type pos) const {
    if (pos >= size()) {
        throw std::out_of_range("");
    }
    return data_[pos / CELL_SIZE][pos % CELL_SIZE];
}

bool bector::front() const noexcept {
    return data_.front()[0];
}

bool bector::back() const noexcept {
    return data_.back()[bitoffset_ - 1];
}

bector bector::slice(size_type start, size_type end) const {
    if (start >= size() || end > size()) {
        throw std::out_of_range("");
    }
    if (start > end) {
        return slice(end, start);
    }
    if (start == end) {
        return {};
    }
    bector temp;
    temp.resize(end - start);
    for (size_type b = 0; b < end - start; b++) {
        temp.data_[b / CELL_SIZE].set(b, data_[(start + b) / CELL_SIZE][(start + b) % CELL_SIZE]);
    }

    return temp;
}

bector::operator bool() const noexcept {
    for (auto c: data_) {
        if (c.any()) {
            return true;
        }
    }

    return false;
}

bool bector::operator!() const noexcept {
    for (auto c: data_) {
        if (c.any()) {
            return false;
        }
    }

    return true;
}

bool bector::all() const noexcept {
    for (size_type c = 0; c < data_.size() - 1; c++) {
        if (!data_[c].all()) {
            return false;
        }
    }
    for (unsigned char b = 0; b < bitoffset_; b++) {
        if (!data_.back()[b]) {
            return false;
        }
    }

    return true;
}

bool bector::any() const noexcept {
    for (auto c: data_) {
        if (c.any()) {
            return true;
        }
    }

    return false;
}

bool bector::none() const noexcept {
    for (auto c: data_) {
        if (c.any()) {
            return false;
        }
    }

    return true;
}
