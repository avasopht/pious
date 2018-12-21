//
// Created by keldon on 21/12/18.
//
#include <cstring>

#include "literal.hpp"
namespace emcee {

Literal::Literal(const char *literal, size_t length) : literal_(literal), length_(length) { }

Literal Literal::CreateIfReallyLiteral(const char *literal,
                 size_t length,
                 std::true_type,
                 std::false_type,
                 std::false_type,
                 std::false_type,
                 std::false_type) {
  return {literal, length};
}

size_t Literal::length() const { return length_; }
const char *Literal::c_str() const { return literal_; }
bool Literal::operator<(const Literal &rhs) const {
  const Literal &lhs = *this;
  return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}
bool Literal::operator==(const Literal &rhs) const {
  const Literal &lhs = *this;
  return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

}