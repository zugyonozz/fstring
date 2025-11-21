# zuu::string - Compile-Time String Library v1.0

Modern C++20 compile-time string library dengan optimasi tinggi, zero-overhead abstractions, dan full STL compatibility.

## ✨ Features

- **🚀 Full Constexpr**: Semua operasi dapat dievaluasi pada compile-time
- **⚡ Zero Overhead**: Tidak ada dynamic allocation, stack-only
- **🎯 Type Safe**: Strong typing dengan C++20 concepts
- **🔧 STL Compatible**: Bekerja dengan algorithms dan ranges
- **📊 Rich API**: Lengkap dengan search, replace, transform, dll
- **🔄 Conversions**: to_string untuk integers/floats, interop dengan std::string
- **⚙️ Optimized**: Loop unrolling, efficient algorithms
- **📝 Well Documented**: Comprehensive documentation dengan examples

## 📋 Requirements

- **C++20 compiler**:
  - GCC 10+ 
  - Clang 12+
  - MSVC 19.28+ (Visual Studio 2019 16.8+)
- Standard library dengan full C++20 support

## 📦 Installation

### Header-Only Library

Cukup copy semua `.hpp` files ke project Anda:

```bash
# Clone repository
git clone https://github.com/yourusername/constant-string.git

# Copy headers to your project
cp constant-string/*.hpp your-project/include/
```

### CMake Integration

```cmake
# CMakeLists.txt
add_subdirectory(constant-string)
target_link_libraries(your_target PRIVATE zuu::string)
```

## 🚀 Quick Start

```cpp
#include "constant_string.hpp"
using namespace zuu::literals;

int main() {
    // Compile-time string creation
    constexpr auto hello = "Hello"_cs;
    constexpr auto world = "World"_cs;
    constexpr auto greeting = hello + " "_cs + world + "!"_cs;
    
    static_assert(greeting == "Hello World!"_cs);
    static_assert(greeting.length() == 12);
    static_assert(greeting.starts_with("Hello"));
    
    // Runtime operations (tetap efisien)
    zuu::cstring<100> dynamic("Runtime string");
    dynamic += " with append";
    dynamic.to_upper();
    
    // Convert integers
    auto num_str = zuu::to_string(2024);
    auto hex_str = zuu::to_string_base(0xFF, 16);
    
    std::cout << greeting.c_str() << std::endl;
    std::cout << dynamic.c_str() << std::endl;
    std::cout << num_str.c_str() << std::endl;
    
    return 0;
}
```

## 📚 Documentation

### Basic Operations

```cpp
// Construction
constexpr zuu::cstring<20> str1("Hello");
constexpr auto str2 = "World"_cs;
zuu::cstring<10> str3(5, 'x');  // "xxxxx"

// Concatenation
constexpr auto combined = str1 + " "_cs + str2;

// Access
char first = str1[0];
char last = str1.back();
const char* cstr = str1.c_str();

// Modification
zuu::cstring<50> text("Hello");
text += " World";
text.push_back('!');
text.insert(5, " Beautiful", 10);
text.erase(6, 10);
```

### Integer Conversions

```cpp
// To string
constexpr auto num = zuu::to_string(42);
constexpr auto hex = zuu::to_string_base(255, 16);  // "ff"
constexpr auto bin = zuu::to_string_base(10, 2);    // "1010"

static_assert(num == "42"_cs);

// From string
int value;
if (zuu::from_string(num, value)) {
    // value == 42
}

unsigned hex_val;
zuu::from_string(zuu::cstring<10>("FF"), hex_val, 16);
// hex_val == 255
```

### Floating Point

```cpp
auto pi = zuu::to_string(3.14159, 2);     // "3.14"
auto e = zuu::to_string(2.71828, 4);      // "2.7183"
auto sci = zuu::to_string(1.23e-4, 6);    // "0.000123"
```

### Search Operations

```cpp
constexpr zuu::cstring<50> text("The quick brown fox");

// Find substring
constexpr auto pos = text.find("quick");
static_assert(pos == 4);

// Find character
auto first_o = text.find('o');
auto last_o = text.rfind('o');
auto count_o = text.count('o');

// Prefix/Suffix checking
static_assert(text.starts_with("The"));
static_assert(text.ends_with("fox"));
static_assert(text.contains("brown"));
```

### String Transformations

```cpp
zuu::cstring<50> text("  Hello World  ");

// Case conversion
text.to_upper();    // "  HELLO WORLD  "
text.to_lower();    // "  hello world  "

// Whitespace trimming
text.trim();        // "hello world"
text.trim_left();   // "hello world  "
text.trim_right();  // "  hello world"

// Reverse
text.reverse();     // "dlrow olleh"

// Or create copies
auto upper = zuu::to_upper(text);
auto reversed = zuu::reversed(text);
```

### STL Interoperability

```cpp
// To std::string
zuu::cstring<50> cs("Hello");
std::string std_str = zuu::to_std_string(cs);
std::string_view view = zuu::to_string_view(cs);

// From std::string
std::string source("Hello");
auto back = zuu::from_std_string<50>(source);

// Works with STL algorithms
zuu::cstring<20> text("hello");
std::transform(text.begin(), text.end(), text.begin(), ::toupper);

// Range-based for loop
for (char c : text) {
    std::cout << c;
}
```

### Comparison and Hashing

```cpp
constexpr auto a = "apple"_cs;
constexpr auto b = "banana"_cs;

// Comparison operators (C++20 spaceship)
static_assert(a < b);
static_assert(a != b);

// Three-way comparison
int cmp = a.compare(b);  // -1, 0, or 1

// Hashing (FNV-1a)
constexpr auto hash = a.hash();
std::hash<decltype(a)> hasher;
std::size_t h = hasher(a);
```

## ⚡ Performance

### Compile-Time Evaluation

Semua operasi yang memungkinkan akan dievaluasi pada compile-time:

```cpp
// Semua ini terjadi pada compile-time!
constexpr auto result = []() {
    auto s = "Start"_cs;
    for (int i = 0; i < 5; ++i) {
        s += " "_cs + zuu::to_string(i);
    }
    return s;
}();

static_assert(result == "Start 0 1 2 3 4"_cs);
```

### Memory Layout

```cpp
sizeof(zuu::cstring<10>)  = 16 bytes  (10 + 1 + padding + length)
sizeof(zuu::cstring<100>) = 112 bytes (100 + 1 + padding + length)
sizeof(std::string)       = 32 bytes  (+ heap allocation)
```

**Advantages**:
- ✅ Stack allocation (cache-friendly)
- ✅ No heap fragmentation
- ✅ Predictable memory usage
- ✅ Fast construction/destruction

### Optimization Tips

```cpp
// ✅ Good: Konstanta kapasitas, compile-time evaluation
constexpr zuu::cstring<100> optimal("text");

// ⚠️ Okay: Runtime dengan kapasitas tetap
zuu::cstring<100> runtime;
runtime += "dynamic";

// ❌ Avoid: Terlalu besar tanpa alasan
zuu::cstring<10000> wasteful;  // 10KB per string!

// ✅ Better: Sesuaikan kapasitas dengan kebutuhan
zuu::cstring<50> sufficient;
```

## 🏗️ Architecture

### File Organization

```
constant_string.hpp                 # Main header (include this)
├── constant_string_fwd.hpp         # Forward declarations
├── constant_string_traits.hpp      # Type traits & concepts
├── constant_string_detail.hpp      # Internal utilities
├── constant_string_iterator.hpp    # Iterator implementation
├── constant_string_core.hpp        # Core string class
├── constant_string_algorithms.hpp  # Search & algorithms
├── constant_string_conversions.hpp # to_string, from_string
└── constant_string_literals.hpp    # User-defined literals
```

### Design Principles

1. **Header-Only**: Easy integration
2. **Modular**: Clean separation of concerns
3. **Constexpr First**: Maximum compile-time evaluation
4. **Zero Cost**: No runtime overhead untuk compile-time ops
5. **STL Compatible**: Drop-in replacement dimana applicable

## 🧪 Testing

```bash
# Compile examples
g++ -std=c++20 -O3 -o example example.cpp
./example

# Advanced examples
g++ -std=c++20 -O3 -o example_advanced example_advanced.cpp
./example_advanced

# With optimizations
g++ -std=c++20 -O3 -march=native -o example_advanced example_advanced.cpp
```

## 🤝 Contributing

Contributions welcome! Please:

1. Fork repository
2. Create feature branch
3. Add tests
4. Submit pull request

## 📄 License

MIT License - see LICENSE file for details

## 🔗 Links

- **Documentation**: [Full API Reference](docs/)
- **Examples**: [examples/](examples/)
- **Issues**: [GitHub Issues](https://github.com/yourusername/constant-string/issues)

## 📊 Comparison

| Feature | zuu::string | std::string | std::string_view |
|---------|------------|-------------|------------------|
| Compile-time | ✅ Full | ❌ Limited | ✅ Partial |
| Mutable | ✅ Yes | ✅ Yes | ❌ No |
| Capacity | Fixed | Dynamic | View only |
| Allocation | Stack | Heap (SSO) | None |
| Overhead | Zero | Small | Zero |
| to_string | ✅ Built-in | stdlib | N/A |

## 💡 Use Cases

- ✅ **Compile-time configuration strings**
- ✅ **Embedded systems** (no heap allocation)
- ✅ **Template metaprogramming**
- ✅ **Performance-critical code** (stack allocation)
- ✅ **Constexpr algorithms**
- ⚠️ **Large text processing** (use std::string instead)
- ⚠️ **Unknown size data** (use std::string instead)

## 📈 Roadmap

- [x] Basic string operations
- [x] Integer/float conversions
- [x] STL compatibility
- [x] Search algorithms
- [x] Hash support
- [ ] Regular expressions (simplified, constexpr)
- [ ] Unicode support
- [ ] Split/join operations
- [ ] Advanced formatting

## 🙏 Acknowledgments

Inspired by various compile-time string libraries dan modern C++ best practices.

---

**Made with ❤️ using C++20**
