#include "niven/CodeBlock.h"
#include <cstdint>

#include <ctime>

namespace niven {

template <typename ui_> ui_ CodeBlock<ui_>::get_time() {

  struct timespec ts;
  // Get the current time from CLOCK_REALTIME
  if (clock_gettime(CLOCK_REALTIME, &ts) == 0) {
    // std::cout << "Current time: "
    //           << ts.tv_sec << " seconds and "
    //           << ts.tv_nsec << " nanoseconds since the epoch."
    //           << std::endl;
    return ts.tv_nsec;
  } else {
    // perror("clock_gettime failed");
    // TODO throw exception
    return 1;
  }
}

template <typename ui_>
void CodeBlock<ui_>::write_json_string(string &json_string,
                                       const string &indent) const {

  json_string += indent + "{\n";
  json_string += indent + "\"label\": \"" + this->label + "\",\n";
  json_string += indent + "\"n_calls\": " + to_string(this->calls) + ",\n";
  json_string +=
      indent + "\"nanoseconds\": " + to_string(this->nano_seconds) + ",\n";
  json_string +=
      indent + "\"pct_of_parent\": " + to_string(this->get_pct_of_partent()) + ",\n";

  json_string += indent + "\"children\": [\n";

  for (const auto &child : this->children) {
    child.second.write_json_string(json_string, indent + "\t");
    json_string += ",\n";
  }
  if (not this->children.empty()) {
    json_string.pop_back();
    json_string.pop_back();
    json_string += "\n" + indent + "]\n";
  } else {
    json_string.pop_back();
    json_string += " ]\n";
  }

  json_string += indent + "}";
}

template class CodeBlock<uint64_t>;
} // namespace niven
