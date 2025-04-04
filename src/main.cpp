#include <config.hpp>
#include <filesystem>
#include<memory.h>
#include<string.h>
#include <logger.hpp>
#include <dpp/dpp.h>

std::filesystem::path getConfigPath() {
    const char *homedir;

    if((homedir = getenv("$XDG_CONFIG_HOME")) == NULL) {
        homedir = getenv("HOME");
    }

    std::filesystem::path configPath = homedir;
    configPath /= ".disko/config.toml";

    return configPath;
}

int main() {
    std::filesystem::path configPath = getConfigPath();

    std::unique_ptr<Config> cfg = Config::parse(configPath);

    if(!cfg) return 1;

    auto token = cfg->retrieve<std::string>("bot", "token");

    if(!token.has_value()) {
        Logger::error("Bot token missing from config");
        return 2;
    }

    dpp::cluster bot(token.value());

    bot.on_log([](const dpp::log_t& event) {
        switch (event.severity)
        {
        case dpp::ll_trace:
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
    });
 
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
    });
 
    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
        }
    });

    bot.start(dpp::st_wait);

    return 0;
}