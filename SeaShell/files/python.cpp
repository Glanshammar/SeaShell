#include "python.hpp"

void RunPythonScript(Arguments args, Options options) {
    std::string scriptPath = args.empty() ? "scripts/hello.py" : args[0];
    std::string command = "exec(open('" + scriptPath + "').read())";
    Py_Initialize();
    PyRun_SimpleString(command.c_str());
    Py_Finalize();
}