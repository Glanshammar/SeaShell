#include "python.hpp"

void RunPythonScript(const CommandArgs& args) {
    std::string scriptPath = args.isEmpty() ? "scripts/hello.py" : args.getArg(0);
    std::string command = "exec(open('" + scriptPath + "').read())";
    Py_Initialize();
    PyRun_SimpleString(command.c_str());
    Py_Finalize();
}