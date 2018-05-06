#include "chat_message.hpp"
#include <QJsonDocument>
#include <QJsonObject>

ChatMessage::ChatMessage(QString message, QString senderName)
    : m_message{std::move(message)}
    , m_messageKind{"chat"}
    , m_senderName{std::move(senderName)}
{
}

boost::optional<ChatMessage> ChatMessage::fromJson(const QString& json)
{
    const QJsonDocument doc{QJsonDocument::fromJson(json.toLocal8Bit())};

    if (!doc.isObject()) { return boost::none; }

    const QJsonObject o{doc.object()};

    if (!o.contains("message") || !o.contains("messageKind")
        || !o.contains("senderName")) {
        return boost::none;
    }

    if (!o["message"].isString() || !o["messageKind"].isString()
        || !o["senderName"].isString()) {
        return boost::none;
    }

    if (o["messageKind"].toString() != "chat") { return boost::none; }

    return boost::make_optional(
        ChatMessage{o["message"].toString(), o["senderName"].toString()});
}

const QString& ChatMessage::message() const { return m_message; }

const QString& ChatMessage::messageKind() const { return m_messageKind; }

const QString& ChatMessage::senderName() const { return m_senderName; }

QString ChatMessage::asJson() const
{
    QJsonObject obj;
    obj["message"]     = m_message;
    obj["messageKind"] = m_messageKind;
    obj["senderName"]  = m_senderName;
    const QJsonDocument doc{obj};
    return doc.toJson(QJsonDocument::Compact);
}
