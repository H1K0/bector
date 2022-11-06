#include "bector.hpp"

bool bector::operator==(const bector &rhs) const noexcept {
    if (size() != rhs.size()) {
        return false;
    }
    for (size_type b = 0; b < size(); b++) {
        if ((*this)[b] ^ rhs[b]) {
            return false;
        }
    }

    return true;
}

bool bector::operator!=(const bector &rhs) const noexcept {
    if (size() != rhs.size()) {
        return true;
    }
    for (size_type b = 0; b < size(); b++) {
        if ((*this)[b] ^ rhs[b]) {
            return true;
        }
    }

    return false;
}

bool bector::operator<(const bector &rhs) const noexcept {
    if (size() < rhs.size()) {
        return true;
    } else if (size() > rhs.size()) {
        return false;
    }
    for (size_type b = 0; b < size(); b++) {
        if ((*this)[b] && !rhs[b]) {
            return false;
        } else if (!(*this)[b] && rhs[b]) {
            return true;
        }
    }

    return false;
}

bool bector::operator<=(const bector &rhs) const noexcept {
    if (size() < rhs.size()) {
        return true;
    } else if (size() > rhs.size()) {
        return false;
    }
    for (size_type b = 0; b < size(); b++) {
        if ((*this)[b] && !rhs[b]) {
            return false;
        } else if (!(*this)[b] && rhs[b]) {
            return true;
        }
    }

    return true;
}

bool bector::operator>(const bector &rhs) const noexcept {
    if (size() > rhs.size()) {
        return true;
    } else if (size() < rhs.size()) {
        return false;
    }
    for (size_type b = 0; b < size(); b++) {
        if ((*this)[b] && !rhs[b]) {
            return true;
        } else if (!(*this)[b] && rhs[b]) {
            return false;
        }
    }

    return false;
}

bool bector::operator>=(const bector &rhs) const noexcept {
    if (size() > rhs.size()) {
        return true;
    } else if (size() < rhs.size()) {
        return false;
    }
    for (size_type b = 0; b < size(); b++) {
        if ((*this)[b] && !rhs[b]) {
            return true;
        } else if (!(*this)[b] && rhs[b]) {
            return false;
        }
    }

    return true;
}
