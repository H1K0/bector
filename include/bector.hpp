#ifndef BECTOR_LIBRARY
#define BECTOR_LIBRARY
#define BECTOR_API __declspec(dllexport)
#else
#define BECTOR_API __declspec(dllimport)
#endif

#include <cstdint>
#include <bitset>
#include <vector>
#include <stdexcept>

#define CELL_SIZE 32

typedef std::bitset<CELL_SIZE> cell;
typedef size_t size_type;
using std::vector;

class BECTOR_API bector {
private:
    unsigned char bitoffset_ = 0;
    vector<cell> data_;
public:
    bector() = default;
    explicit bector(size_type count);
    explicit bector(const bool *array, size_t count);
    explicit bector(const vector<bool> &vect) noexcept;
    explicit bector(const std::string &str, char zero = '0', char one = '1');
    bector(const bector &other) = default;
    bector(bector &&other) noexcept;

    bector &operator=(const bector &rhs) = default;
    bector &operator=(bector &&rhs) noexcept = default;

    bool operator[](size_type pos) const;
    bool front() const noexcept;
    bool back() const noexcept;
    bector slice(size_type start, size_type end) const;
    explicit operator bool() const noexcept;
    bool operator!() const noexcept;
    bool all() const noexcept;
    bool any() const noexcept;
    bool none() const noexcept;

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    size_type capacity() const noexcept;
    void reserve(size_type new_cap);
    void resize(size_type count);
    void shrink_to_fit();

    void clear() noexcept;
    void push_back(bool value = true);
    bool pop_back();
    bector &set() noexcept;
    bector &set(size_type pos, bool value = true);
    bector &set(size_type start, size_type end, bool value);
    bector &reset() noexcept;
    bector &reset(size_type pos);
    bector &reset(size_type start, size_type end);
    void flip() noexcept;
    void flip(size_type pos);
    void flip(size_type start, size_type end);
    bector &operator&=(const bector &rhs) noexcept;
    bector &operator|=(const bector &rhs) noexcept;
    bector &operator^=(const bector &rhs) noexcept;
    bector &operator<<=(size_type shift) noexcept;
    bector &operator>>=(size_type shift) noexcept;

    std::string to_string(char zero = '0', char one = '1') const noexcept;

    bector operator~() const noexcept;

    bector operator&(const bector &rhs) const noexcept;
    bector operator|(const bector &rhs) const noexcept;
    bector operator^(const bector &rhs) const noexcept;
    bector operator<<(size_type shift) const noexcept;
    bector operator>>(size_type shift) const noexcept;

    bool operator==(const bector &rhs) const noexcept;
    bool operator!=(const bector &rhs) const noexcept;
    bool operator<(const bector &rhs) const noexcept;
    bool operator<=(const bector &rhs) const noexcept;
    bool operator>(const bector &rhs) const noexcept;
    bool operator>=(const bector &rhs) const noexcept;
};
