/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *topHalfHorizontalLayout;
    QSplitter *chatMessagesSplitter;
    QLabel *chatMessagesLabel;
    QPlainTextEdit *chateMessagesPlainTextEdit;
    QSplitter *clientListSplitter;
    QLabel *clientListLabel;
    QPlainTextEdit *clientListPlainTextEdit;
    QSplitter *sendMessageSplitter;
    QLabel *sendMessageLabel;
    QPlainTextEdit *sendMessagePlainTextEdit;
    QPushButton *sendMessagePushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(888, 501);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topHalfHorizontalLayout = new QHBoxLayout();
        topHalfHorizontalLayout->setSpacing(6);
        topHalfHorizontalLayout->setObjectName(QStringLiteral("topHalfHorizontalLayout"));
        chatMessagesSplitter = new QSplitter(centralWidget);
        chatMessagesSplitter->setObjectName(QStringLiteral("chatMessagesSplitter"));
        chatMessagesSplitter->setOrientation(Qt::Vertical);
        chatMessagesLabel = new QLabel(chatMessagesSplitter);
        chatMessagesLabel->setObjectName(QStringLiteral("chatMessagesLabel"));
        chatMessagesSplitter->addWidget(chatMessagesLabel);
        chateMessagesPlainTextEdit = new QPlainTextEdit(chatMessagesSplitter);
        chateMessagesPlainTextEdit->setObjectName(QStringLiteral("chateMessagesPlainTextEdit"));
        chateMessagesPlainTextEdit->setReadOnly(true);
        chatMessagesSplitter->addWidget(chateMessagesPlainTextEdit);

        topHalfHorizontalLayout->addWidget(chatMessagesSplitter);

        clientListSplitter = new QSplitter(centralWidget);
        clientListSplitter->setObjectName(QStringLiteral("clientListSplitter"));
        clientListSplitter->setOrientation(Qt::Vertical);
        clientListLabel = new QLabel(clientListSplitter);
        clientListLabel->setObjectName(QStringLiteral("clientListLabel"));
        clientListSplitter->addWidget(clientListLabel);
        clientListPlainTextEdit = new QPlainTextEdit(clientListSplitter);
        clientListPlainTextEdit->setObjectName(QStringLiteral("clientListPlainTextEdit"));
        clientListPlainTextEdit->setReadOnly(true);
        clientListSplitter->addWidget(clientListPlainTextEdit);

        topHalfHorizontalLayout->addWidget(clientListSplitter);


        verticalLayout->addLayout(topHalfHorizontalLayout);

        sendMessageSplitter = new QSplitter(centralWidget);
        sendMessageSplitter->setObjectName(QStringLiteral("sendMessageSplitter"));
        sendMessageSplitter->setOrientation(Qt::Horizontal);
        sendMessageLabel = new QLabel(sendMessageSplitter);
        sendMessageLabel->setObjectName(QStringLiteral("sendMessageLabel"));
        sendMessageSplitter->addWidget(sendMessageLabel);
        sendMessagePlainTextEdit = new QPlainTextEdit(sendMessageSplitter);
        sendMessagePlainTextEdit->setObjectName(QStringLiteral("sendMessagePlainTextEdit"));
        sendMessageSplitter->addWidget(sendMessagePlainTextEdit);
        sendMessagePushButton = new QPushButton(sendMessageSplitter);
        sendMessagePushButton->setObjectName(QStringLiteral("sendMessagePushButton"));
        sendMessageSplitter->addWidget(sendMessagePushButton);

        verticalLayout->addWidget(sendMessageSplitter);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 888, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        chatMessagesLabel->setText(QApplication::translate("MainWindow", "chat messages:", nullptr));
        clientListLabel->setText(QApplication::translate("MainWindow", "client list:", nullptr));
        sendMessageLabel->setText(QApplication::translate("MainWindow", "Enter message:", nullptr));
        sendMessagePushButton->setText(QApplication::translate("MainWindow", "Send message!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
