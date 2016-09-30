/*
 * Created by keldon on 30/09/16.
 */

#ifndef PIOUS_COUNT_CALLS_HPP
#define PIOUS_COUNT_CALLS_HPP


class CountCalls {
 public:
  CountCalls() { ++constructor_calls(); }
  CountCalls(const CountCalls &) { ++copy_calls(); }
  CountCalls &operator=(const CountCalls &) { ++assignment_calls(); }
  ~CountCalls() { ++destructor_calls(); }

  static int &constructor_calls() {
    static int val = 0;
    return val;
  }
  static int &destructor_calls() {
    static int val = 0;
    return val;
  }
  static int &copy_calls() {
    static int val = 0;
    return val;
  }
  static int &assignment_calls() {
    static int val = 0;
    return val;
  }

  static void ClearCount() {
    constructor_calls() = 0;
    destructor_calls() = 0;
    copy_calls() = 0;
    assignment_calls() = 0;
  }
};

#endif /* PIOUS_COUNT_CALLS_HPP */
