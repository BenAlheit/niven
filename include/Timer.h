#ifndef INCLUDE_INCLUDE_TIMER_H_
#define INCLUDE_INCLUDE_TIMER_H_

#include <map>
#include <memory>
#include <string>

#include "CodeBlock.h"

namespace niven {

using namespace std;

template <typename ui_> class Timer {
public:
  Timer() = default;
  Timer(Timer &&) = default;
  Timer(const Timer &) = default;
  Timer &operator=(Timer &&) = default;
  Timer &operator=(const Timer &) = default;
  ~Timer() = default;

  void start();
  void end();

  TimerPawn<ui_> time_section(const string &label){
        CodeBlock<ui_>& section = this->current_block->get_create(label);
        current_block = &section;
        return TimerPawn(section, *this);
    };
  void start_section(const string &label);
  void end_section();
  void time_function();
  void print();

private:
  bool running = false;
  bool finished = false;
  map<string, unique_ptr<CodeBlock<ui_>>> code_blocks;
    TimerPawn<ui_>* root_pawn = NULL;

  CodeBlock<ui_> *root;
  CodeBlock<ui_> *current_block;
  friend TimerPawn<ui_>;
};

template <typename ui_> struct TimerPawn {
    TimerPawn(CodeBlock<ui_> &partner_, Timer<ui_> &timer) : partner(partner_), timer(timer) {
    partner.calls++;
    start_time = partner.get_time();
  }

  ~TimerPawn() {
    partner.nano_seconds += partner.get_time() - this->start_time;
    timer.current_block = partner.parent;
  }

  ui_ start_time;
  CodeBlock<ui_> &partner;
  Timer<ui_> &timer;
};

} // namespace niven
//

static niven::Timer<uint64_t> timer;
#define NameConcat2(A, B) A##B
#define NameConcat(A, B) NameConcat2(A, B)
#define NivenTimeBlock(Name) niven::TimerPawn<uint64_t> NameConcat(Pawn, __LINE__) = timer.time_section(Name);
#define NivenTimeFunction NivenTimeBlock(__func__)

        // niven::TimerPawn<uint64_t> pawn1 = timer.time_section("outside loop");

#endif // INCLUDE_INCLUDE_TIMER_H_
