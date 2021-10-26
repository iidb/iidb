#pragma once

#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "field/fields.h"
#include "record/record.h"
#include "table/table.h"

namespace Neru {

class Instance {
public:
  Instance(std::string path = "data");

  bool create(std::string tbName, Header header);

  bool drop(std::string tbName);

  bool test(size_t seed);

  std::string info() const;

  friend std::ostream &operator<<(std::ostream &os, const Instance &instance);

private:
  std::filesystem::path _dir;
  std::unordered_map<std::string, std::shared_ptr<Table>> _tables;
};

} // namespace Neru
