#include "double_field.h"

namespace Neru {

DoubleField::DoubleField(double data) : _data(data) {}

DoubleField::DoubleField(const uint8_t *src) { this->load(src); }

uint8_t *DoubleField::store(uint8_t *dst) const {
  auto *src = (const uint8_t *)&_data;
  std::copy_n(src, this->size(), dst);
  return dst + this->size();
}

const uint8_t *DoubleField::load(const uint8_t *src) {
  auto *dst = (uint8_t *)&_data;
  std::copy_n(src, this->size(), dst);
  return src + this->size();
}

FieldType DoubleField::type() const { return FieldType::DOUBLE; }

size_t DoubleField::size() const { return sizeof(double); }

std::string DoubleField::info() const {
  return std::to_string(this->size()) +
         "\tDoubleField: " + std::to_string(_data);
}

bool DoubleField::operator==(const DoubleField &field) const {
  return _data == field._data;
}

bool DoubleField::operator!=(const DoubleField &field) const {
  return _data != field._data;
}

bool DoubleField::operator<(const DoubleField &field) const {
  return _data < field._data;
}

bool DoubleField::operator<=(const DoubleField &field) const {
  return _data <= field._data;
}

bool DoubleField::operator>(const DoubleField &field) const {
  return _data > field._data;
}

bool DoubleField::operator>=(const DoubleField &field) const {
  return _data >= field._data;
}

std::ostream &operator<<(std::ostream &os, const DoubleField &field) {
  return os << field.info();
}

} // namespace Neru
