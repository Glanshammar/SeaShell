#pragma once

#include "../common.hpp"
#include "../types.hpp"
#include "../utils.hpp"

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

using namespace Poco;
using Poco::Process;
using Poco::ProcessHandle;
using Poco::Pipe;
using Poco::PipeInputStream;
using Poco::StreamCopier;

void KillProcess(Arguments args, Options options);
void ListProcesses(Arguments args, Options options);