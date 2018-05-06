#ifndef NETSTRING_HPP
#define NETSTRING_HPP
#include <boost/optional.hpp>
#include <iosfwd>
#include <string>

class Netstring {
public:
    explicit Netstring(std::string s);

    static boost::optional<Netstring> fromNetStringData(
        const void* p,
        std::size_t byteCount);

    const std::string& str() const;

    friend std::ostream& operator<<(std::ostream& os, const Netstring& ns);

private:
    std::string m_str;
};
#endif // NETSTRING_HPP
