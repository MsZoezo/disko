#ifndef CONFIG_HPP
#define CONFIG_HPP

#include<fmt/printf.h>
#include<fmt/color.h>
#include<toml++/toml.hpp>
#include<sys/stat.h>
#include<memory.h>
#include<logger.hpp>


class Config {
    private:
        toml::table tbl;

    public:
        static std::unique_ptr<Config> parse(std::string filename);

        template<typename T>
        std::optional<T> retrieve(std::string section, std::string token);
};

template <typename T>
inline std::optional<T> Config::retrieve(std::string section, std::string token)
{
    std::optional<T> value = this->tbl[section][token].value<T>();

    if(!value.has_value()) {
        fmt::print(fg(fmt::color::gray), "({} -> {}) was accessed, but is not defined.\n", section, token);
    }

    return value;
}

#endif