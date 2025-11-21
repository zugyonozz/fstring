/**
 * @file constant_string_fwd.hpp
 * @brief Forward declarations untuk compile-time string library
 * @version 1.0.2
 */

#pragma once

#include <cstddef>
#include <type_traits>

namespace zuu {

// Forward declarations
template <typename = char, std::size_t = 0>
class string ;

template <typename, bool>
class string_iterator ;

namespace traits {
    template <typename T>
    struct is_char;
    
    template <typename T>
    inline constexpr bool is_char_v = is_char<std::remove_cv_t<T>>::value;
}

// Type aliases
template <std::size_t N> using cstring    = string<char, N>;
template <std::size_t N> using cwstring   = string<wchar_t, N>;
template <std::size_t N> using cu8string  = string<char8_t, N>;
template <std::size_t N> using cu16string = string<char16_t, N>;
template <std::size_t N> using cu32string = string<char32_t, N>;

} // namespace zuu
