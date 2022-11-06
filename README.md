# Bit vector for C++

---

[![License][license-shield]][license-link]

## Contents

- [Usage](#usage)
- [Features](#features)
  * [Constructors](#constructors)
  * [Assignment](#assignment)
  * [Element access](#element-access)
  * [Capacity](#capacity)
  * [Modifiers](#modifiers)
  * [Conversion](#conversion)
  * [Unary operators](#unary-operators)
  * [Binary operators](#binary-operators)
  * [Comparison](#comparison)
- [License](#license)

## Usage

1. Download the repository and put the contents of the [`include`](https://github.com/H1K0/bector/tree/master/include) folder to your include path. Then `#include` it in your code:
   ```c++
   #include "path/to/bector/bector.hpp"
   ```
2. Create objects of the `bector` class and do what you got to do!
   ```c++
   bector bect("11001010");
   std::cout << bect[4] << '\n';
   // Output: 1
   
   bect.flip();
   std::cout << bect.to_string() << '\n';
   // Output: 00110101
   ```

## Features

### Constructors

1. #### Default constructor
   ```c++
   bector() = default;
   ```
   Constructs an empty container.
2. #### Zeros constructor
   ```c++
   explicit bector(size_type count);
   ```
   Constructs the container with `count` zero bits.
3. #### Constructor with bool array
   ```c++
   explicit bector(const bool *array, size_t count);
   ```
   Constructs the container with the copy of the contents of `array`.
4. #### Constructor with bool vector
   ```c++
   explicit bector(const vector<bool> &vect) noexcept;
   ```
   Constructs the container with the copy of the contents of `vect`.
5. #### Constructor with string
   ```c++
   explicit bector(const std::string &str, char zero = '0', char one = '1');
   ```
   Constructs the container with the contents of `str` interpreting `one` and `zero` characters as `1` and `0` respectively. `str` must consist of only `one` and `zero` characters.
6. #### Copy constructor
   ```c++
   bector(const bector &other) = default;
   ```
   Constructs the container with the copy of the contents of `other`.
7. #### Move constructor
   ```c++
   bector(bector &&other) noexcept;
   ```
   Constructs the container with the contents of `other` using move semantics. `other` is guaranteed to be `empty()` afterwards.

### Assignment

1. #### Copy assignment
   ```c++
   bector &operator=(const bector &rhs) = default;
   ```
   Replaces the contents with a copy of the contents of `rhs`.
2. #### Move assignment
   ```c++
   bector &operator=(bector &&rhs) noexcept = default;
   ```
   Replaces the contents with those of other using move semantics. `rhs` is guaranteed to be `empty()` afterwards.

### Element access

1. #### Access a single bit
   ```c++
   bool operator[](size_type pos) const;
   ```
   Accesses the bit at position `pos` and returns the value.
2. #### Access the first bit
   ```c++
   bool front() const noexcept;
   ```
   Returns the value of the first bit in the container.
3. #### Access the last bit
   ```c++
   bool back() const noexcept;
   ```
   Returns the value of the last bit in the container.
4. #### Get slice
   ```c++
   bector slice(size_type start, size_type end) const;
   ```
   Returns a bector slice [start, end).
5. #### Bool operator
   ```c++
   explicit operator bool() const noexcept;
   ```
   Returns `true` if the container is not empty otherwise `false`.
6. #### `!` operator
   ```c++
   bool operator!() const noexcept;
   ```
   Returns `true` if the container is empty otherwise `false`.
7. #### All, any, none
   ```c++
   bool all() const noexcept;  // (1)
   bool any() const noexcept;  // (2)
   bool none() const noexcept; // (3)
   ```
   1) Checks if all bits are set to `true`.
   2) Checks if any bits are set to `true`.
   3) Checks if none of the bits are set to `true`.

### Capacity

1. #### Check if empty
   ```c++
   bool empty() const noexcept;
   ```
   Returns `true` if the container has no elements.
2. #### Get size
   ```c++
   size_type size() const noexcept;
   ```
   Returns the number of elements.
3. #### Get maximum size
   ```c++
   size_type max_size() const noexcept;
   ```
   Returns the maximum possible number of elements.
4. #### Get capacity
   ```c++
   size_type capacity() const noexcept;
   ```
   Returns the number of elements that can be held in currently allocated storage.
5. #### Reserve storage
   ```c++
   void reserve(size_type new_cap);
   ```
   Reserves storage for `new_cap` elements.
6. #### Resize container
   ```c++
   void resize(size_type count);
   ```
   Changes the number of elements stored to `count`.
7. #### Shrink to fit
   ```c++
   void shrink_to_fit();
   ```
   Reduces memory usage by freeing unused memory.

### Modifiers

1. #### Clear container
   ```c++
   void clear() noexcept;
   ```
   Clears the contents.
2. #### Push back bit
   ```c++
   void push_back(bool value = true);
   ```
   Adds an element to the end.
3. #### Pop back bit
   ```c++
   bool pop_back();
   ```
   Removes the last element.
4. #### Set bit(s)
   ```c++
   bector &set() noexcept;
   bector &set(size_type pos, bool value = true);
   bector &set(size_type start, size_type end, bool value);
   ```
   1) Sets all bits to `true`.
   2) Sets the bit at position `pos` to the value `value`.
   3) Sets the bits [start, end) to the value `value`.
5. #### Reset bit(s)
   ```c++
   bector &reset() noexcept;
   bector &reset(size_type pos);
   bector &reset(size_type start, size_type end);
   ```
   1) Sets all bits to `false`.
   2) Sets the bit at position `pos` to the `false`.
   3) Sets the bits [start, end) to `false`.
6. #### Flip bit(s)
   ```c++
   void flip() noexcept;
   void flip(size_type pos);
   void flip(size_type start, size_type end);
   ```
   1) Flips all bits.
   2) Flips the bit at position `pos`.
   3) Flips the bits [start, end).
7. #### Perform binary AND
   ```c++
   bector &operator&=(const bector &rhs) noexcept;
   ```
   Sets the bits to the result of binary AND on corresponding pairs of bits of `*this` and `rhs`.
8. #### Perform binary OR
   ```c++
   bector &operator|=(const bector &rhs) noexcept;
   ```
   Sets the bits to the result of binary OR on corresponding pairs of bits of `*this` and `rhs`.
9. #### Perform binary XOR
   ```c++
   bector &operator^=(const bector &rhs) noexcept;
   ```
   Sets the bits to the result of binary XOR on corresponding pairs of bits of `*this` and `rhs`.
10. #### Perform binary shift left
    ```c++
    bector &operator<<=(size_type shift) noexcept;
    ```
    Shifts all bits `shift` positions left.
10. #### Perform binary shift right
    ```c++
    bector &operator>>=(size_type shift) noexcept;
    ```
    Shifts all bits `shift` positions right.

### Conversion

1. #### To string
   ```c++
   std::string to_string(char zero = '0', char one = '1') const noexcept;
   ```
   Converts the contents of the bector to a string. Uses `zero` to represent bits with value of `false` and `one` to represent bits with value of `true`.

### Unary operators

1. #### Binary NOT
   ```c++
   bector operator~() const noexcept;
   ```
   Returns a temporary copy of `*this` with all bits flipped.

### Binary operators

1. #### Binary AND
   ```c++
   bector operator&(const bector &rhs) const noexcept;
   ```
   Returns a bector containing the result of binary AND on corresponding pairs of bits of lhs and rhs.
2. #### Binary OR
   ```c++
   bector operator|(const bector &rhs) const noexcept;
   ```
   Returns a bector containing the result of binary OR on corresponding pairs of bits of lhs and rhs.
3. #### Binary XOR
   ```c++
   bector operator^(const bector &rhs) const noexcept;
   ```
   Returns a bector containing the result of binary XOR on corresponding pairs of bits of lhs and rhs.
4. #### Binary shift left
   ```c++
   bector operator<<(size_type shift) const noexcept;
   ```
   Returns a temporary copy of `*this` with all bits shifted `shift` positions left.
5. #### Binary shift right
   ```c++
   bector operator>>(size_type shift) const noexcept;
   ```
   Returns a temporary copy of `*this` with all bits shifted `shift` positions right.

### Comparison

1. LHS **equals** RHS if both bectors are of the same size and contain the same bits on the same positions.
2. LHS **not equals** RHS if bectors are of different sizes or contain different bits on the same potitions.
3. LHS is **less than** RHS if LHS is smaller in size or represents a smaller integer than RHS for the same size.
4. LHS is **less than or equal to** RHS if LHS is smaller in size or represents a smaller or the same integer as RHS for the same size.
5. LHS is **greater than** RHS if LHS is larger in size or represents a larger integer than RHS for the same size.
6. LHS is **greater than or equal to** RHS if LHS is larger in size or represents a larger or the same integer as RHS for the same size.

## License

This project is licensed under the terms of the [MIT license][license-link].

[license-shield]: https://img.shields.io/github/license/H1K0/bector.svg?style=for-the-badge
[license-link]: https://github.com/H1K0/bector/blob/master/LICENSE
