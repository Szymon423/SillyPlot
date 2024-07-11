#include "yapl.hpp"

namespace yapl {
    Exception::Exception(const char* msg) : message(msg) {}

    const char* Exception::what() const noexcept {
        return message.c_str();
    }
}
