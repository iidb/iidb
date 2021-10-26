#pragma once

#include <algorithm>
#include <iostream>
#include <string>

namespace Neru {

enum class FieldType { INT, FLOAT, DOUBLE, STRING };

class Field {
public:
  virtual uint8_t *store(uint8_t *dst) const = 0;

  virtual const uint8_t *load(const uint8_t *src) = 0;

  virtual FieldType type() const = 0;

  virtual size_t size() const = 0;

  virtual std::string info() const = 0;

  friend std::ostream &operator<<(std::ostream &os, const Field &field);
};

} // namespace Neru
