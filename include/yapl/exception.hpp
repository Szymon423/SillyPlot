#pragma once

#include <exception>
#include <string>

namespace yapl {
    class Exception : public std::exception {
    private:
        std::string message;

    public:
        explicit Exception(const char* msg);
        ~Exception() noexcept override = default;
        const char* what() const noexcept override;
    };
}
