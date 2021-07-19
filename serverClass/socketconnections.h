#ifndef SOCKETCONNECTIONS_H
#define SOCKETCONNECTIONS_H

#pragma once
#include "qobject.h"
#include <thread>
#include <QTcpSocket>
using namespace std;
class socketConnections :
    public QObject
{
    Q_OBJECT
public:
    socketConnections(int, QObject* parent = 0);
    ~socketConnections();
    void newSocketEstablish();
private:
    int number;
    std::thread t;
    QTcpSocket *socket;
    int socketID;
    public slots:
};
#endif // SOCKETCONNECTIONS_H
