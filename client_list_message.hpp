#ifndef CLIENT_LIST_MESSAGE_HPP
#define CLIENT_LIST_MESSAGE_HPP
#include "client.hpp"
#include <QString>
#include <boost/optional.hpp>
#include <vector>

class ClientListMessage {
public:
    explicit ClientListMessage(std::vector<Client> clients);

    static boost::optional<ClientListMessage> fromJson(const QString& json);

    const std::vector<Client>& clients() const noexcept;

    const QString& messageKind() const noexcept;

    QString asJson() const noexcept;

private:
    std::vector<Client> m_clients;
    QString             m_messageKind;
};
#endif // CLIENT_LIST_MESSAGE_HPP
