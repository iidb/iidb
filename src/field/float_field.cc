#include "float_field.h"

namespace Neru {

FloatField::FloatField(double data) : _data(data) {}

FloatField::FloatField(const uint8_t *src) { this->load(src); }

uint8_t *FloatField::store(uint8_t *dst) const {
  auto *src = (const uint8_t *)&_data;
  std::copy_n(src, this->size(), dst);
  return dst + this->size();
}

const uint8_t *FloatField::load(const uint8_t *src) {
  auto *dst = (uint8_t *)&_data;
  std::copy_n(src, this->size(), dst);
  return src + this->size();
}

FieldType FloatField::type() const { return FieldType::FLOAT; }

size_t FloatField::size() const { return sizeof(double); }

std::string FloatField::info() const {
  return std::to_string(this->size()) +
         "\tFloatField: " + std::to_string(_data);
}

bool FloatField::operator==(const FloatField &field) const {
  return _data == field._data;
}

bool FloatField::operator!=(const FloatField &field) const {
  return _data != field._data;
}

bool FloatField::operator<(const FloatField &field) const {
  return _data < field._data;
}

bool FloatField::operator<=(const FloatField &field) const {
  return _data <= field._data;
}

bool FloatField::operator>(const FloatField &field) const {
  return _data > field._data;
}

bool FloatField::operator>=(const FloatField &field) const {
  return _data >= field._data;
}

std::ostream &operator<<(std::ostream &os, const FloatField &field) {
  return os << field.info();
}

} // namespace Neru
