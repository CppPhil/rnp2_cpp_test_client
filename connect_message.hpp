#ifndef CONNECT_MESSAGE_HPP
#define CONNECT_MESSAGE_HPP
#include <QString>
#include <boost/optional.hpp>

class ConnectMessage {
public:
    explicit ConnectMessage(QString userName);

    static boost::optional<ConnectMessage> fromJson(const QString& json);

    const QString& messageKind() const;

    const QString& userName() const;

    QString asJson() const;

private:
    QString m_messageKind;
    QString m_userName;
};
#endif // CONNECT_MESSAGE_HPP
