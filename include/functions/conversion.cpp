#include "bector.hpp"

std::string bector::to_string(char zero, char one) const noexcept {
    if (!size()) {
        return "";
    }
    std::string out;
    out.reserve(size());
    for (size_type c = 0; c < data_.size() - 1; c++) {
        for (unsigned char b = 0; b < CELL_SIZE; b++) {
            out.push_back(data_[c][b] ? one : zero);
        }
    }
    for (unsigned char b = 0; b < bitoffset_; b++) {
        out.push_back(data_.back()[b] ? one : zero);
    }

    return out;
}
