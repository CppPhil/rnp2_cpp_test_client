#ifndef READ_SERVER_ADDRESS_FROM_FILE_HPP
#define READ_SERVER_ADDRESS_FROM_FILE_HPP
#include <boost/optional.hpp>
#include <string>

boost::optional<std::string> readServerAddressFromFile(
    const std::string& filePath);
#endif // READ_SERVER_ADDRESS_FROM_FILE_HPP
