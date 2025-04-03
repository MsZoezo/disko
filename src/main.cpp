#include <config.hpp>
#include <filesystem>
#include<memory.h>
#include<string.h>

int main() {
    const char *homedir;

    if((homedir = getenv("$XDG_CONFIG_HOME")) == NULL) {
        homedir = getenv("HOME");
    }

    std::filesystem::path configPath = homedir;
    configPath /= ".disko/config.toml";

    std::unique_ptr<Config> cfg = Config::parse(configPath);

    if(!cfg) return 1;

    return 0;
}