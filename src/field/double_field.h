#pragma once

#include "field.h"

namespace Neru {

class DoubleField : public Field {
public:
  DoubleField() = default;

  explicit DoubleField(double data);

  explicit DoubleField(const uint8_t *src);

  uint8_t *store(uint8_t *dst) const override;

  const uint8_t *load(const uint8_t *src) override;

  FieldType type() const override;

  size_t size() const override;

  std::string info() const override;

  bool operator==(const DoubleField &field) const;

  bool operator!=(const DoubleField &field) const;

  bool operator<(const DoubleField &field) const;

  bool operator<=(const DoubleField &field) const;

  bool operator>(const DoubleField &field) const;

  bool operator>=(const DoubleField &field) const;

  friend std::ostream &operator<<(std::ostream &os, const DoubleField &field);

private:
  double _data{};
};

} // namespace Neru
