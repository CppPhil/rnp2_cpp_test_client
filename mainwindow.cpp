#include "mainwindow.hpp"
#include "read_server_address_from_file.hpp"
#include <QMessageBox>
#include <cstdlib>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), m_serverAddress{}
{
    ui.setupUi(this);

    auto opt = readServerAddressFromFile("./server_address.txt");
    if (!opt) {
        QMessageBox msgB;
        msgB.setText("could not read server address from file");
        msgB.exec();
        std::exit(EXIT_FAILURE);
    }

    m_serverAddress = QString::fromStdString(*opt);
}
