/**
 * @file constant_string_algorithms.hpp
 * @brief Search, comparison, dan operasi string lainnya
 * @version 1.0
 */

#pragma once

#include "constant_string_core.hpp"

namespace zuu {

// Continuation dari class string...
// Methods untuk search dan comparison

template <traits::character CharT, std::size_t N>
class string {
    // ... (previous members)

public:
    // ========================================================================
    // Search Operations
    // ========================================================================

    /**
     * @brief Find substring
     * @param str Substring to find
     * @param pos Starting position
     * @return Position of first occurrence or npos
     */
    [[nodiscard]] constexpr size_type find(const CharT* str, size_type pos = 0) const noexcept {
        if (!str) return npos;
        return detail::find_substring(data_, len_, str, detail::strlen(str), pos);
    }

    template <size_type M>
    [[nodiscard]] constexpr size_type find(const string<CharT, M>& str, 
                                            size_type pos = 0) const noexcept {
        return detail::find_substring(data_, len_, str.data(), str.length(), pos);
    }

    /**
     * @brief Find character
     */
    [[nodiscard]] constexpr size_type find(CharT ch, size_type pos = 0) const noexcept {
        return detail::find_char(data_, len_, ch, pos);
    }

    /**
     * @brief Reverse find character
     */
    [[nodiscard]] constexpr size_type rfind(CharT ch, size_type pos = npos) const noexcept {
        return detail::rfind_char(data_, len_, ch, pos);
    }

    /**
     * @brief Reverse find substring
     */
    [[nodiscard]] constexpr size_type rfind(const CharT* str, size_type pos = npos) const noexcept {
        if (!str) return npos;
        
        size_type str_len = detail::strlen(str);
        if (str_len == 0) return (pos >= len_) ? len_ : pos;
        if (str_len > len_) return npos;
        
        size_type search_end = (pos >= len_ - str_len) ? (len_ - str_len) : pos;
        
        for (size_type i = search_end + 1; i > 0; --i) {
            size_type idx = i - 1;
            bool match = true;
            for (size_type j = 0; j < str_len; ++j) {
                if (data_[idx + j] != str[j]) {
                    match = false;
                    break;
                }
            }
            if (match) return idx;
        }
        return npos;
    }

    /**
     * @brief Find first of any character in set
     */
    [[nodiscard]] constexpr size_type find_first_of(const CharT* set, 
                                                     size_type pos = 0) const noexcept {
        if (!set || pos >= len_) return npos;
        
        size_type set_len = detail::strlen(set);
        for (size_type i = pos; i < len_; ++i) {
            for (size_type j = 0; j < set_len; ++j) {
                if (data_[i] == set[j]) return i;
            }
        }
        return npos;
    }

    [[nodiscard]] constexpr size_type find_first_of(CharT ch, size_type pos = 0) const noexcept {
        return find(ch, pos);
    }

    /**
     * @brief Find first NOT of any character in set
     */
    [[nodiscard]] constexpr size_type find_first_not_of(const CharT* set, 
                                                         size_type pos = 0) const noexcept {
        if (!set || pos >= len_) return npos;
        
        size_type set_len = detail::strlen(set);
        for (size_type i = pos; i < len_; ++i) {
            bool found = false;
            for (size_type j = 0; j < set_len; ++j) {
                if (data_[i] == set[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) return i;
        }
        return npos;
    }

    /**
     * @brief Find last of any character in set
     */
    [[nodiscard]] constexpr size_type find_last_of(const CharT* set, 
                                                    size_type pos = npos) const noexcept {
        if (!set || len_ == 0) return npos;
        
        size_type set_len = detail::strlen(set);
        size_type start = (pos >= len_) ? len_ - 1 : pos;
        
        for (size_type i = start + 1; i > 0; --i) {
            size_type idx = i - 1;
            for (size_type j = 0; j < set_len; ++j) {
                if (data_[idx] == set[j]) return idx;
            }
        }
        return npos;
    }

    /**
     * @brief Find last NOT of any character in set
     */
    [[nodiscard]] constexpr size_type find_last_not_of(const CharT* set, 
                                                        size_type pos = npos) const noexcept {
        if (!set || len_ == 0) return npos;
        
        size_type set_len = detail::strlen(set);
        size_type start = (pos >= len_) ? len_ - 1 : pos;
        
        for (size_type i = start + 1; i > 0; --i) {
            size_type idx = i - 1;
            bool found = false;
            for (size_type j = 0; j < set_len; ++j) {
                if (data_[idx] == set[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) return idx;
        }
        return npos;
    }

    // ========================================================================
    // Prefix/Suffix Checking
    // ========================================================================

    /**
     * @brief Check if starts with prefix
     */
    [[nodiscard]] constexpr bool starts_with(const CharT* prefix) const noexcept {
        if (!prefix) return false;
        
        size_type prefix_len = detail::strlen(prefix);
        if (prefix_len > len_) return false;
        
        return detail::strcmp(data_, prefix, prefix_len) == 0;
    }

    template <size_type M>
    [[nodiscard]] constexpr bool starts_with(const string<CharT, M>& prefix) const noexcept {
        return starts_with(prefix.data());
    }

    [[nodiscard]] constexpr bool starts_with(CharT ch) const noexcept {
        return len_ > 0 && data_[0] == ch;
    }

    /**
     * @brief Check if ends with suffix
     */
    [[nodiscard]] constexpr bool ends_with(const CharT* suffix) const noexcept {
        if (!suffix) return false;
        
        size_type suffix_len = detail::strlen(suffix);
        if (suffix_len > len_) return false;
        
        return detail::strcmp(data_ + (len_ - suffix_len), suffix, suffix_len) == 0;
    }

    template <size_type M>
    [[nodiscard]] constexpr bool ends_with(const string<CharT, M>& suffix) const noexcept {
        return ends_with(suffix.data());
    }

    [[nodiscard]] constexpr bool ends_with(CharT ch) const noexcept {
        return len_ > 0 && data_[len_ - 1] == ch;
    }

    /**
     * @brief Check if contains substring
     */
    [[nodiscard]] constexpr bool contains(const CharT* str) const noexcept {
        return find(str) != npos;
    }

    template <size_type M>
    [[nodiscard]] constexpr bool contains(const string<CharT, M>& str) const noexcept {
        return find(str) != npos;
    }

    [[nodiscard]] constexpr bool contains(CharT ch) const noexcept {
        return find(ch) != npos;
    }

    /**
     * @brief Count character occurrences
     */
    [[nodiscard]] constexpr size_type count(CharT ch) const noexcept {
        size_type result = 0;
        for (size_type i = 0; i < len_; ++i) {
            if (data_[i] == ch) ++result;
        }
        return result;
    }

    /**
     * @brief Count substring occurrences
     */
    [[nodiscard]] constexpr size_type count(const CharT* str) const noexcept {
        if (!str) return 0;
        
        size_type str_len = detail::strlen(str);
        if (str_len == 0 || str_len > len_) return 0;
        
        size_type result = 0;
        size_type pos = 0;
        while ((pos = find(str, pos)) != npos) {
            ++result;
            pos += str_len;
        }
        return result;
    }

    // ========================================================================
    // Substring Operations
    // ========================================================================

    /**
     * @brief Extract substring (same capacity)
     */
    [[nodiscard]] constexpr string substr(size_type pos = 0, 
                                          size_type count = npos) const noexcept {
        string result;
        if (pos >= len_) return result;
        
        size_type actual_count = std::min(count, len_ - pos);
        result.assign_impl(data_ + pos, actual_count);
        return result;
    }

    // ========================================================================
    // Comparison
    // ========================================================================

    /**
     * @brief Three-way comparison
     */
    template <size_type M>
    [[nodiscard]] constexpr int compare(const string<CharT, M>& other) const noexcept {
        return detail::strcmp_full(data_, len_, other.data(), other.length());
    }

    [[nodiscard]] constexpr int compare(const CharT* str) const noexcept {
        if (!str) return (len_ > 0) ? 1 : 0;
        return detail::strcmp_full(data_, len_, str, detail::strlen(str));
    }

    [[nodiscard]] constexpr int compare(size_type pos, size_type count, 
                                        const CharT* str) const noexcept {
        if (pos >= len_ || !str) return -1;
        
        size_type actual = std::min(count, len_ - pos);
        return detail::strcmp_full(data_ + pos, actual, str, detail::strlen(str));
    }

    // ========================================================================
    // Comparison Operators
    // ========================================================================

    template <size_type M>
    [[nodiscard]] constexpr bool operator==(const string<CharT, M>& other) const noexcept {
        return len_ == other.length() && compare(other) == 0;
    }

    [[nodiscard]] constexpr bool operator==(const CharT* str) const noexcept {
        return compare(str) == 0;
    }

    template <size_type M>
    [[nodiscard]] constexpr auto operator<=>(const string<CharT, M>& other) const noexcept {
        int cmp = compare(other);
        return (cmp < 0) ? std::strong_ordering::less :
               (cmp > 0) ? std::strong_ordering::greater :
                           std::strong_ordering::equal;
    }

    [[nodiscard]] constexpr auto operator<=>(const CharT* str) const noexcept {
        int cmp = compare(str);
        return (cmp < 0) ? std::strong_ordering::less :
               (cmp > 0) ? std::strong_ordering::greater :
                           std::strong_ordering::equal;
    }

    // ========================================================================
    // Hash Support
    // ========================================================================

    /**
     * @brief Compute FNV-1a hash
     */
    [[nodiscard]] constexpr std::size_t hash() const noexcept {
        return detail::hash_fnv1a(data_, len_);
    }
};

// ============================================================================
// Non-member Functions
// ============================================================================

/**
 * @brief Concatenate two strings (capacity = N1 + N2)
 */
template <traits::character CharT, std::size_t N1, std::size_t N2>
[[nodiscard]] constexpr auto concat(const string<CharT, N1>& a, 
                                    const string<CharT, N2>& b) noexcept {
    string<CharT, N1 + N2> result;
    result.append(a);
    result.append(b);
    return result;
}

/**
 * @brief Operator + for concatenation
 */
template <traits::character CharT, std::size_t N1, std::size_t N2>
[[nodiscard]] constexpr auto operator+(const string<CharT, N1>& a, 
                                        const string<CharT, N2>& b) noexcept {
    return concat(a, b);
}

/**
 * @brief Create substring with new capacity
 */
template <std::size_t NewN, traits::character CharT, std::size_t N>
[[nodiscard]] constexpr auto substr(const string<CharT, N>& str,
                                    std::size_t pos = 0,
                                    std::size_t count = string<CharT, N>::npos) noexcept {
    string<CharT, NewN> result;
    if (pos < str.length()) {
        std::size_t actual = std::min(count, str.length() - pos);
        actual = std::min(actual, NewN);
        result.append(str.data() + pos, actual);
    }
    return result;
}

/**
 * @brief Create reversed copy
 */
template <traits::character CharT, std::size_t N>
[[nodiscard]] constexpr auto reversed(const string<CharT, N>& str) noexcept {
    string<CharT, N> result = str;
    result.reverse();
    return result;
}

/**
 * @brief Create uppercase copy
 */
template <std::size_t N>
[[nodiscard]] constexpr auto to_upper(const string<char, N>& str) noexcept {
    string<char, N> result = str;
    result.to_upper();
    return result;
}

/**
 * @brief Create lowercase copy
 */
template <std::size_t N>
[[nodiscard]] constexpr auto to_lower(const string<char, N>& str) noexcept {
    string<char, N> result = str;
    result.to_lower();
    return result;
}

/**
 * @brief Create trimmed copy
 */
template <std::size_t N>
[[nodiscard]] constexpr auto trimmed(const string<char, N>& str) noexcept {
    string<char, N> result = str;
    result.trim();
    return result;
}

} // namespace zuu
