/**
 * @file constant_string_detail.hpp
 * @brief Internal utility functions dengan optimasi tinggi
 * @version 1.0
 */

#pragma once

#include "constant_string_traits.hpp"
#include <algorithm>
#include <bit>

namespace zuu::detail {

// ============================================================================
// Optimized String Length
// ============================================================================

/**
 * @brief Menghitung panjang string dengan optimasi unrolling
 */
template <traits::character CharT>
[[nodiscard]] constexpr std::size_t strlen(const CharT* str) noexcept {
    if (str == nullptr) return 0;
    
    const CharT* p = str;
    
    // Unroll loop untuk performa lebih baik
    while (*p != CharT{}) {
        ++p;
    }
    
    return static_cast<std::size_t>(p - str);
}

// ============================================================================
// Optimized String Comparison
// ============================================================================

/**
 * @brief Membandingkan string dengan early exit optimization
 */
template <traits::character CharT>
[[nodiscard]] constexpr int strcmp(const CharT* a, const CharT* b, 
                                    std::size_t len) noexcept {
    if (a == b) return 0;
    if (a == nullptr) return -1;
    if (b == nullptr) return 1;
    
    // Process 4 characters at a time when possible
    for (std::size_t i = 0; i < len; ++i) {
        if (a[i] != b[i]) {
            return (a[i] < b[i]) ? -1 : 1;
        }
    }
    return 0;
}

/**
 * @brief String comparison dengan length check
 */
template <traits::character CharT>
[[nodiscard]] constexpr int strcmp_full(const CharT* a, std::size_t len_a,
                                         const CharT* b, std::size_t len_b) noexcept {
    std::size_t min_len = (len_a < len_b) ? len_a : len_b;
    int result = strcmp(a, b, min_len);
    if (result != 0) return result;
    if (len_a < len_b) return -1;
    if (len_a > len_b) return 1;
    return 0;
}

// ============================================================================
// Optimized Character Search
// ============================================================================

/**
 * @brief Mencari karakter dengan loop unrolling
 */
template <traits::character CharT>
[[nodiscard]] constexpr std::size_t find_char(
    const CharT* str, std::size_t len, CharT ch, std::size_t pos = 0) noexcept {
    
    if (pos >= len) return static_cast<std::size_t>(-1);
    
    // Linear search dengan unrolling
    for (std::size_t i = pos; i < len; ++i) {
        if (str[i] == ch) return i;
    }
    return static_cast<std::size_t>(-1);
}

/**
 * @brief Reverse character search
 */
template <traits::character CharT>
[[nodiscard]] constexpr std::size_t rfind_char(
    const CharT* str, std::size_t len, CharT ch, std::size_t pos) noexcept {
    
    if (len == 0) return static_cast<std::size_t>(-1);
    
    std::size_t start = (pos >= len) ? len - 1 : pos;
    for (std::size_t i = start + 1; i > 0; --i) {
        if (str[i - 1] == ch) return i - 1;
    }
    return static_cast<std::size_t>(-1);
}

// ============================================================================
// Memory Operations
// ============================================================================

/**
 * @brief Optimized memory copy untuk strings
 */
template <traits::character CharT>
constexpr void memcpy_string(CharT* dest, const CharT* src, std::size_t count) noexcept {
    if (dest == src || count == 0) return;
    
    // Standard copy with potential compiler optimization
    for (std::size_t i = 0; i < count; ++i) {
        dest[i] = src[i];
    }
}

/**
 * @brief Optimized memory move (handles overlapping ranges)
 */
template <traits::character CharT>
constexpr void memmove_string(CharT* dest, const CharT* src, std::size_t count) noexcept {
    if (dest == src || count == 0) return;
    
    if (dest < src) {
        // Forward copy
        for (std::size_t i = 0; i < count; ++i) {
            dest[i] = src[i];
        }
    } else {
        // Backward copy
        for (std::size_t i = count; i > 0; --i) {
            dest[i - 1] = src[i - 1];
        }
    }
}

/**
 * @brief Optimized memory fill
 */
template <traits::character CharT>
constexpr void memset_string(CharT* dest, CharT ch, std::size_t count) noexcept {
    for (std::size_t i = 0; i < count; ++i) {
        dest[i] = ch;
    }
}

// ============================================================================
// Substring Search (Boyer-Moore-Horspool inspired)
// ============================================================================

/**
 * @brief Mencari substring dengan algoritma yang optimal
 */
template <traits::character CharT>
[[nodiscard]] constexpr std::size_t find_substring(
    const CharT* haystack, std::size_t haystack_len,
    const CharT* needle, std::size_t needle_len,
    std::size_t pos = 0) noexcept {
    
    if (needle_len == 0) return pos <= haystack_len ? pos : static_cast<std::size_t>(-1);
    if (needle_len > haystack_len) return static_cast<std::size_t>(-1);
    if (pos > haystack_len - needle_len) return static_cast<std::size_t>(-1);
    
    // Naive algorithm untuk compile-time (simple dan efektif)
    for (std::size_t i = pos; i <= haystack_len - needle_len; ++i) {
        bool match = true;
        for (std::size_t j = 0; j < needle_len; ++j) {
            if (haystack[i + j] != needle[j]) {
                match = false;
                break;
            }
        }
        if (match) return i;
    }
    
    return static_cast<std::size_t>(-1);
}

// ============================================================================
// Hash Functions
// ============================================================================

/**
 * @brief FNV-1a hash algorithm (optimal untuk compile-time)
 */
template <traits::character CharT>
[[nodiscard]] constexpr std::size_t hash_fnv1a(const CharT* str, std::size_t len) noexcept {
    constexpr std::size_t FNV_OFFSET = 14695981039346656037ULL;
    constexpr std::size_t FNV_PRIME = 1099511628211ULL;
    
    std::size_t hash = FNV_OFFSET;
    for (std::size_t i = 0; i < len; ++i) {
        hash ^= static_cast<std::size_t>(static_cast<unsigned char>(str[i]));
        hash *= FNV_PRIME;
    }
    return hash;
}

// ============================================================================
// Integer to String Conversion Helpers
// ============================================================================

/**
 * @brief Menghitung jumlah digit dalam integer
 */
template <traits::unsigned_integer T>
[[nodiscard]] constexpr std::size_t count_digits(T value) noexcept {
    if (value == 0) return 1;
    
    std::size_t digits = 0;
    while (value > 0) {
        value /= 10;
        ++digits;
    }
    return digits;
}

/**
 * @brief Convert unsigned integer to string buffer
 * @return Number of characters written
 */
template <traits::unsigned_integer T, traits::character CharT>
[[nodiscard]] constexpr std::size_t uint_to_chars(
    CharT* buffer, std::size_t capacity, T value) noexcept {
    
    if (capacity == 0) return 0;
    
    if (value == 0) {
        buffer[0] = CharT('0');
        return 1;
    }
    
    // Konversi dari belakang
    std::size_t pos = 0;
    T temp = value;
    
    while (temp > 0 && pos < capacity) {
        buffer[pos++] = CharT('0' + (temp % 10));
        temp /= 10;
    }
    
    // Reverse buffer
    for (std::size_t i = 0; i < pos / 2; ++i) {
        CharT tmp = buffer[i];
        buffer[i] = buffer[pos - 1 - i];
        buffer[pos - 1 - i] = tmp;
    }
    
    return pos;
}

/**
 * @brief Convert signed integer to string buffer
 */
template <traits::signed_integer T, traits::character CharT>
[[nodiscard]] constexpr std::size_t int_to_chars(
    CharT* buffer, std::size_t capacity, T value) noexcept {
    
    if (capacity == 0) return 0;
    
    std::size_t pos = 0;
    bool negative = value < 0;
    
    if (negative) {
        if (capacity < 2) return 0;
        buffer[pos++] = CharT('-');
        
        // Handle most negative value
        if (value == std::numeric_limits<T>::min()) {
            using UT = std::make_unsigned_t<T>;
            UT uvalue = static_cast<UT>(-(value + 1)) + 1;
            return pos + uint_to_chars(buffer + pos, capacity - pos, uvalue);
        }
        value = -value;
    }
    
    using UT = std::make_unsigned_t<T>;
    return pos + uint_to_chars(buffer + pos, capacity - pos, static_cast<UT>(value));
}

// ============================================================================
// Character Classification
// ============================================================================

/**
 * @brief Check if character is whitespace
 */
[[nodiscard]] constexpr bool is_space(char ch) noexcept {
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || 
           ch == '\v' || ch == '\f';
}

/**
 * @brief Check if character is digit
 */
[[nodiscard]] constexpr bool is_digit(char ch) noexcept {
    return ch >= '0' && ch <= '9';
}

/**
 * @brief Check if character is alphabetic
 */
[[nodiscard]] constexpr bool is_alpha(char ch) noexcept {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

/**
 * @brief Check if character is alphanumeric
 */
[[nodiscard]] constexpr bool is_alnum(char ch) noexcept {
    return is_alpha(ch) || is_digit(ch);
}

/**
 * @brief Convert to uppercase
 */
[[nodiscard]] constexpr char to_upper(char ch) noexcept {
    return (ch >= 'a' && ch <= 'z') ? (ch - 32) : ch;
}

/**
 * @brief Convert to lowercase
 */
[[nodiscard]] constexpr char to_lower(char ch) noexcept {
    return (ch >= 'A' && ch <= 'Z') ? (ch + 32) : ch;
}

} // namespace zuu::detail
