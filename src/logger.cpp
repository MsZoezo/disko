#include<logger.hpp>

void Logger::print(const fmt::text_style& style, const std::string& domain, const std::string& str) {
    auto timestamp = std::chrono::system_clock::now();

    fmt::print(style, "[{:%Y-%m-%d %H:%M:%S}] {}\n{}\n\n", timestamp, domain, str);
}

void Logger::error(const std::string& domain, const std::string& str) {
    Logger::print(fg(fmt::color::red), domain, str);
}

void Logger::log(const std::string& domain, const std::string &str) {
    Logger::print(fg(fmt::color::light_gray), domain, str);
}

void Logger::info(const std::string& domain, const std::string &str) {
    Logger::print(fg(fmt::color::light_blue), domain, str);
}

std::function<void(const dpp::log_t &)> Logger::initBotLogging()
{
    return [](const dpp::log_t& event) {
        switch (event.severity)
        {
        case dpp::ll_trace:
            break;
        
        case dpp::ll_debug:
            Logger::log("Bot", event.message);
            break;

        case dpp::ll_info:
            Logger::info("Bot", event.message);
            break;

        case dpp::ll_warning:
            Logger::log("Bot", event.message);
            break;

        case dpp::ll_critical:
        case dpp::ll_error:
            Logger::error("Bot", event.message);
            break;
        }
    };
}
