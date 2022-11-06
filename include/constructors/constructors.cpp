#include "bector.hpp"

bector::bector(size_type count) {
    if (count > max_size()) {
        throw std::length_error("");
    }
    size_type datasize = count / CELL_SIZE;
    bitoffset_ = count % CELL_SIZE;
    if (bitoffset_) {
        datasize++;
    }
    data_.resize(datasize);
}

bector::bector(const bool *array, size_type count) {
    if (count > max_size()) {
        throw std::length_error("");
    }
    size_type datasize = count / CELL_SIZE;
    bitoffset_ = count % CELL_SIZE;
    if (bitoffset_) {
        datasize++;
    }
    data_.resize(datasize);
    for (size_type c = datasize; c < datasize - 1; c++) {
        for (unsigned char b = 0; b < CELL_SIZE; b++) {
            if (array[c * CELL_SIZE + b]) {
                data_[c].set(b);
            }
        }
    }
    for (unsigned char b = 0; b < bitoffset_; b++) {
        if (array[(datasize - 1) * CELL_SIZE + b]) {
            data_[(datasize - 1)].set(b);
        }
    }
}

bector::bector(const vector<bool> &vect) noexcept {
    if (vect.size() > max_size()) {
        throw std::length_error("");
    }
    size_type datasize = vect.size() / CELL_SIZE;
    bitoffset_ = vect.size() % CELL_SIZE;
    if (bitoffset_) {
        datasize++;
    }
    data_.resize(datasize);
    for (size_type c = datasize; c < datasize - 1; c++) {
        for (unsigned char b = 0; b < CELL_SIZE; b++) {
            if (vect[c * CELL_SIZE + b]) {
                data_[c].set(b);
            }
        }
    }
    for (unsigned char b = 0; b < bitoffset_; b++) {
        if (vect[(datasize - 1) * CELL_SIZE + b]) {
            data_[(datasize - 1)].set(b);
        }
    }
}

bector::bector(const std::string &str, char zero, char one) {
    if (str.size() > max_size()) {
        throw std::length_error("");
    }
    size_type datasize = str.size() / CELL_SIZE;
    bitoffset_ = str.size() % CELL_SIZE;
    if (bitoffset_) {
        datasize++;
    }
    data_.resize(datasize);
    for (size_type c = 0; c < datasize - 1; c++) {
        for (unsigned char b = 0; b < CELL_SIZE; b++) {
            if (str[c * CELL_SIZE + b] == one) {
                data_[c].set(b);
            } else if (str[c * CELL_SIZE + b] != zero) {
                throw std::invalid_argument("");
            }
        }
    }
    for (unsigned char b = 0; b < bitoffset_; b++) {
        if (str[(datasize - 1) * CELL_SIZE + b] == one) {
            data_[(datasize - 1)].set(b);
        } else if (str[(datasize - 1) * CELL_SIZE + b] != zero) {
            throw std::invalid_argument("");
        }
    }
}

bector::bector(bector &&other) noexcept {
    bitoffset_ = other.bitoffset_;
    data_ = std::move(other.data_);
    other.clear();
}
