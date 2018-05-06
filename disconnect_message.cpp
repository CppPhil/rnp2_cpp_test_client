#include "disconnect_message.hpp"
#include <QJsonDocument>
#include <QJsonObject>

DisconnectMessage::DisconnectMessage() : m_messageKind{"disconnect"} {}

boost::optional<DisconnectMessage> DisconnectMessage::fromJson(
    const QString& json)
{
    QJsonDocument doc = QJsonDocument::fromJson(json.toLocal8Bit());

    if (!doc.isObject()) { return boost::none; }

    QJsonObject obj = doc.object();

    if (!obj.contains("messageKind")) { return boost::none; }

    if (!obj["messageKind"].isString()) { return boost::none; }

    if (obj["messageKind"].toString() != "disconnect") { return boost::none; }

    return boost::make_optional(DisconnectMessage{});
}

const QString& DisconnectMessage::messageKind() const { return m_messageKind; }

QString DisconnectMessage::asJson() const
{
    QJsonObject obj;
    obj["messageKind"] = m_messageKind;
    QJsonDocument doc{obj};
    return doc.toJson(QJsonDocument::Compact);
}
