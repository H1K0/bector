#include "bector.hpp"

void bector::clear() noexcept {
    data_.clear();
    bitoffset_ = 0;
}

void bector::push_back(bool value) {
    if (size() == max_size()) {
        throw std::length_error("");
    }
    if (bitoffset_ == CELL_SIZE - 1) {
        data_.back().set(bitoffset_, value);
        bitoffset_ = 0;
    } else {
        if (!bitoffset_) {
            data_.emplace_back(0);
        }
        data_.back().set(bitoffset_++, value);
    }
}

bool bector::pop_back() {
    bool out = this->back();
    if (bitoffset_) {
        if (!--bitoffset_) {
            data_.pop_back();
        } else {
            data_.back().reset(bitoffset_);
        }
    } else {
        bitoffset_ = CELL_SIZE - 1;
        data_.back().reset(bitoffset_ - 1);
    }

    return out;
}

bector &bector::set() noexcept {
    for (size_type c = 0; c < data_.size() - 1; c++) {
        data_[c].set();
    }
    for (unsigned char b = 0; b < bitoffset_; b++) {
        data_.back().set(b);
    }

    return *this;
}

bector &bector::set(size_t pos, bool value) {
    if (pos >= size()) {
        throw std::out_of_range("");
    }
    data_[pos / CELL_SIZE].set(pos % CELL_SIZE, value);

    return *this;
}

bector &bector::set(size_type start, size_type end, bool value) {
    if (start >= size() | end >= size()) {
        throw std::out_of_range("");
    }
    if (end == SIZE_MAX && size() < SIZE_MAX) {
        end = size();
    }
    if (start / CELL_SIZE == end / CELL_SIZE) {
        for (unsigned char b = start; b < end; b++) {
            data_[start / CELL_SIZE].set(b, value);
        }
    } else {
        if (start % CELL_SIZE) {
            for (unsigned char b = start; b < CELL_SIZE; b++) {
                data_[start / CELL_SIZE].set(b, value);
            }
            start += CELL_SIZE - start % CELL_SIZE;
        }
        if (end % CELL_SIZE) {
            for (unsigned char b = 0; b < end; b++) {
                data_[end / CELL_SIZE].set(b, value);
            }
            end -= end % CELL_SIZE;
        }
        start /= CELL_SIZE;
        end /= CELL_SIZE;
        for (size_type c = start; c <= end; c++) {
            if (value) {
                data_[c].set();
            } else {
                data_[c].reset();
            }
        }
    }

    return *this;
}

bector &bector::reset() noexcept {
    for (size_type c = 0; c < data_.size() - 1; c++) {
        data_[c].reset();
    }
    for (unsigned char b = 0; b < bitoffset_; b++) {
        data_.back().reset(b);
    }

    return *this;
}

bector &bector::reset(size_t pos) {
    if (pos >= size()) {
        throw std::out_of_range("");
    }
    data_[pos / CELL_SIZE].reset(pos % CELL_SIZE);

    return *this;
}

bector &bector::reset(size_type start, size_type end) {
    if (start >= size() | end >= size()) {
        throw std::out_of_range("");
    }
    if (size() < SIZE_MAX && end == SIZE_MAX) {
        end = size();
    }
    if (start / CELL_SIZE == end / CELL_SIZE) {
        for (unsigned char b = start; b < end; b++) {
            data_[start / CELL_SIZE].reset(b);
        }
    } else {
        if (start % CELL_SIZE) {
            for (unsigned char b = start; b < CELL_SIZE; b++) {
                data_[start / CELL_SIZE].set(b);
            }
            start += CELL_SIZE - start % CELL_SIZE;
        }
        if (end % CELL_SIZE) {
            for (unsigned char b = 0; b < end; b++) {
                data_[end / CELL_SIZE].set(b);
            }
            end -= end % CELL_SIZE;
        }
        start /= CELL_SIZE;
        end /= CELL_SIZE;
        for (size_type c = start; c <= end; c++) {
            data_[c].reset();
        }
    }

    return *this;
}

void bector::flip() noexcept {
    for (size_type c = 0; c < data_.size() - 1; c++) {
        data_[c].flip();
    }
    for (unsigned char b = 0; b < bitoffset_; b++) {
        data_.back().flip(b);
    }
}

void bector::flip(size_t pos) {
    if (pos >= size()) {
        throw std::out_of_range("");
    }
    data_[pos / CELL_SIZE].flip(pos % CELL_SIZE);
}

void bector::flip(size_type start, size_type end) {
    if (start >= size() | end >= size()) {
        throw std::out_of_range("");
    }
    if (size() < SIZE_MAX && end == SIZE_MAX) {
        end = size();
    }
    if (start / CELL_SIZE == end / CELL_SIZE) {
        for (unsigned char b = start; b < end; b++) {
            data_[start / CELL_SIZE].flip(b);
        }
    } else {
        if (start % CELL_SIZE) {
            for (unsigned char b = start; b < CELL_SIZE; b++) {
                data_[start / CELL_SIZE].flip(b);
            }
            start += CELL_SIZE - start % CELL_SIZE;
        }
        if (end % CELL_SIZE) {
            for (unsigned char b = 0; b < end; b++) {
                data_[end / CELL_SIZE].flip(b);
            }
            end -= end % CELL_SIZE;
        }
        start /= CELL_SIZE;
        end /= CELL_SIZE;
        for (size_type c = start; c <= end; c++) {
            data_[c].flip();
        }
    }
}

bector &bector::operator&=(const bector &rhs) noexcept {
    for (size_type c = 0; c < std::min(data_.size(), rhs.data_.size()); c++) {
        data_[c] &= rhs.data_[c];
    }
    if (size() > rhs.size()) {
        for (size_type c = rhs.data_.size(); c < data_.size(); c++) {
            data_[c].reset();
        }
    }

    return *this;
}

bector &bector::operator|=(const bector &rhs) noexcept {
    for (size_type c = 0; c < std::min(data_.size(), rhs.data_.size()); c++) {
        data_[c] |= rhs.data_[c];
    }

    return *this;
}

bector &bector::operator^=(const bector &rhs) noexcept {
    for (size_type c = 0; c < std::min(data_.size(), rhs.data_.size()); c++) {
        data_[c] ^= rhs.data_[c];
    }

    return *this;
}

bector &bector::operator<<=(size_type shift) noexcept {
    if (!shift) {
        return *this;
    }
    if (shift >= size()) {
        return reset();
    }
    for (size_type b = 0; b < size(); b++) {
        if (b < size() - shift) {
            data_[b / CELL_SIZE].set(b % CELL_SIZE, data_[(b + shift) / CELL_SIZE][(b + shift) % CELL_SIZE]);
        } else {
            data_[b / CELL_SIZE].reset(b % CELL_SIZE);
        }
    }

    return *this;
}

bector &bector::operator>>=(size_type shift) noexcept {
    if (!shift) {
        return *this;
    }
    if (shift >= size()) {
        return reset();
    }
    for (size_type b = size() - 1; b < size(); --b) {
        if (b >= shift) {
            data_[b / CELL_SIZE].set(b % CELL_SIZE, data_[(b - shift) / CELL_SIZE][(b - shift) % CELL_SIZE]);
        } else {
            data_[b / CELL_SIZE].reset(b % CELL_SIZE);
        }
    }

    return *this;
}
