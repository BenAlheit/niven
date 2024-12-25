# Niven

A light-weight C++ profiling tool. 


<!-- ![alt text](https://github.com/BenAlheit/niven/blob/main/resources/niven.png?raw=true) -->

<p align="center">
  <img src="https://github.com/BenAlheit/niven/blob/main/resources/niven.png?raw=true" alt="Niven image"/>
</p>

## Minimal usage example


```C++
#include "Timer.h"

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
  timer.dump_json("profile_data.json");

  return 0;
}
```

Will result in an output (in stdout because of `timer.print()` and `profile_data.json` because of `timer.dump_json("profile_data.json")`) of
```
{
"label": "total",
"n_calls": 1,
"nanoseconds": 1046132,
"pct_of_parent": 100,
"children": [
        {
        "label": "outside loop",
        "n_calls": 1,
        "nanoseconds": 528704,
        "pct_of_parent": 50,
        "children": [
                {
                "label": "loop",
                "n_calls": 10000,
                "nanoseconds": 199672,
                "pct_of_parent": 37,
                "children": [ ]
                }
        ]
        },
        {
        "label": "some_function",
        "n_calls": 1,
        "nanoseconds": 515028,
        "pct_of_parent": 49,
        "children": [
                {
                "label": "nested_function",
                "n_calls": 10000,
                "nanoseconds": 184318,
                "pct_of_parent": 35,
                "children": [ ]
                }
        ]
        }
]
}
```
