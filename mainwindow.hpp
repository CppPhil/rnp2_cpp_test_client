#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include "client.hpp"
#include "ui_mainwindow.h"
#include <QAbstractSocket>
#include <QCloseEvent>
#include <QString>
#include <QTcpSocket>
#include <QUdpSocket>
#include <vector>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void onTcpConnected();

    void onTcpDisconnected();

    void onTcpError(QAbstractSocket::SocketError socketError);

    void onTcpReadyRead();

    void onUdpReadyRead();

    void onSendMessagePushButtonClick();

private:
    void connectToTcpServer();

    void disconnectFromTcpServer();

    void bindUdpSocket();

    virtual void closeEvent(QCloseEvent* event) override;

    Ui::MainWindow      ui;
    QString             m_serverAddress;
    QString             m_userName;
    QTcpSocket          m_tcpSocket;
    QUdpSocket          m_udpSocket;
    std::vector<Client> m_clientList;
};

#endif // MAINWINDOW_HPP
