#pragma once

/**
 * @file fstring.hpp
 * @author zugyonozz (rafizuhayr001@gmail.com)
 * @brief Main header file for the fstring library
 * @version 2.0
 * @date 2025-11-26
 * 
 * @copyright Copyright (c) 2025
 * 
 * fstring - A modern C++ fixed-capacity string library
 * 
 * Features:
 * - Fixed capacity at compile-time (no heap allocation)
 * - Full constexpr support
 * - Compatible with all standard character types
 * - Compatible with std::string and std::string_view
 * - Rich set of string operations
 * - Type-safe conversions
 * - User-defined literals
 * 
 * Basic Usage:
 * @code
 * #include "fstring.hpp"
 * using namespace zuu;
 * 
 * // Create fstring
 * fstring<10> str1 = "hello";
 * auto str2 = "world"_fs;
 * 
 * // Concatenation
 * auto str3 = str1 + " " + str2;
 * 
 * // String operations
 * str1.append("!");
 * str1.insert(0, "Say ");
 * 
 * // Conversions
 * auto num_str = to_fstring(42);
 * int num = parse_int<int>(num_str);
 * 
 * // Algorithms
 * auto upper = algorithms::to_upper(str1);
 * auto trimmed = algorithms::trim(str2);
 * @endcode
 */

// Configuration
#include "fstring_config.hpp"

// Core type traits and concepts
#include "fstring_traits.hpp"

// Utility functions
#include "fstring_utils.hpp"

// Main fstring class
#include "fstring_core.hpp"

// Conversion utilities
#include "fstring_convertions.hpp"

// String algorithms
#include "fstring_algorithms.hpp"

// User-defined literals
#include "fstring_literals.hpp"

/**
 * @namespace zuu
 * @brief Main namespace for the fstring library
 */
namespace zuu {

/**
 * @brief Library version information
 */
inline constexpr struct version_info_t {
    int major = version::major;
    int minor = version::minor;
    int patch = version::patch;
    const char* string = version::string;
    
    [[nodiscard]] constexpr bool is_at_least(int maj, int min = 0, int pat = 0) const noexcept {
        if (major > maj) return true;
        if (major < maj) return false;
        if (minor > min) return true;
        if (minor < min) return false;
        return patch >= pat;
    }
} version_info;

/**
 * @brief Quick reference type aliases
 */
namespace types {
    /// Standard fstring with common sizes
    using str8 = fstring<8>;
    using str16 = fstring<16>;
    using str32 = fstring<32>;
    using str64 = fstring<64>;
    using str128 = fstring<128>;
    using str256 = fstring<256>;
    using str512 = fstring<512>;
    using str1k = fstring<1024>;
    
    /// Path string (suitable for file paths)
    using path_str = fstring<260>; // MAX_PATH on Windows
    
    /// Name string (suitable for names, identifiers)
    using name_str = fstring<64>;
    
    /// Message string (suitable for messages, descriptions)
    using msg_str = fstring<256>;
    
    /// UUID string
    using uuid_str = fstring<36>;
    
    /// IP address string
    using ip_str = fstring<45>; // IPv6 max length
    
    /// Date/time string
    using datetime_str = fstring<32>;
}

} // namespace zuu

/**
 * @example examples.cpp
 * Basic usage examples of fstring library
 * 
 * @example test.cpp
 * testing
 */
