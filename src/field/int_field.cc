#include "int_field.h"

namespace Neru {

IntField::IntField(int32_t data) : _data(data) {}

IntField::IntField(const uint8_t *src) { this->load(src); }

uint8_t *IntField::store(uint8_t *dst) const {
  const auto *src = (const uint8_t *)&_data;
  std::copy_n(src, this->size(), dst);
  return dst + this->size();
}

const uint8_t *IntField::load(const uint8_t *src) {
  auto *dst = (uint8_t *)&_data;
  std::copy_n(src, this->size(), dst);
  return src + this->size();
}

FieldType IntField::type() const { return FieldType::INT; }

size_t IntField::size() const { return sizeof(int32_t); }

std::string IntField::info() const {
  return std::to_string(this->size()) + "\tIntField: " + std::to_string(_data);
}

bool IntField::operator==(const IntField &field) const {
  return _data == field._data;
}

bool IntField::operator!=(const IntField &field) const {
  return _data != field._data;
}

bool IntField::operator<(const IntField &field) const {
  return _data < field._data;
}

bool IntField::operator<=(const IntField &field) const {
  return _data <= field._data;
}

bool IntField::operator>(const IntField &field) const {
  return _data > field._data;
}

bool IntField::operator>=(const IntField &field) const {
  return _data >= field._data;
}

std::ostream &operator<<(std::ostream &os, const IntField &field) {
  return os << field.info();
}

} // namespace Neru
