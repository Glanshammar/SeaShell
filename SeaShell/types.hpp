#pragma once

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>


class Command;

using Arguments = const std::vector<std::string>&;
using Options = const std::vector<std::string>&;
using CommandPtr = std::unique_ptr<Command>;
using CommandRegistry = std::unordered_map<std::string, CommandPtr>;

class Command {
public:
    virtual ~Command() = default;
    
    virtual void execute(Arguments args, Options opts) = 0;
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual std::string getUsage() const = 0;
    virtual std::string getCategory() const { return "general"; }
    virtual bool isAvailable() const { return true; }
};