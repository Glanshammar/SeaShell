#include "python.hpp"

#define PY_SSIZE_T_CLEAN

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <sys/types.h>
#include <signal.h>
#endif

std::map<string, string> scriptMap = {
    {"test", std::filesystem::path(getenv("HOME")) / "Documents" / "script.py"},
};


void RunPythonScript(Arguments args, Options options) {
    wchar_t* program = Py_DecodeLocale("SeaShell", nullptr);

    if(program == nullptr) {
        cout << "Fatal error: cannot decode script path." << std::endl;
        exit(1);
    }

    PyConfig config;
    PyConfig_InitPythonConfig(&config);
    PyConfig_SetString(&config, &config.program_name, program);
    Py_InitializeFromConfig(&config);
    PyConfig_Clear(&config);

    std::string pyPath;
    if (scriptMap.find(args[0]) != scriptMap.end()) {
        pyPath = scriptMap[args[0]];
    } else {
        pyPath = args[0];
    }

    string commandPath = "exec(open('" + pyPath + "').read())";
    PyRun_SimpleString(commandPath.c_str());

    if(Py_FinalizeEx() < 0) {
        exit(120);
    }

    PyMem_RawFree(program);
}