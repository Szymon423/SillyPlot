#include "yapl.hpp"

yapl::Exception::Exception(const char* msg) : message(msg) {}

const char* yapl::Exception::what() const noexcept {
    return message.c_str();
}
