#include<config.hpp>

std::unique_ptr<Config> Config::parse(std::string filename)
{
    // Check if the file exists
    struct stat buffer;   
    if(stat(filename.c_str(), &buffer) != 0) {
        fmt::print("Config file doesn't exist, please create one\n'{}'\n", filename);
        return nullptr;
    }

    std::unique_ptr<Config> cfg (new Config());

    try {
        cfg->tbl = toml::parse_file(filename);

    } catch(const toml::parse_error& err) {
        fmt::print(fmt::emphasis::bold | bg(fmt::color::red), " Error parsing config file ");
        fmt::print("\n\n{}\n", err.description());
        fmt::print(fg(fmt::color::purple), "(Error occured at line {}, column {})\n\n", err.source().begin.line, err.source().begin.column);
        return nullptr;
    }

    return cfg;
}