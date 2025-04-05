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

std::function<void(const dpp::log_t &)> Logger::initBotLogging()
{
    return [](const dpp::log_t& event) {
        switch (event.severity)
        {
        case dpp::ll_trace:
            break;
        
        case dpp::ll_debug:
            Logger::log(event.message);
            break;

        case dpp::ll_info:
            Logger::info(event.message);
            break;

        case dpp::ll_warning:
            Logger::log(event.message);
            break;

        case dpp::ll_critical:
        case dpp::ll_error:
            Logger::error(event.message);
            break;
        }
    };
}
