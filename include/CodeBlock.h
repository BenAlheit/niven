#ifndef INCLUDE_INCLUDE_CODEBLOCK_H_
#define INCLUDE_INCLUDE_CODEBLOCK_H_

#include <map>
#include <string>
// #include <vector>
#include <iostream>

namespace niven {
using namespace std;

template <typename ui_> struct TimerPawn;

template <typename ui_> class CodeBlock {
public:
  CodeBlock(const string &label, CodeBlock<ui_> *parent = NULL)
      : label(label), parent(parent) {};
  CodeBlock(CodeBlock &&) = default;
  CodeBlock(const CodeBlock &) = default;
  CodeBlock &operator=(CodeBlock &&) = default;
  CodeBlock &operator=(const CodeBlock &) = default;
  ~CodeBlock() = default;



    void write_json_string(string & json_string,
                           const string & indent="") const;

  ui_ get_pct_of_partent() const {
    if (this->parent)
      return 100 * this->nano_seconds / this->parent->get_ns_ellapsed();
    else
      return 100;
  }
  ui_ get_ns_ellapsed() const { return this->nano_seconds; }
  ui_ get_n_calls() const { return this->calls; }
  void print(const string &prefix = "") const {
    cout << prefix << label << "\t" << "time: " << nano_seconds
         << "\tpct of parent: " << get_pct_of_partent() << endl;
    for (const auto &child : children)
      child.second.print(prefix + "\t");
  }

  CodeBlock<ui_> &get_create(const string &label) {
    if (children.empty() || children.find(label) == children.end())

      // if (children.find(label) == children.end())
      this->children.insert(make_pair(label, CodeBlock<ui_>(label, this)));

    return children.at(label);
  };

private:
  const string label;

  CodeBlock<ui_> *parent;
  map<string, CodeBlock<ui_>> children;

  // ui_ last_time;

  ui_ nano_seconds = 0;
  ui_ calls = 0;
  ui_ get_time();
  friend TimerPawn<ui_>;
};

} // namespace niven
//
#endif // INCLUDE_INCLUDE_CODEBLOCK_H_
