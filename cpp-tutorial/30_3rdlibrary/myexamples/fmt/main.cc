#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/os.h>
#include <fmt/ranges.h>

#include <vector>

int main() {
    fmt::print("Hello, world!\n");
    std::vector<int> v = {1, 2, 3};
    fmt::print("{}\n", v);

    // auto out = fmt::output_file("guide.txt");
    // out.print("Don't {}", "Panic");

    fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
               "Hello, {}!\n", "world");
    fmt::print(fg(fmt::color::floral_white) | bg(fmt::color::slate_gray) |
                   fmt::emphasis::underline,
               "Hello, {}!\n", "мир");
    fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic,
               "Hello, {}!\n", "世界");

    using namespace std::literals::chrono_literals;
    fmt::print("Default format: {} {}\n", 42s, 100ms);
    fmt::print("strftime-like format: {:%H:%M:%S}\n", 3h + 15min + 30s);

    std::string s = fmt::format("The answer is {}.", 42);
    // s == "The answer is 42."
    fmt::print(s);
    std::string s1 = fmt::format("I'd rather be {1} than {0}.", "right", "happy");
    // s == "I'd rather be happy than right."
    fmt::print(s1);
}