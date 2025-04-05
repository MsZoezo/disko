#ifndef COMMAND_HPP
#define COMMAND_HPP

#include<string>
#include<dpp/dpp.h>

class Command {
    public:        
        virtual void run(const dpp::slashcommand_t& event) = 0;
        virtual dpp::slashcommand getCommand(const dpp::cluster& bot) = 0;

        virtual std::string getCommandName() { return "Unset"; }
};

#endif