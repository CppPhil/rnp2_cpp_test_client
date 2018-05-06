#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP
#include <QString>
#include <boost/optional.hpp>

class ChatMessage {
public:
    ChatMessage(QString message, QString senderName);

    static boost::optional<ChatMessage> fromJson(const QString& json);

    const QString& message() const;

    const QString& messageKind() const;

    const QString& senderName() const;

    QString asJson() const;

private:
    QString m_message;
    QString m_messageKind;
    QString m_senderName;
};

#endif // CHAT_MESSAGE_HPP
