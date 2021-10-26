#include "instance.h"

namespace Neru {

Instance::Instance(std::string path) : _dir(path) {
  std::cout << _dir << std::endl;
  if (!std::filesystem::exists(_dir))
    std::filesystem::create_directories(_dir);
  for (const auto &dir_entry : std::filesystem::directory_iterator(_dir))
    // TODO
    std::cout << dir_entry.path() << std::endl;
}

bool Instance::create(std::string tbName, Header header) {
  if (std::filesystem::exists(_dir / tbName))
    return false;
  std::filesystem::create_directories(_dir / tbName);
  // TODO
  _tables[tbName] = nullptr;
  return true;
}

bool Instance::drop(std::string tbName) {
  if (!std::filesystem::exists(_dir / tbName))
    return false;
  std::filesystem::remove_all(_dir / tbName);
  _tables.erase(tbName);
  return true;
}

std::string Instance::info() const {
  std::string info = "Instance:";
  for (const auto &kv : _tables)
    info += "\n\t" + kv.first;
  return info;
}

std::ostream &operator<<(std::ostream &os, const Instance &instance) {
  return os << instance.info();
}

bool Instance::test(size_t seed) {
  srand(seed);
  assert(create("foo", {FieldType::INT, FieldType::INT, FieldType::FLOAT}));
  assert(create("bar", {FieldType::INT, FieldType::STRING}));
  assert(_tables["foo"]);
  assert(_tables["bar"]);
  return true;
}

} // namespace Neru
