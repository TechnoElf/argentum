/*
 * Created by janis on 2024-02-01
 */

#pragma once

#include <string>
#include <array>

namespace ag {
    template<typename T>
    concept EnumTrait = requires(T v) {
        { typename T::Kind() };
        { T::Kind::Any } -> std::convertible_to<typename T::Kind>;
        { T::Kind::Unknown } -> std::convertible_to<typename T::Kind>;
        { v.kind } -> std::convertible_to<typename T::Kind>;
        { v.kinds };
        { std::get<0>(v.kinds[0]) } -> std::convertible_to<typename T::Kind>;
        { std::get<1>(v.kinds[0]) } -> std::convertible_to<const char*>;
        { std::get<2>(v.kinds[0]) } -> std::convertible_to<const char*>;
    };

    template<EnumTrait K>
    struct Enum {
        K inner;

    public:
        const K operator*() const {
            return this->inner;
        }

        bool operator==(const Enum<K>& other) const {
            return (**this).kind == (*other).kind || (**this).kind == K::Kind::Any || (*other).kind == K::Kind::Any;
        }

        const char* to_string() const {
            for (const auto& kind : K::kinds) {
                if ((**this).kind == std::get<0>(kind)) {
                    return std::get<1>(kind);
                }
            }
            return "Unknown";
        }

        static Enum<K> from_string(const std::string& v) {
            for (const auto& kind : K::kinds) {
                if (v == std::get<1>(kind)) {
                    return {std::get<0>(kind)};
                }
            }
            return {K::Kind::Unknown};
        }

        static Enum<K> from_api_string(const std::string& v) {
            for (const auto& kind : K::kinds) {
                if (v == std::get<2>(kind)) {
                    return {std::get<0>(kind)};
                }
            }
            return {K::Kind::Unknown};
        }
    };
}