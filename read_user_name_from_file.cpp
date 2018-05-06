#include "read_user_name_from_file.hpp"
#include <boost/algorithm/string/trim_all.hpp>
#include <fstream>

boost::optional<std::string> readUserNameFromFile(
    const std::string& filePath) noexcept
{
    std::ifstream ifs{filePath};

    if (!ifs) { return boost::none; }

    std::string s;
    std::getline(ifs, s);

    if (!ifs) { return boost::none; }

    return boost::make_optional(boost::algorithm::trim_all_copy(s));
}
