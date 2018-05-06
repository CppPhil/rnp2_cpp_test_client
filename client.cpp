#include "client.hpp"
#include <QJsonDocument>
#include <QJsonObject>

Client::Client(QString ip, QString userName)
    : m_ip{std::move(ip)}, m_userName{std::move(userName)}
{
}

boost::optional<Client> Client::fromJson(const QString& json)
{
    const QJsonDocument doc{QJsonDocument::fromJson(json.toLocal8Bit())};

    if (!doc.isObject()) { return boost::none; }

    const QJsonObject obj{doc.object()};

    if (!obj.contains("ipAddress")) { return boost::none; }

    if (!obj.contains("userName")) { return boost::none; }

    if (!obj["ipAddress"].isString()) { return boost::none; }

    if (!obj["userName"].isString()) { return boost::none; }

    return boost::make_optional(
        Client{obj["ipAddress"].toString(), obj["userName"].toString()});
}

const QString& Client::ip() const { return m_ip; }
const QString& Client::userName() const { return m_userName; }

QString Client::asJson() const
{
    QJsonObject obj;
    obj["ipAddress"] = m_ip;
    obj["userName"]  = m_userName;
    QJsonDocument doc{obj};
    return doc.toJson(QJsonDocument::Compact);
}
