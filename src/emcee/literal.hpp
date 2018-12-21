//
// Created by keldon on 21/12/18.
//

#ifndef PIOUS_LITERAL_HPP
#define PIOUS_LITERAL_HPP

#include <cstddef>
#include <boost/type_traits.hpp>


// Based on macro from https://stackoverflow.com/a/14805137
/**! \brief Converts string literals into objects but fails with non-literal strings.
 *
 */
#define LITERAL(message)\
    emcee::Literal::CreateIfReallyLiteral\
      (\
        message, \
        sizeof(message)-1,\
        std::is_convertible      <decltype(message), const char *>(),\
        std::is_rvalue_reference <decltype(message)>(),\
        std::is_pointer          <decltype(message)>(),\
        std::is_array            <decltype(message)>(),\
        std::is_class            <decltype(message)>()\
    );

namespace emcee {

class Literal {
 public:

  //! Do not call directly, use LITERAL Macro.
  static Literal CreateIfReallyLiteral(const char *literal,
                                       size_t size,
                                       std::true_type,
                                       std::false_type,
                                       std::false_type,
                                       std::false_type,
                                       std::false_type);

  //! Do not call directly
  static Literal CreateIfReallyLiteral(const char *str, ...) = delete;

  size_t length() const;
  const char *c_str() const;

  bool operator==(const Literal &rhs) const;
  bool operator<(const Literal &rhs) const;

 private:

  Literal(const char *literal, size_t length);
  const char *literal_;
  size_t length_;
};

}

#endif //PIOUS_LITERAL_HPP
