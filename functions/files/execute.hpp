#ifndef EXECUTE_HPP
#define EXECUTE_HPP

#include "boost/process.hpp"
#include <boost/filesystem.hpp>
#include <boost/asio.hpp>
#include "../../global.hpp"

void ExecuteFile(const vector<string>& args, const vector<string>& options);

#endif //EXECUTE_HPP
