#pragma once

#include "field.h"

namespace Neru {

class IntField : public Field {
public:
  IntField() = default;

  explicit IntField(int32_t data);

  explicit IntField(const uint8_t *src);

  uint8_t *store(uint8_t *dst) const override;

  const uint8_t *load(const uint8_t *src) override;

  FieldType type() const override;

  size_t size() const override;

  std::string info() const override;

  bool operator==(const IntField &field) const;

  bool operator!=(const IntField &field) const;

  bool operator<(const IntField &field) const;

  bool operator<=(const IntField &field) const;

  bool operator>(const IntField &field) const;

  bool operator>=(const IntField &field) const;

  friend std::ostream &operator<<(std::ostream &os, const IntField &field);

private:
  int32_t _data{};
};

} // namespace Neru
