#ifndef DISCONNECT_MESSAGE_HPP
#define DISCONNECT_MESSAGE_HPP
#include <QString>
#include <boost/optional.hpp>

class DisconnectMessage {
public:
    DisconnectMessage();

    static boost::optional<DisconnectMessage> fromJson(const QString& json);

    const QString& messageKind() const;

    QString asJson() const;

private:
    QString m_messageKind;
};
#endif // DISCONNECT_MESSAGE_HPP
