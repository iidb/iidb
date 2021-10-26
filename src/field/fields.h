#pragma once

#include "double_field.h"
#include "float_field.h"
#include "int_field.h"
#include "string_field.h"

namespace Neru {

bool operator==(const Field &lhs, const Field &rhs);

bool operator!=(const Field &lhs, const Field &rhs);

bool operator<(const Field &lhs, const Field &rhs);

bool operator<=(const Field &lhs, const Field &rhs);

bool operator>(const Field &lhs, const Field &rhs);

bool operator>=(const Field &lhs, const Field &rhs);

} // namespace Neru
