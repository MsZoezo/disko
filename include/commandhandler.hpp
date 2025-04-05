#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include<command.hpp>
#include<logger.hpp>

class Commandhandler {
    private:
        std::unordered_map<std::string, std::shared_ptr<Command>> commands;

    public:
        Commandhandler& addCommand(Command* cmd);

        void handleEvent(const dpp::slashcommand_t& event) const;
        void registerCommands();

};

#endif