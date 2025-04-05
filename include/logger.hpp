#ifndef LOGGER_HPP
#define LOGGER_HPP

#include<fmt/color.h>
#include<fmt/chrono.h>
#include<fmt/printf.h>
#include <fmt/core.h>
#include<functional>
#include<dpp/dpp.h>


class Logger {
    private:
        static void print(const fmt::text_style& ts, const std::string& domain, const std::string& str);

    public:
        static void error(const std::string& domain, const std::string& str);
        static void log(const std::string& domain, const std::string& str);
        static void info(const std::string& domain, const std::string& str);

        static std::function<void(const dpp::log_t&)> initBotLogging();
};

#endif


