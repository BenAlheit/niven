#include "niven/Timer.h"
#include <cstdint>
#include <memory>
#include <iostream>
#include <fstream>

namespace niven {

template <typename ui_>
void Timer<ui_>::print()
{
    // cout << "Total time: " << this->root->get_ns_ellapsed() << endl;
    // this->root->print();

    string json_string = "";
    this->root->write_json_string(json_string);
    cout << json_string << endl;
    // ofstream out(output_pth);
    // out << json_string;
    // out.close();

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

template <typename ui_>
void Timer<ui_>::dump_json(const string & output_pth)
{

    string json_string = "";
    this->root->write_json_string(json_string);
    ofstream out(output_pth);
    out << json_string;
    out.close();

}

template class Timer<uint64_t>;

} // namespace niven
