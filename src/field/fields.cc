#include "fields.h"

namespace Neru {

bool operator==(const Field &lhs, const Field &rhs) {
  FieldType type = lhs.type();
  if (type != rhs.type()) {
    // std::cerr << "Type Error" << std::endl;
    return false;
  }
  switch (type) {
  case FieldType::INT:
    return static_cast<const IntField &>(lhs) ==
           static_cast<const IntField &>(rhs);
  case FieldType::FLOAT:
    return static_cast<const FloatField &>(lhs) ==
           static_cast<const FloatField &>(rhs);
  case FieldType::DOUBLE:
    return static_cast<const DoubleField &>(lhs) ==
           static_cast<const DoubleField &>(rhs);
  case FieldType::STRING:
    return static_cast<const StringField &>(lhs) ==
           static_cast<const StringField &>(rhs);
  default:
    __builtin_unreachable();
  }
}

bool operator!=(const Field &lhs, const Field &rhs) {
  FieldType type = lhs.type();
  if (type != rhs.type()) {
    // std::cerr << "Type Error" << std::endl;
    return true;
  }
  switch (type) {
  case FieldType::INT:
    return static_cast<const IntField &>(lhs) !=
           static_cast<const IntField &>(rhs);
  case FieldType::FLOAT:
    return static_cast<const FloatField &>(lhs) !=
           static_cast<const FloatField &>(rhs);
  case FieldType::DOUBLE:
    return static_cast<const DoubleField &>(lhs) !=
           static_cast<const DoubleField &>(rhs);
  case FieldType::STRING:
    return static_cast<const StringField &>(lhs) !=
           static_cast<const StringField &>(rhs);
  default:
    __builtin_unreachable();
  }
}

bool operator<(const Field &lhs, const Field &rhs) {
  FieldType type = lhs.type();
  if (type != rhs.type()) {
    std::cerr << "Type Error" << std::endl;
    return false;
  }
  switch (type) {
  case FieldType::INT:
    return static_cast<const IntField &>(lhs) <
           static_cast<const IntField &>(rhs);
  case FieldType::FLOAT:
    return static_cast<const FloatField &>(lhs) <
           static_cast<const FloatField &>(rhs);
  case FieldType::DOUBLE:
    return static_cast<const DoubleField &>(lhs) <
           static_cast<const DoubleField &>(rhs);
  case FieldType::STRING:
    return static_cast<const StringField &>(lhs) <
           static_cast<const StringField &>(rhs);
  default:
    __builtin_unreachable();
  }
}

bool operator<=(const Field &lhs, const Field &rhs) {
  FieldType type = lhs.type();
  if (type != rhs.type()) {
    std::cerr << "Type Error" << std::endl;
    return false;
  }
  switch (type) {
  case FieldType::INT:
    return static_cast<const IntField &>(lhs) <=
           static_cast<const IntField &>(rhs);
  case FieldType::FLOAT:
    return static_cast<const FloatField &>(lhs) <=
           static_cast<const FloatField &>(rhs);
  case FieldType::DOUBLE:
    return static_cast<const DoubleField &>(lhs) <=
           static_cast<const DoubleField &>(rhs);
  case FieldType::STRING:
    return static_cast<const StringField &>(lhs) <=
           static_cast<const StringField &>(rhs);
  default:
    __builtin_unreachable();
  }
}

bool operator>(const Field &lhs, const Field &rhs) {
  FieldType type = lhs.type();
  if (type != rhs.type()) {
    std::cerr << "Type Error" << std::endl;
    return false;
  }
  switch (type) {
  case FieldType::INT:
    return static_cast<const IntField &>(lhs) >
           static_cast<const IntField &>(rhs);
  case FieldType::FLOAT:
    return static_cast<const FloatField &>(lhs) >
           static_cast<const FloatField &>(rhs);
  case FieldType::DOUBLE:
    return static_cast<const DoubleField &>(lhs) >
           static_cast<const DoubleField &>(rhs);
  case FieldType::STRING:
    return static_cast<const StringField &>(lhs) >
           static_cast<const StringField &>(rhs);
  default:
    __builtin_unreachable();
  }
}

bool operator>=(const Field &lhs, const Field &rhs) {
  FieldType type = lhs.type();
  if (type != rhs.type()) {
    std::cerr << "Type Error" << std::endl;
    return false;
  }
  switch (type) {
  case FieldType::INT:
    return static_cast<const IntField &>(lhs) >=
           static_cast<const IntField &>(rhs);
  case FieldType::FLOAT:
    return static_cast<const FloatField &>(lhs) >=
           static_cast<const FloatField &>(rhs);
  case FieldType::DOUBLE:
    return static_cast<const DoubleField &>(lhs) >=
           static_cast<const DoubleField &>(rhs);
  case FieldType::STRING:
    return static_cast<const StringField &>(lhs) >=
           static_cast<const StringField &>(rhs);
  default:
    __builtin_unreachable();
  }
}

std::ostream &operator<<(std::ostream &os, const Field &field) {
  switch (field.type()) {
  case FieldType::INT:
    return os << static_cast<const IntField &>(field);
  case FieldType::FLOAT:
    return os << static_cast<const FloatField &>(field);
  case FieldType::DOUBLE:
    return os << static_cast<const DoubleField &>(field);
  case FieldType::STRING:
    return os << static_cast<const StringField &>(field);
  default:
    __builtin_unreachable();
  }
}

} // namespace Neru
