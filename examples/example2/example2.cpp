#include <niven/Timer.h>
#include <cstdint>
#include <ctime>
#include <iostream>

void nested_function() {
  NivenTimeFunction;
  for (unsigned int i = 0; i < 10000; i++) {
    double a = 2 * 2;
  }
}

void some_function() {
  NivenTimeFunction;
  for (unsigned int i = 0; i < 10000; i++) {
    double a = 2 * 2;
    nested_function();
  }
}

int main() {

  timer.start();
  {
    NivenTimeBlock("outside loop");
    for (unsigned int i = 0; i < 10000; i++) {
      NivenTimeBlock("loop");

      double a = 2 * 2;
    }
  }
  some_function();
  timer.end();
  timer.print();
  timer.dump_json("test.json");

  return 0;
}
