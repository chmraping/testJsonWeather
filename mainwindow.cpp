#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QTextCodec>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariantList>
#include <QJsonObject>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),  // 必须要有finished信号才算下载完数据
            this,SLOT(replyFinished(QNetworkReply*)));

    QUrl url("http://apix.sinaapp.com/weather/");
    QUrlQuery query;
    query.addQueryItem("appkey", "trialuser");
    query.addQueryItem("city", "温州");
    url.setQuery(query);
    manager->get(QNetworkRequest(url)); //发送请求



//http://apix.sinaapp.com/weather/?appkey=trialuser&city=%E6%B7%B1%E5%9C%B3

/*    QUrl url("http://apix.sinaapp.com/weather/");
    QUrlQuery query;
    query.addQueryItem("appkey", "trialuser");
    query.addQueryItem("city", "%E6%B7%B1%E5%9C%B3");

    url.setQuery(query);//http://apix.sinaapp.com/weather/?appkey=trialuser&city=温州
    qDebug() << url;
    QNetworkReply *rep = manager->get(QNetworkRequest(url));



    QTextCodec *codec = QTextCodec::codecForName("utf8");


    QString all = codec->toUnicode(rep->readAll());
    qDebug() << all;
    ui->textBrowser->setText(all);

    rep->deleteLater();  */ //最后要释放reply对象

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
//    QTextCodec *codec = QTextCodec::codecForName("utf8");

    //使用utf8编码，这样才可以显示中文

//    QString all = codec->toUnicode(reply->readAll());

//    ui->textBrowser->setText(all);

    QJsonParseError json_error;
    QJsonDocument json =QJsonDocument::fromJson(reply->readAll(),&json_error);
    QJsonArray array = json.array();
    QVariantList list = array.toVariantList();
    ui->textBrowser->setText(list.at(1).toMap()["Title"].toString());


    reply->deleteLater();   //最后要释放reply对象

}
