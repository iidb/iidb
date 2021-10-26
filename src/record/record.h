#pragma once

#include "field/fields.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace Neru {

typedef std::vector<FieldType> Header;

class Record {
public:
  Record() = default;

  explicit Record(std::vector<std::shared_ptr<Field>> &&fields);

  explicit Record(const std::vector<std::shared_ptr<Field>> &fields);

  Record(const uint8_t *src, const Header &head);

  void clear();

  Record &append(std::shared_ptr<Field> field);

  std::shared_ptr<Field> get(size_t pos) const;

  uint8_t *store(uint8_t *dst) const;

  const uint8_t *load(const uint8_t *src, const Header &head);

  size_t size() const;

  size_t length() const;

  Header head() const;

  std::string info() const;

  bool operator==(const Record &record) const;

  bool operator!=(const Record &record) const;

  friend std::ostream &operator<<(std::ostream &os, const Record &record);

private:
  std::vector<std::shared_ptr<Field>> _fields;
};

} // namespace Neru
