#pragma once

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <functional>



class CommandArgs {
public:
    std::vector<std::string> args;
    std::map<std::string, std::string> options;
    
    // Check if an option exists
    bool hasOption(const std::string& name) const {
        return options.find(name) != options.end();
    }
    
    // Get option value with default
    std::string getOption(const std::string& name, const std::string& defaultValue = "") const {
        auto it = options.find(name);
        return (it != options.end()) ? it->second : defaultValue;
    }
    
    // Get option as integer with default
    int getIntOption(const std::string& name, int defaultValue = 0) const {
        auto it = options.find(name);
        if (it != options.end()) {
            try {
                return std::stoi(it->second);
            } catch (...) {
                return defaultValue;
            }
        }
        return defaultValue;
    }
    
    // Get option as boolean
    bool getBoolOption(const std::string& name, bool defaultValue = false) const {
        auto it = options.find(name);
        if (it != options.end()) {
            std::string val = it->second;
            std::transform(val.begin(), val.end(), val.begin(), ::tolower);
            return (val == "true" || val == "yes" || val == "1" || val.empty());
        }
        return defaultValue;
    }
    
    // Get argument at index with default value
    std::string getArg(size_t index, const std::string& defaultValue = "") const {
        return (index < args.size()) ? args[index] : defaultValue;
    }
    
    // Get number of arguments
    size_t argCount() const {
        return args.size();
    }
    
    // Check if arguments are empty
    bool isEmpty() const {
        return args.empty();
    }
};

// Function type for command handlers
using CommandFunction = std::function<void(const CommandArgs& args)>;