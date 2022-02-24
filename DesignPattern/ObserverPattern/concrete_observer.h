
#ifndef DESIGNPATTERN_CONCRETE_OBSERVER_H
#define DESIGNPATTERN_CONCRETE_OBSERVER_H

#include <iostream>
#include <string>

#include "observer.h"

class ConcreteObserver : public IObserver {
 public:
  ConcreteObserver(std::string name) { m_strName = name; }
  void Update(float price) {
    std::cout << m_strName << " - price" << price << "\n";
  }

 private:
  std::string m_strName;  // name
};

#endif  // DESIGNPATTERN_CONCRETE_OBSERVER_H
