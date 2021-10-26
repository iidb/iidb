#pragma once

#include "field.h"

namespace Neru {

class FloatField : public Field {
public:
  FloatField() = default;

  explicit FloatField(double data);

  explicit FloatField(const uint8_t *src);

  uint8_t *store(uint8_t *dst) const override;

  const uint8_t *load(const uint8_t *src) override;

  FieldType type() const override;

  size_t size() const override;

  std::string info() const override;

  bool operator==(const FloatField &field) const;

  bool operator!=(const FloatField &field) const;

  bool operator<(const FloatField &field) const;

  bool operator<=(const FloatField &field) const;

  bool operator>(const FloatField &field) const;

  bool operator>=(const FloatField &field) const;

  friend std::ostream &operator<<(std::ostream &os, const FloatField &field);

private:
  double _data{};
};

} // namespace Neru
