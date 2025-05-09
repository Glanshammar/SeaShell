#pragma once

#include <Poco/Process.h>
#include <Poco/Exception.h>
#include <Poco/Pipe.h>
#include <Poco/PipeStream.h>
#include <Poco/StreamCopier.h>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <sys/types.h>
#include <signal.h>
#endif
#include "../types.hpp"

using namespace Poco;

void KillProcess(Arguments args, Options options);
void ListProcesses(Arguments args, Options options);