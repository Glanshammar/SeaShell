#pragma once

#include "../global.hpp"
#include <libzippp/libzippp.h>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/bzip2.hpp>  // Adjust filter based on your archive format
#include <boost/filesystem.hpp>

using namespace libzippp;
namespace io = boost::iostreams;
namespace fs = boost::filesystem;

void ZIP(Arguments args, Options options);
void UnZIP(Arguments args, Options options);