#include "connect_message.hpp"
#include <QJsonDocument>
#include <QJsonObject>

ConnectMessage::ConnectMessage(QString userName)
    : m_messageKind{"connect"}, m_userName{std::move(userName)}
{
}

boost::optional<ConnectMessage> ConnectMessage::fromJson(const QString& json)
{
    QJsonDocument doc = QJsonDocument::fromJson(json.toLocal8Bit());
    if (!doc.isObject()) { return boost::none; }

    QJsonObject obj = doc.object();

    if (!obj.contains("messageKind")) { return boost::none; }

    if (!obj.contains("userName")) { return boost::none; }

    if (!obj["messageKind"].isString()) { return boost::none; }

    if (!obj["userName"].isString()) { return boost::none; }

    if (obj["messageKind"].toString() != "connect") { return boost::none; }

    return ConnectMessage{obj["userName"].toString()};
}

const QString& ConnectMessage::messageKind() const { return m_messageKind; }

const QString& ConnectMessage::userName() const { return m_userName; }

QString ConnectMessage::asJson() const
{
    QJsonObject obj;
    obj["messageKind"] = m_messageKind;
    obj["userName"]    = m_userName;
    const QJsonDocument doc{obj};
    return QString{doc.toJson(QJsonDocument::Compact)};
}
