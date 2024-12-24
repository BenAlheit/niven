#include "CodeBlock.h"
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
    // this->last_time = ts.tv_nsec;
  } else {
    // perror("clock_gettime failed");
    // TODO throw exception
    return 1;
  }
}

// template <typename ui_> void CodeBlock<ui_>::tick() {
//   this->last_time = this->get_time();
//   this->calls++;
// }
// template <typename ui_> void CodeBlock<ui_>::tok() {
//   this->nano_seconds += this->get_time() - this->last_time;
// }

template class CodeBlock<uint64_t>;
} // namespace niven
