#pragma once

#include "../types.hpp"
#include <Poco/Zip/Compress.h>
#include <Poco/Zip/Decompress.h>
#include <Poco/Zip/ZipArchive.h>
#include <Poco/Path.h>
#include <Poco/DirectoryIterator.h>


using namespace Poco;
using namespace Poco::Zip;

void ZIP(const CommandArgs& args);
void UnZIP(const CommandArgs& args);