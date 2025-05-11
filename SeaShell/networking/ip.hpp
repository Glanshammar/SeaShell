#pragma once

#include "../common.hpp"
#include "../types.hpp"

#include <Poco/Net/NetworkInterface.h>
#include <Poco/Net/IPAddress.h>
#include <Poco/Exception.h>

void ListInterfaces(const CommandArgs& args);