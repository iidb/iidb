#pragma once

#include "record/record.h"

namespace Neru {

typedef std::pair<size_t, size_t> Entry;

class Table {
public:
  Table() = delete;

  Table(std::string name, Header head);

  Table(const uint8_t *src);

  Entry insert(std::shared_ptr<Record> record);

  bool update(Entry dst, std::shared_ptr<Record> record);

  bool remove(Entry dst);

  std::vector<std::shared_ptr<Record>> select();

  Header head() const;

  size_t size() const;

  std::string info() const;

  friend std::ostream &operator<<(std::ostream &os, const Table &table);

private:
  std::string _name;

  Header _head;

  const uint8_t *load(const uint8_t *src);

  uint8_t *store(uint8_t *dst) const;
};

} // namespace Neru
