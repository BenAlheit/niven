# Niven

A simple, light-weight, header only C++ profiling tool with no dependencies. 


<!-- ![alt text](https://github.com/BenAlheit/niven/blob/main/resources/niven.png?raw=true) -->

<p align="center">
  <img src="https://github.com/BenAlheit/niven/blob/main/resources/niven.png?raw=true" alt="Niven image"/>
</p>

## Minimal usage example

There are a few simple steps to profiling a program using Niven:
 - Include the Timer header file `#include <niven/Timer.h>`
    * This will create a static Timer object named `nivenTimer` -- you should not have a variable named `nivenTimer` anywhere else in your project.
 - Put anything to be timed between the calls `nivenTimer.start()` and `nivenTimer.end()`; that is, a skeleton program should look as follows:
 ```C++
#include <niven/Timer.h>

int main(){
    nivenTimer.start()
    //
    // ... your code goes here.
    //
    nivenTimer.end()
    return 0;
}

```
 - Niven provides two macros that allow you to time a function and a code block; these are, `NivenTimeFunction` and `NivenTimeBlock(<user-given-label>)`, respectively. The `NivenTimeFunction` macro uses the function name as a label, whereas `NivenTimeBlock` must be provided with a label from the user. Each of these macros will time from the line where the macro was called up to the end of the current scope. 
 - Finally, timing data can be printed to stdout using `nivenTimer.print()` and/or it can be written to a json file using `nivenTimer.dump_json("your_file_name.json")`. A complete demonstration of the functionality is provided in the following minimal example:
```C++
#include <niven/Timer.h>

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

  nivenTimer.start();
  {
    NivenTimeBlock("outside loop");
    for (unsigned int i = 0; i < 10000; i++) {
      NivenTimeBlock("loop");

      double a = 2 * 2;
    }
  }
  some_function();
  nivenTimer.end();
  nivenTimer.print();
  nivenTimer.dump_json("profile_data.json");

  return 0;
}
```
 - The data is stored and displayed in a tree structure so the above example will result in an output (in stdout because of `timer.print()` and `profile_data.json` because of `timer.dump_json("profile_data.json")`) of
```json
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
- Here, `label` is the name of the function that was timed if `NivenTimeFunction` was used and the user provided label if `NivenTimeBlock` was used; `n_calls` is the number of times the function (or code block) was called; `nanoseconds` is the number of nanoseconds taken to run the code in that scope; `pct_of_parent` is the percentage of time that the direct parent of the current code block spent within the current code block (that is, `100 * parent.nanoseconds/child.nanoseconds`); and `children` is a list of the children blocks of the current block.
- Unfortunately, timing takes time. If you time very short-running pieces of code then it is quite possible that taking the time measurement takes longer than the piece of code you are actually timing. In this case, the reported measurements will not be a good representation of reality. A good way to check if fine grained timing is adding to the compute time of your code significantly is simply turn-off all timing except for that at the outer most scope and compare the running time of the program with and without timing. This can be done in Niven by define the macro `DEACTIVATE_NIVEN` before including `niven/Timer.h` as follows:
```C++
#define DEACTIVATE_NIVEN
#include <niven/Timer.h>
// ...
// ...
// ...
```
- Doing this with the example above produces an output of 
```json
{
"label": "total",
"n_calls": 1,
"nanoseconds": 475,
"pct_of_parent": 100,
"children": [ ]
}
```
You might notice that the total running time of the program is much less in this case than the earlier case (475 nanoseconds vs. 1046132 nanoseconds) which indicates that almost all the compute time of the previous program was due to taking timing measurements.
