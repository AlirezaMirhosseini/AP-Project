#include "client.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include "information.h"
#include "profile.h"
client::client(QWidget *parent , int _id)
    : QWidget(parent)
{
    id=_id;
    socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1", 1030);
    qDebug() << "connecting....";
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));



}

client::~client()
{

}

void client::connected(){
    qDebug() << "Connected\n";
    QJsonObject obj=read_info();
    //
    QJsonArray mainArray=obj["User"].toArray();
    QJsonArray finalArray;
    QJsonObject temp;
    for(int counter=0;counter<mainArray.size();counter++){
        temp["username"] = mainArray[counter].toObject()["username"];
        temp["exp"] = mainArray[counter].toObject()["exp"];
        temp["level_player"] = mainArray[counter].toObject()["level_player"];
        finalArray.push_back(temp);
    }
    obj["User"] = finalArray;

    QJsonDocument doc;
    doc.setObject(obj);
    QByteArray byte=doc.toJson();
    socket->write(byte);
}
void client::disconnected()
{
    qDebug() << "disconnected\n"; // when it is called

}
void client::bytesWritten(qint64 bytes){
    qDebug() << "we wrote ";
    // ted->append(QString::number(bytes));
}
void client::readyRead(){
    QByteArray data = socket->readAll();
    qDebug() << data;
    profile* window = new profile(this,id,data);
    window->show();
}
