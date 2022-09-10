#include "kqtnetworktest.h"

KQtNetworkTest::KQtNetworkTest(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

void KQtNetworkTest::replyFinished(QNetworkReply* reply)
{
    QTextCodec* codec = QTextCodec::codecForName("utf8");
    QString all = codec->toUnicode(reply->readAll());
    ui.textBrowser->setText(all);
    ui.pushButton->setText("查询");
    ui.pushButton->setEnabled(true);
    reply->deleteLater();
}

void KQtNetworkTest::on_pushButton_clicked()
{
    manager->get(QNetworkRequest(QUrl(ui.lineEdit->text())));
    ui.pushButton->setText("查询中，请稍等......");
    ui.pushButton->setEnabled(false);
}