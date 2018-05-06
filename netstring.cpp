#include "netstring.hpp"
#include <algorithm>
#include <boost/lexical_cast.hpp>
#include <ostream>

Netstring::Netstring(std::string s) : m_str{std::move(s)} {}

boost::optional<Netstring> Netstring::fromNetStringData(
    const void* p,
    std::size_t byteCount)
{
    const char* const begin = static_cast<const char*>(p);
    const char* const end   = begin + byteCount;

    auto it = std::find(begin, end, ':');

    if (it == end) { return boost::none; }

    const std::string sizeAsString(begin, it);
    std::size_t       size{0};

    try {
        size = boost::lexical_cast<std::size_t>(sizeAsString);
    }
    catch (const boost::bad_lexical_cast&) {
        return boost::none;
    }

    ++it; // skip the colon

    const char* const endOfNestedMsg = it + size;
    const std::string nestedMsg(it, endOfNestedMsg);

    it += size;

    if (it != (end - 1)) { return boost::none; }

    if (*(end - 1) != ',') { return boost::none; }

    return boost::make_optional(Netstring{nestedMsg});
}

const std::string& Netstring::str() const { return m_str; }

std::ostream& operator<<(std::ostream& os, const Netstring& ns)
{
    os << ns.str().size() << ':' << ns.str() << ',';
    return os;
}
