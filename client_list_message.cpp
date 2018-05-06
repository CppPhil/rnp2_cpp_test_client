#include "client_list_message.hpp"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <utility>

ClientListMessage::ClientListMessage(std::vector<Client> clients)
    : m_clients{std::move(clients)}, m_messageKind{"clientlist"}
{
}

boost::optional<ClientListMessage> ClientListMessage::fromJson(
    const QString& json)
{
    QJsonDocument doc{QJsonDocument::fromJson(json.toLocal8Bit())};
    if (!doc.isObject()) { return boost::none; }

    const QJsonObject obj{doc.object()};

    if (!obj.contains("connectedClients")) { return boost::none; }

    if (!obj.contains("messageKind")) { return boost::none; }

    if (!obj["connectedClients"].isArray()) { return boost::none; }

    if (!obj["messageKind"].isString()) { return boost::none; }

    if (obj["messageKind"].toString() != "clientlist") { return boost::none; }

    QJsonArray a{obj["connectedClients"].toArray()};

    std::vector<Client> v;

    QJsonValue val = a.at(0);
    if (!val.isArray()) { return boost::none; }

    a = val.toArray();

    for (const QJsonValue& val : a) {
        if (!val.isObject()) { return boost::none; }

        const QJsonObject   curObj{val.toObject()};
        const QJsonDocument curDoc{curObj};
        const QString       curStr{curDoc.toJson(QJsonDocument::Compact)};
        const boost::optional<Client> oc{Client::fromJson(curStr)};
        if (!oc) { return boost::none; }
        v.push_back(*oc);
    }

    return boost::make_optional(ClientListMessage{std::move(v)});
}

const std::vector<Client>& ClientListMessage::clients() const noexcept
{
    return m_clients;
}

const QString& ClientListMessage::messageKind() const noexcept
{
    return m_messageKind;
}

QString ClientListMessage::asJson() const noexcept
{
    QJsonObject obj{};
    QJsonArray  array{};

    for (const auto& e : clients()) {
        QString       curJsonString = e.asJson();
        QJsonDocument curDoc{
            QJsonDocument::fromJson(curJsonString.toLocal8Bit())};
        array.append(QJsonValue(curDoc.object()));
    }
    obj["connectedClients"] = array;
    obj["messageKind"]      = m_messageKind;

    QJsonDocument doc{obj};
    return doc.toJson(QJsonDocument::Compact);
}
