#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_kqtnetworktest.h"
#include <QtNetwork>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTextCodec>

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

class KQtNetworkTest : public QMainWindow
{
    Q_OBJECT

public:
    KQtNetworkTest(QWidget *parent = Q_NULLPTR);

private:
    Ui::KQtNetworkTestClass ui{};
    QNetworkAccessManager* manager;

private slots:
    void replyFinished(QNetworkReply*);
    void on_pushButton_clicked();
};
