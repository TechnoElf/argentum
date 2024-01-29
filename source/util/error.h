/*
 * Created by janis on 2024-01-25
 */

#pragma once

#include <expected>

namespace ag {
    enum class ErrorKind {
        Unknown
    };

    struct Error {
        ErrorKind kind;
    };

    template<typename T>
    using Result = std::expected<T, Error>;
}
