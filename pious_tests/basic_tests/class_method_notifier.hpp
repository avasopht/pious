/*
 * Created by keldon on 29/09/16.
 */

#ifndef PIOUS_CLASS_METHOD_NOTIFIER_HPP
#define PIOUS_CLASS_METHOD_NOTIFIER_HPP

class ClassMethodNotifier {
 public:
  virtual ~ClassMethodNotifier() {}

  virtual void Construct() = 0;
  virtual void Destruct() = 0;
  virtual void CopyConstruct() = 0;
  virtual void CopyAssign() = 0;
};

#endif /* PIOUS_CLASS_METHOD_NOTIFIER_HPP */
