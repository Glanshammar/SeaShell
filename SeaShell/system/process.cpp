#include "../common.hpp"
#include "../utils.hpp"
#include "../platform.hpp"
#include "../types.hpp"
#include "process.hpp"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
void TerminateProcessByID(const DWORD pid) {
    if (const HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid)) {
        TerminateProcess(hProcess, 0);
        CloseHandle(hProcess);
    }
}
#else
#include <csignal>
#include <unistd.h>
void TerminateProcessByID(pid_t pid) {
    kill(pid, SIGTERM); // Sends termination signal
}
#endif


void KillProcess(const CommandArgs& args)
{    
    if (args.isEmpty()) {
        std::cout << "No process ID provided." << std::endl;
        return;
    }
    
    const std::string& target = args.getArg(0);
    
    if (target == "self") {
        OpenURL("https://youtu.be/2dbR2JZmlWo?si=Sbb9kpW3uBt4xBFp");
        std::cout << "Please do it." << std::endl;
    } else if (isNumeric(target)) {
        bool force = args.hasOption("f") || args.hasOption("force");
        
        if (force) {
            std::cout << "Force terminating process: " << target << std::endl;
            // Could use SIGKILL instead of SIGTERM for force
        }
        
        TerminateProcessByID(std::stoi(target));
        std::cout << "Process terminated: " << target << std::endl;
    } else {
        std::cout << "Invalid process ID. Must be a number or 'self'." << std::endl;
        std::cout << "Usage: kill [options] <pid|self>" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  -f, --force    Force terminate the process" << std::endl;
    }
}


void ListProcesses(const CommandArgs& args)
{    
    bool showAll = args.hasOption("a") || args.hasOption("all");
    bool showDetails = args.hasOption("l") || args.hasOption("long");
    
#ifdef _WIN32
    std::string command = "tasklist";
    if (showDetails) {
        command += " /v"; // Verbose output
    }
#else
    std::string command = "/bin/ps";
    if (showAll) {
        command += " -e"; // Show all processes
    }
    if (showDetails) {
        command += " -l"; // Long format
    }
#endif
    
    Pipe outPipe;
    ProcessHandle ph = Process::launch(command, {}, nullptr, &outPipe, nullptr);
    PipeInputStream istr(outPipe);
    StreamCopier::copyStream(istr, std::cout);
    std::cout << std::endl;
}