#include "socketConnections.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

socketConnections::socketConnections(int _socketID, QObject *parent) :QObject(parent)
{
    socketID = _socketID;
    t = std::thread(&socketConnections::newSocketEstablish, this);

}

void socketConnections::newSocketEstablish(){
    socket = new  QTcpSocket();
    qDebug() << "new connection:  " << socketID;

        if (socket->setSocketDescriptor(socketID)){
            while (true){
                while (!socket->waitForReadyRead(-1));
                QByteArray data=socket->readAll();
                qDebug() << "received: " << data;
                qDebug()<<data;
                QJsonDocument doc = QJsonDocument::fromJson(data);
                QJsonObject file_obg = doc.object();
                QJsonArray file_Array = file_obg["User"].toArray();
                QJsonArray final;
                for(int counter=0;counter<file_Array.size();counter++){
                   // QJsonObject info=file_Array[counter].toObject();
                    number=0;
                    for(int counter2=0;counter2<counter;counter2++){
                        if((file_Array[counter].toObject()["level_player"].toInt()<file_Array[counter2].toObject()["level_player"].toInt())
                         || ((file_Array[counter].toObject()["level_player"].toInt() == file_Array[counter2].toObject()["level_player"].toInt())&&
                           (file_Array[counter].toObject()["exp"].toInt()<file_Array[counter2].toObject()["exp"].toInt())))
                            number++;
                    }
                    final.insert(number,QJsonValue(file_Array[counter].toObject()["username"].toString()));
                }
                file_obg["User"]=final;
                doc.setObject(file_obg);
                QByteArray byte=doc.toJson();
                qDebug()<<byte;
                socket->write(byte);
                socket->waitForBytesWritten(-1);
            }
        }
        else{
            qDebug() << "could not find the socket";
            return;
        }

}
socketConnections::~socketConnections()
{
    qDebug() << "Destroy an object";
    t.join();
}
