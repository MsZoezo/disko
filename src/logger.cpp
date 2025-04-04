#include<logger.hpp>

void Logger::print(const fmt::text_style& style, const std::string& str) {
    auto timestamp = std::chrono::system_clock::now();

    fmt::print(style, "[{:%Y-%m-%d %H:%M:%S}] {}\n", timestamp, str);
}

void Logger::error(const std::string& str) {
    Logger::print(fg(fmt::color::red), str);
}

void Logger::log(const std::string &str) {
    Logger::print(fg(fmt::color::light_gray), str);
}

void Logger::info(const std::string &str) {
    Logger::print(fg(fmt::color::light_blue), str);
}