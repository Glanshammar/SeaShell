#include "../common.hpp"
#include "../utils.hpp"
#include "../platform.hpp"
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


void KillProcess(Arguments args, Options options)
{    
    if(args.empty()) {
        cout << "No process ID provided." << endl;
        return;
    }
    
    if(args[0] == "self")
    {
        OpenURL("https://youtu.be/2dbR2JZmlWo?si=Sbb9kpW3uBt4xBFp");
        cout << "Please do it." << endl;
    } else if(isNumeric(args[0]))
    {
        TerminateProcessByID(stoi(args[0]));
        cout << "Process terminated: " << args[0] << endl;
    } else {
        cout << "Invalid process ID. Must be a number or 'self'." << endl;
    }
}


void ListProcesses(Arguments args, Options options)
{    
#ifdef _WIN32
    const string command = "tasklist"; // Windows command to list processes
#else
    const string command = "/bin/ps"; // Unix command to list processes
#endif
    Pipe outPipe;
    ProcessHandle ph = Process::launch(command, {}, nullptr, &outPipe, nullptr);
    PipeInputStream istr(outPipe);
    StreamCopier::copyStream(istr, cout);
    cout << endl;
}