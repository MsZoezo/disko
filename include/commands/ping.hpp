#ifndef PING_HPP
#define PING_HPP

#include<string>
#include<dpp/dpp.h>
#include<command.hpp>

class PingCommand : public Command {
    public:
        std::string getCommandName() override { return "ping"; }
        
        void run(const dpp::slashcommand_t& event);
        dpp::slashcommand getCommand(const dpp::cluster& bot);
};

#endif