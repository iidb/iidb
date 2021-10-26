#include "table.h"

namespace Neru {

Table::Table(std::string name, Header head) : _name(name), _head(head) {}

Table::Table(const uint8_t *src) { this->load(src); }

uint8_t *Table::store(uint8_t *dst) const {
  // TODO
  return nullptr;
}

const uint8_t *Table::load(const uint8_t *src) {
  // TODO
  return nullptr;
}

Header Table::head() const { return _head; }

size_t Table::size() const { return _head.size(); }

std::string Table::info() const {
  std::string info = "Table:\n\t" + _name + "\n\tFields:";
  for (const auto &head : _head)
    switch (head) {
    case FieldType::INT:
      info += "\n\t\tIntField";
      break;
    case FieldType::FLOAT:
      info += "\n\t\tFloatField";
      break;
    case FieldType::DOUBLE:
      info += "\n\t\tDoubleField";
      break;
    case FieldType::STRING:
      info += "\n\t\tStringField";
    default:
      __builtin_unreachable();
    }
  return info;
}

std::ostream &operator<<(std::ostream &os, const Table &table) {
  return os << table.info();
}

Entry Table::insert(std::shared_ptr<Record> record) {
  // TODO
  return {0, 0};
}

bool Table::update(Entry dst, std::shared_ptr<Record> record) {
  // TODO
  return false;
}

bool Table::remove(Entry dst) {
  // TODO
  return false;
}

std::vector<std::shared_ptr<Record>> Table::select() {
  // TODO
  return {};
}

} // namespace Neru
