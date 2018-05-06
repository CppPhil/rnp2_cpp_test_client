#ifndef READ_USER_NAME_FROM_FILE_HPP
#define READ_USER_NAME_FROM_FILE_HPP
#include <boost/optional.hpp>
#include <string>

boost::optional<std::string> readUserNameFromFile(
    const std::string& filePath) noexcept;

#endif // READ_USER_NAME_FROM_FILE_HPP
