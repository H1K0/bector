#include "bector.hpp"

bool bector::empty() const noexcept {
    return data_.empty();
}

size_type bector::size() const noexcept {
    return (data_.size() - (bool) bitoffset_) * CELL_SIZE + bitoffset_;
}

size_type bector::max_size() const noexcept {
    return data_.max_size() * CELL_SIZE;
}

size_type bector::capacity() const noexcept {
    return data_.capacity() * CELL_SIZE;
}

void bector::reserve(size_type new_cap) {
    size_type datasize = new_cap / CELL_SIZE;
    if (new_cap % CELL_SIZE) {
        datasize++;
    }
    data_.reserve(datasize);
}

void bector::resize(size_type count) {
    if (count > max_size()) {
        throw std::length_error("");
    }
    if (count / CELL_SIZE + (bool) (count % CELL_SIZE) != data_.size()) {
        data_.resize(count / CELL_SIZE + (bool) (count % CELL_SIZE));
    }
    count %= CELL_SIZE;
    if (count) {
        for (unsigned char b = count; b < CELL_SIZE; b++) {
            data_.back().reset(b);
        }
    }
    bitoffset_ = count;
}

void bector::shrink_to_fit() {
    data_.shrink_to_fit();
}
