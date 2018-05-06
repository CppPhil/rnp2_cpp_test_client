#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include <QString>

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    Ui::MainWindow ui;
    QString        m_serverAddress;
};

#endif // MAINWINDOW_HPP
