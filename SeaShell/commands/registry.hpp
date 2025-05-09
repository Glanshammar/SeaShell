#pragma once

#include "../types.hpp"
#include <memory>
#include <stdexcept>

namespace commands {

class CommandRegistry {
public:
    static CommandRegistry& getInstance() {
        static CommandRegistry instance;
        return instance;
    }

    // Register a new command
    void registerCommand(CommandPtr cmd) {
        if (!cmd) {
            throw std::invalid_argument("Cannot register null command");
        }
        registry_[cmd->getName()] = std::move(cmd);
    }

    // Get a command by name
    Command* getCommand(const std::string& name) const {
        auto it = registry_.find(name);
        return it != registry_.end() ? it->second.get() : nullptr;
    }

    // Execute a command
    bool executeCommand(const std::string& name, Arguments args, Options opts) {
        if (auto* cmd = getCommand(name)) {
            if (cmd->isAvailable()) {
                cmd->execute(args, opts);
                return true;
            }
        }
        return false;
    }

    // Get all commands
    const std::unordered_map<std::string, CommandPtr>& getRegistry() const { return registry_; }

    // Get commands by category
    std::vector<Command*> getCommandsByCategory(const std::string& category) const {
        std::vector<Command*> result;
        for (const auto& [name, cmd] : registry_) {
            if (cmd->getCategory() == category) {
                result.push_back(cmd.get());
            }
        }
        return result;
    }

private:
    CommandRegistry() = default;
    ~CommandRegistry() = default;
    CommandRegistry(const CommandRegistry&) = delete;
    CommandRegistry& operator=(const CommandRegistry&) = delete;

    std::unordered_map<std::string, CommandPtr> registry_;
};

} // namespace commands 