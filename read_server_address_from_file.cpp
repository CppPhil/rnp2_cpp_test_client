#include "read_server_address_from_file.hpp"
#include <cstring>
#include <fstream>

boost::optional<std::string> readServerAddressFromFile(
    const std::string& filePath)
{
    std::ifstream ifs{filePath};
    if (!ifs) { return boost::none; }

    std::string s;
    std::getline(ifs, s);

    if (!ifs) { return boost::none; }

    const char a[] = "server_address:";

    auto p = std::strstr(s.data(), a);

    if (p == nullptr) { return boost::none; }

    p += (sizeof(a) - 1U);

    return boost::make_optional(std::string(p));
}
