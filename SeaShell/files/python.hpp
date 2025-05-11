#pragma once

// Python.h redefines _XOPEN_SOURCE, undefine it to avoid conflict
#ifdef _XOPEN_SOURCE
#undef _XOPEN_SOURCE
#endif

#include <Python.h>
#include "../common.hpp"
#include "../types.hpp"

void RunPythonScript(const CommandArgs& args);
