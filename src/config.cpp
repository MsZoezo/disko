#include<config.hpp>

std::unique_ptr<Config> Config::parse(std::string filename)
{
    Logger::log("Config", "Checking if config file exists...");
    // Check if the file exists
    struct stat buffer;   
    if(stat(filename.c_str(), &buffer) != 0) {
        Logger::error("Config", fmt::format("Config file doesn't exist, please create one\n'{}'\n", filename));
        return nullptr;
    }

    std::unique_ptr<Config> cfg (new Config());

    Logger::log("Config", "Parsing config file...");

    try {
        cfg->tbl = toml::parse_file(filename);

    } catch(const toml::parse_error& err) {
        Logger::error("Config", fmt::format("Error parsing config file\n\t{}\n\t(Error occured at line {}, column {})", err.description(), err.source().begin.line, err.source().begin.column));
        return nullptr;
    }

    return cfg;
}