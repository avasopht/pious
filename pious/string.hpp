/*
 * Created by keldon on 17/08/16.
 */

#ifndef PIOUS_STRING_H
#define PIOUS_STRING_H

namespace pious {

class Os;

class String {
 public:
  String(Os &os, const char *string);
  String(String &other);
  String(const String &first, const String &second);
  String& operator=(String &rhs);
};

String operator+(const String &first, const String &second);

}

#endif /* PIOUS_STRING_H */
