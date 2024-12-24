#include "Timer.h"
#include <cstdint>
#include <memory>
#include <iostream>

namespace niven {

template <typename ui_>
void Timer<ui_>::print()
{
    // cout << "Total time: " << this->root->get_ns_ellapsed() << endl;
    this->root->print();
}

template <typename ui_> void Timer<ui_>::start() {

    if(this->running) //TODO throw error
        ;

    this->running = true;
    this->code_blocks.insert(make_pair("total", make_unique<CodeBlock<ui_>>("total")));
    this->root = this->code_blocks.at("total").get();
    this->root_pawn = new TimerPawn<ui_>(*this->code_blocks.at("total").get(), *this);
    // this->root->tick();
    this->current_block = this->code_blocks.at("total").get();

}

template <typename ui_> void Timer<ui_>::end() {

    delete this->root_pawn;
    // this->root->tok();
    this->running = false;
    this->finished = true;

}

template <typename ui_> void Timer<ui_>::start_section(const string &label) {}
template <typename ui_> void Timer<ui_>::end_section() {}
template <typename ui_> void Timer<ui_>::time_function() {}

template class Timer<uint64_t>;

#define NameConcat2(A, B) A##B
#define NameConcat(A, B) NameConcat2(A, B)
#define NivenTimeBlock(Name) profile_block NameConcat(Block, __LINE__)(Name, __COUNTER__ + 1);
#define NivenTimeFunction NivenTimeBlock(__func__)
} // namespace niven
