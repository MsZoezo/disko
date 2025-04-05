#include<commands/ping.hpp>


void PingCommand::run(const dpp::slashcommand_t &event) {
    event.reply("Pong!");
}

dpp::slashcommand PingCommand::getCommand(const dpp::cluster& bot) {
    return dpp::slashcommand("ping", "Ping pong!", bot.me.id);
}