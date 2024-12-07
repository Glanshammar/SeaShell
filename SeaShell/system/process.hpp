#pragma once

#include <Poco/Process.h>
#include <Poco/Exception.h>
#include <Poco/Pipe.h>
#include <Poco/PipeStream.h>
#include <Poco/StreamCopier.h>
#include <tlhelp32.h>
#include <global.hpp>

using namespace Poco;

void KillProcess(Arguments args, Options options);
void ListProcesses(Arguments args, Options options);