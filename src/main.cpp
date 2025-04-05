#include <config.hpp>
#include <filesystem>
#include<memory.h>
#include<string.h>
#include <logger.hpp>
#include <dpp/dpp.h>
#include<commandhandler.hpp>
#include<commands/ping.hpp>

std::filesystem::path getConfigPath() {
    const char *homedir;

    if((homedir = getenv("$XDG_CONFIG_HOME")) == NULL) {
        homedir = getenv("HOME");
    }

    std::filesystem::path configPath = homedir;
    configPath /= ".disko/config.toml";

    return configPath;
}

void initCommands(Commandhandler& cmdHandler) {
    cmdHandler.addCommand(new PingCommand());
}

int main() {
    Commandhandler cmdHandler;

    initCommands(cmdHandler);

    std::filesystem::path configPath = getConfigPath();

    std::unique_ptr<Config> cfg = Config::parse(configPath);

    if(!cfg) return 1;

    auto token = cfg->retrieve<std::string>("bot", "token");

    if(!token.has_value()) {
        Logger::error("Main", "Bot token missing from config");
        return 2;
    }

    dpp::cluster bot(token.value());

    bot.on_log(Logger::initBotLogging());
 
    bot.on_slashcommand([cmdHandler](const dpp::slashcommand_t& event) {
        cmdHandler.handleEvent(event);
    });
 
    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            Logger::log("Main", "Registering commands...");
            // bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
        }
    });

    Logger::log("Main", "Starting bot...");

    bot.start(dpp::st_wait);

    return 0;
}