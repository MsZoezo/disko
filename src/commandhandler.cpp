#include<commandhandler.hpp>

Commandhandler &Commandhandler::addCommand(Command* cmd)
{
    std::string commandName = cmd->getCommandName();

    if(this->commands.contains(commandName)) {
        Logger::error(fmt::format("Tried to add command '{}' to the commandHandler, but it already exists", commandName));
        return *this;
    }

    this->commands.emplace(commandName, std::shared_ptr<Command>(cmd));

    return *this;
}

void Commandhandler::handleEvent(const dpp::slashcommand_t &event) const {
    std::string commandName = event.command.get_command_name();

    dpp::user* user = event.command.member.get_user();

    Logger::log(fmt::format("User {}[{}] ran '{}' command", user->username, user->id, commandName));

    if(!this->commands.contains(commandName)) {
        Logger::error(fmt::format("There is no command to handle for '{}'", commandName));
        event.reply(dpp::message("I'm sorry! This command can't be handled right now...").set_flags(dpp::m_ephemeral));
        return;
    }

    auto cmd = this->commands.at(commandName);

    cmd->run(event);
}
