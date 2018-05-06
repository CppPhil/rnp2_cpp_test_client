#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <QString>
#include <boost/optional.hpp>

class Client {
public:
    Client(QString ip, QString userName);

    static boost::optional<Client> fromJson(const QString& json);

    const QString& ip() const;
    const QString& userName() const;

    QString asJson() const;

private:
    QString m_ip;
    QString m_userName;
};

#endif // CLIENT_HPP
