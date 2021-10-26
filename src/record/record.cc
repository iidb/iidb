#include "record.h"

#include <utility>

namespace Neru {

Record::Record(std::vector<std::shared_ptr<Field>> &&fields)
    : _fields(std::move(fields)) {}

Record::Record(const std::vector<std::shared_ptr<Field>> &fields)
    : _fields(fields) {}

Record::Record(const uint8_t *src, const Header &head) {
  this->load(src, head);
}

void Record::clear() { _fields.clear(); }

Record &Record::append(std::shared_ptr<Field> field) {
  _fields.push_back(field);
  return *this;
}

std::shared_ptr<Field> Record::get(size_t pos) const { return _fields[pos]; }

uint8_t *Record::store(uint8_t *dst) const {
  uint8_t *pos = dst;
  for (const auto &field : _fields) {
    switch (field->type()) {
    case FieldType::INT:
      std::static_pointer_cast<IntField>(field)->store(pos);
      break;
    case FieldType::DOUBLE:
      std::static_pointer_cast<DoubleField>(field)->store(pos);
      break;
    default:
      __builtin_unreachable();
    }
    pos += field->size();
  }
  return pos;
}

const uint8_t *Record::load(const uint8_t *src, const Header &head) {
  this->clear();
  auto *pos = const_cast<uint8_t *>(src);
  for (const auto &type : head) {
    switch (type) {
    case FieldType::INT: {
      std::shared_ptr<IntField> field(new IntField(pos));
      _fields.push_back(std::static_pointer_cast<Field>(field));
      pos += field->size();
      break;
    }
    case FieldType::FLOAT: {
      std::shared_ptr<FloatField> field(new FloatField(pos));
      _fields.push_back(std::static_pointer_cast<Field>(field));
      pos += field->size();
      break;
    }
    case FieldType::DOUBLE: {
      std::shared_ptr<DoubleField> field(new DoubleField(pos));
      _fields.push_back(std::static_pointer_cast<Field>(field));
      pos += field->size();
      break;
    }
    default:
      __builtin_unreachable();
    }
  }
  return pos;
}

size_t Record::size() const {
  uint32_t size = 0;
  for (const auto &field : _fields)
    size += field->size();
  return size;
}

size_t Record::length() const { return _fields.size(); }

Header Record::head() const {
  Header head;
  for (const auto &field : _fields)
    head.push_back(field->type());
  return head;
}

std::string Record::info() const {
  std::string info;
  for (const auto &field : _fields)
    info += field->info() + '\n';
  info.pop_back();
  return info;
}

bool Record::operator==(const Record &record) const {
  if (length() != record.length())
    return false;
  for (size_t i = 0; i < length(); ++i)
    if (*get(i) != *record.get(i))
      return false;
  return true;
}

bool Record::operator!=(const Record &record) const {
  return !(*this == record);
}

std::ostream &operator<<(std::ostream &os, const Record &record) {
  return os << record.info();
}

} // namespace Neru
