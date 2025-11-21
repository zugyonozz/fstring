/**
 * @file example.cpp
 * @brief Contoh penggunaan library zuu::string
 * 
 * Compile: g++ -std=c++20 -o example constant_string_example.cpp
 */

#include "constant_string.hpp"
#include <iostream>

// Import literal operator
using namespace zuu::literals;

int main() {
    // ========================================================================
    // 1. Konstruksi
    // ========================================================================
    std::cout << "=== Konstruksi ===" << std::endl;
    
    // Dari string literal dengan deduction guide
    constexpr zuu::string str1("Hello");
    
    // Dengan ukuran eksplisit
    constexpr zuu::cstring<20> str2("World");
    
    // Dengan user-defined literal
    constexpr auto str3 = "Compile-time"_cs;
    
    // Dengan karakter berulang
    constexpr zuu::cstring<10> dashes(5, '-');
    
    // Copy dari string lain (berbeda ukuran)
    constexpr zuu::cstring<30> str4(str1);
    
    std::cout << "str1: " << str1.c_str() << " (len=" << str1.length() << ", cap=" << str1.capacity() << ")\n";
    std::cout << "str2: " << str2.c_str() << " (len=" << str2.length() << ", cap=" << str2.capacity() << ")\n";
    std::cout << "str3: " << str3.c_str() << " (len=" << str3.length() << ")\n";
    std::cout << "dashes: " << dashes.c_str() << "\n";
    
    // ========================================================================
    // 2. Concatenation
    // ========================================================================
    std::cout << "\n=== Concatenation ===" << std::endl;
    
    constexpr auto hello = "Hello"_cs;
    constexpr auto world = " World!"_cs;
    constexpr auto greeting = zuu::concat(hello, world);
    
    // Atau dengan operator+
    constexpr auto greeting2 = hello + world;
    
    std::cout << "concat: " << greeting.c_str() << "\n";
    std::cout << "operator+: " << greeting2.c_str() << "\n";
    
    // Append (modifikasi in-place)
    zuu::cstring<50> builder("Start");
    builder += " -> ";
    builder += "Middle";
    builder += " -> ";
    builder += "End";
    std::cout << "builder: " << builder.c_str() << "\n";
    
    // ========================================================================
    // 3. Substring
    // ========================================================================
    std::cout << "\n=== Substring ===" << std::endl;
    
    constexpr zuu::cstring<20> source("Hello World");
    constexpr auto sub1 = source.substr(0, 5);  // "Hello"
    constexpr auto sub2 = source.substr(6);     // "World"
    
    // Substring dengan kapasitas baru
    constexpr auto sub3 = zuu::substr<10>(source, 0, 5);
    
    std::cout << "source: " << source.c_str() << "\n";
    std::cout << "substr(0,5): " << sub1.c_str() << "\n";
    std::cout << "substr(6): " << sub2.c_str() << "\n";
    
    // ========================================================================
    // 4. Search Operations
    // ========================================================================
    std::cout << "\n=== Search ===" << std::endl;
    
    constexpr zuu::cstring<30> text("The quick brown fox");
    
    constexpr auto pos1 = text.find("quick");
    constexpr auto pos2 = text.find('o');
    constexpr auto pos3 = text.rfind('o');
    
    std::cout << "text: " << text.c_str() << "\n";
    std::cout << "find('quick'): " << pos1 << "\n";
    std::cout << "find('o'): " << pos2 << "\n";
    std::cout << "rfind('o'): " << pos3 << "\n";
    std::cout << "contains('fox'): " << std::boolalpha << text.contains("fox") << "\n";
    std::cout << "count('o'): " << text.count('o') << "\n";
    
    // ========================================================================
    // 5. Prefix/Suffix Check
    // ========================================================================
    std::cout << "\n=== Prefix/Suffix ===" << std::endl;
    
    constexpr zuu::cstring<20> filename("document.txt");
    
    std::cout << "filename: " << filename.c_str() << "\n";
    std::cout << "starts_with('doc'): " << filename.starts_with("doc") << "\n";
    std::cout << "ends_with('.txt'): " << filename.ends_with(".txt") << "\n";
    std::cout << "ends_with('.pdf'): " << filename.ends_with(".pdf") << "\n";
    
    // ========================================================================
    // 6. Case Conversion
    // ========================================================================
    std::cout << "\n=== Case Conversion ===" << std::endl;
    
    zuu::cstring<20> mixed("HeLLo WoRLd");
    std::cout << "original: " << mixed.c_str() << "\n";
    
    auto upper = zuu::to_upper(mixed);
    auto lower = zuu::to_lower(mixed);
    
    std::cout << "to_upper: " << upper.c_str() << "\n";
    std::cout << "to_lower: " << lower.c_str() << "\n";
    
    // In-place modification
    mixed.to_upper();
    std::cout << "in-place upper: " << mixed.c_str() << "\n";
    
    // ========================================================================
    // 7. Trim
    // ========================================================================
    std::cout << "\n=== Trim ===" << std::endl;
    
    zuu::cstring<30> padded("   Hello World   \n");
    std::cout << "before trim: [" << padded.c_str() << "]\n";
    
    padded.trim();
    std::cout << "after trim: [" << padded.c_str() << "]\n";
    
    // ========================================================================
    // 8. Reverse
    // ========================================================================
    std::cout << "\n=== Reverse ===" << std::endl;
    
    constexpr auto original = "Hello"_cs;
    constexpr auto rev = zuu::reversed(original);
    
    std::cout << "original: " << original.c_str() << "\n";
    std::cout << "reversed: " << rev.c_str() << "\n";
    
    // ========================================================================
    // 9. Insert/Erase/Replace
    // ========================================================================
    std::cout << "\n=== Insert/Erase/Replace ===" << std::endl;
    
    zuu::cstring<30> editable("Hello World");
    std::cout << "original: " << editable.c_str() << "\n";
    
    editable.insert(5, " Beautiful", 10);
    std::cout << "after insert: " << editable.c_str() << "\n";
    
    zuu::cstring<30> editable2("Hello World");
    editable2.erase(5, 6);  // Hapus " World"
    std::cout << "after erase: " << editable2.c_str() << "\n";
    
    zuu::cstring<30> editable3("Hello World");
    editable3.replace(6, 5, "Universe", 8);
    std::cout << "after replace: " << editable3.c_str() << "\n";
    
    // ========================================================================
    // 10. Comparison
    // ========================================================================
    std::cout << "\n=== Comparison ===" << std::endl;
    
    constexpr auto a = "apple"_cs;
    constexpr auto b = "banana"_cs;
    constexpr auto c = "apple"_cs;
    
    std::cout << "a == c: " << (a == c) << "\n";
    std::cout << "a == b: " << (a == b) << "\n";
    std::cout << "a < b: " << (a < b) << "\n";
    std::cout << "a.compare(b): " << a.compare(b) << "\n";
    
    // ========================================================================
    // 11. Iteration
    // ========================================================================
    std::cout << "\n=== Iteration ===" << std::endl;
    
    constexpr auto iter_str = "ABCDE"_cs;
    
    std::cout << "forward: ";
    for (char ch : iter_str) {
        std::cout << ch << ' ';
    }
    std::cout << "\n";
    
    std::cout << "reverse: ";
    for (auto it = iter_str.rbegin(); it != iter_str.rend(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << "\n";
    
    // ========================================================================
    // 12. Hash
    // ========================================================================
    std::cout << "\n=== Hash ===" << std::endl;
    
    constexpr auto h1 = "Hello"_cs;
    constexpr auto h2 = "Hello"_cs;
    constexpr auto h3 = "World"_cs;
    
    std::cout << "hash('Hello'): " << h1.hash() << "\n";
    std::cout << "hash('Hello'): " << h2.hash() << " (same)\n";
    std::cout << "hash('World'): " << h3.hash() << "\n";
    
    // ========================================================================
    // 13. Compile-time Assertions
    // ========================================================================
    std::cout << "\n=== Compile-time Verification ===" << std::endl;
    
    // Semua ini dievaluasi pada waktu kompilasi!
    static_assert(str1.length() == 5);
    static_assert(str1.capacity() == 5);
    static_assert(hello + world == "Hello World!"_cs);
    static_assert("abc"_cs < "abd"_cs);
    static_assert("test"_cs.contains("es"));
    static_assert("hello.txt"_cs.ends_with(".txt"));
    static_assert(zuu::reversed("abc"_cs) == "cba"_cs);
    
    std::cout << "All compile-time assertions passed!\n";
    
    // ========================================================================
    // 14. Wide String Support
    // ========================================================================
    std::cout << "\n=== Wide String ===" << std::endl;
    
    constexpr zuu::cwstring<20> wide(L"Wide String");
    std::wcout << L"wide: " << wide.c_str() << L"\n";
    
    return 0;
}
