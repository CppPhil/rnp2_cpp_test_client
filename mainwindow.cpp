#include "mainwindow.hpp"
#include "chat_message.hpp"
#include "client_list_message.hpp"
#include "connect_message.hpp"
#include "disconnect_message.hpp"
#include "netstring.hpp"
#include "ports.hpp"
#include "read_server_address_from_file.hpp"
#include "read_user_name_from_file.hpp"
#include <QByteArray>
#include <QHostAddress>
#include <QMessageBox>
#include <QNetworkDatagram>
#include <QNetworkInterface>
#include <algorithm>
#include <boost/lexical_cast.hpp>
#include <vector>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_serverAddress{}
    , m_userName{}
    , m_tcpSocket{}
    , m_udpSocket{}
    , m_clientList{}
{
    ui.setupUi(this);

    auto opt = readServerAddressFromFile("./server_address.txt");
    if (!opt) {
        QMessageBox msgB;
        msgB.setText("could not read server address from file");
        msgB.exec();
        close();
    }
    m_serverAddress = QString::fromStdString(*opt);

    opt = readUserNameFromFile("./user_name.txt");
    if (!opt) {
        QMessageBox msgB;
        msgB.setText("could not read user name from file");
        msgB.exec();
        close();
    }
    m_userName = QString::fromStdString(*opt);

    connect(
        &m_tcpSocket,
        &QAbstractSocket::connected,
        this,
        &MainWindow::onTcpConnected);

    connect(
        &m_tcpSocket,
        &QAbstractSocket::disconnected,
        this,
        &MainWindow::onTcpDisconnected);

    connect(
        &m_tcpSocket,
        static_cast<void (QAbstractSocket::*)(QAbstractSocket::SocketError)>(
            &QAbstractSocket::error),
        this,
        &MainWindow::onTcpError);

    connect(
        &m_tcpSocket, &QIODevice::readyRead, this, &MainWindow::onTcpReadyRead);

    connect(
        &m_udpSocket, &QIODevice::readyRead, this, &MainWindow::onUdpReadyRead);

    connect(
        ui.sendMessagePushButton,
        &QPushButton::clicked,
        this,
        &MainWindow::onSendMessagePushButtonClick);

    connectToTcpServer();
    bindUdpSocket();
}

void MainWindow::onTcpConnected()
{
    // send the connect SCP message
    const ConnectMessage connectMessage{m_userName};
    const QString        jsonString{connectMessage.asJson()};
    const Netstring      netString(jsonString.toStdString());
    const std::string    messageToSend{
        boost::lexical_cast<std::string>(netString)};
    m_tcpSocket.write(
        messageToSend.data(), static_cast<qint64>(messageToSend.size()));
}

void MainWindow::onTcpDisconnected()
{
    // exit the application.
    QMessageBox msgB;
    msgB.setText("Lost TCP connection - shutting down.");
    close();
}

void MainWindow::onTcpError(QAbstractSocket::SocketError socketError)
{
    // TODO: HERE
    // handle error
    (void)socketError;
}

void MainWindow::onTcpReadyRead()
{
    // read the data and put it in the GUI clientList
    const QByteArray                 dataRead{m_tcpSocket.readAll()};
    const boost::optional<Netstring> netStringOpt{Netstring::fromNetStringData(
        dataRead.data(), static_cast<std::size_t>(dataRead.size()))};

    if (!netStringOpt) {
        return;
    }

    const boost::optional<ClientListMessage> clientListMessageOpt{
        ClientListMessage::fromJson(
            QString::fromStdString(netStringOpt->str()))};
    if (clientListMessageOpt) {
        m_clientList = clientListMessageOpt->clients();
        QString strToShowInGui{""};
        for (const Client& client : m_clientList) {
            strToShowInGui += client.userName();
            strToShowInGui += " (" + client.ip() + ")";
            strToShowInGui += "\n";
        }
        ui.clientListPlainTextEdit->setPlainText(strToShowInGui);
    }
}

void MainWindow::onUdpReadyRead()
{
    // read UDP chat messages and put it in the GUI

    while (m_udpSocket.hasPendingDatagrams()) {
        const QNetworkDatagram datagram = m_udpSocket.receiveDatagram();
        const QByteArray       byteArray{datagram.data()};
        const boost::optional<Netstring> netStringOpt{
            Netstring::fromNetStringData(
                byteArray.data(), static_cast<std::size_t>(byteArray.size()))};

        if (!netStringOpt) {
            continue;
        }

        const boost::optional<ChatMessage> chatMessageOpt{
            ChatMessage::fromJson(QString::fromStdString(netStringOpt->str()))};

        if (!chatMessageOpt) {
            continue;
        }

        if (ui.chateMessagesPlainTextEdit->toPlainText().isEmpty()) {
            ui.chateMessagesPlainTextEdit->setPlainText(
                chatMessageOpt->senderName() + " ("
                + datagram.senderAddress().toString()
                + "):"
                + chatMessageOpt->message());
        }
        else {
            ui.chateMessagesPlainTextEdit->setPlainText(
                ui.chateMessagesPlainTextEdit->toPlainText()
                += ("\n" + chatMessageOpt->senderName() + ":"
                    + chatMessageOpt->message()));
        }

        ui.chateMessagesPlainTextEdit->moveCursor(
            QTextCursor::End, QTextCursor::MoveAnchor);
    }
}

void MainWindow::onSendMessagePushButtonClick()
{
    // send chat message to all clients

    // get the text
    const QString messageAsInGui{ui.sendMessagePlainTextEdit->toPlainText()};
    const ChatMessage chatMessage{messageAsInGui, m_userName};
    const QString     chatMessageJson{chatMessage.asJson()};
    const Netstring   netstring{chatMessageJson.toStdString()};
    const std::string messageToSendStdString{
        boost::lexical_cast<std::string>(netstring)};

    // clear it
    ui.sendMessagePlainTextEdit->setPlainText("");

    for (const Client& client : m_clientList) {
        const QHostAddress curHostAddress{client.ip()};
        m_udpSocket.writeDatagram(
            messageToSendStdString.data(),
            static_cast<qint64>(messageToSendStdString.size()),
            curHostAddress,
            UDP_LISTEN_PORT);
    }
}

void MainWindow::connectToTcpServer()
{
    m_tcpSocket.connectToHost(m_serverAddress, TCP_SERVER_PORT);
}

void MainWindow::disconnectFromTcpServer()
{
    // send disconnect message
    const DisconnectMessage disconnectMessage{};
    const QString           json{disconnectMessage.asJson()};
    const Netstring         netstring{json.toStdString()};
    const std::string dataToSend{boost::lexical_cast<std::string>(netstring)};

    m_tcpSocket.write(
        dataToSend.data(), static_cast<qint64>(dataToSend.size()));
    m_tcpSocket.disconnectFromHost();
}

void MainWindow::bindUdpSocket()
{
    QList<QHostAddress>       addresses{QNetworkInterface::allAddresses()};
    std::vector<QHostAddress> v(
        std::make_move_iterator(addresses.begin()),
        std::make_move_iterator(addresses.end()));
    addresses.clear();
    v.erase(
        std::remove_if(
            v.begin(),
            v.end(),
            [](const QHostAddress& addr) {
                return addr.protocol() != QAbstractSocket::IPv4Protocol
                       || addr.isLoopback() || addr.isMulticast()
                       || addr.isNull();
            }),
        v.end());

    if (v.empty()) {
        QMessageBox m;
        m.setText("no addresses in bindUdpSocket.");
        m.exec();
        return;
    }

    m_udpSocket.bind(v.front(), UDP_LISTEN_PORT);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    disconnectFromTcpServer();
    m_udpSocket.close();
    m_tcpSocket.close();
    event->accept();
}
