#ifndef SERVERCLASS_H
#define SERVERCLASS_H
#pragma once
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "socketConnections.h"
#include <vector>
using namespace std;
class serverClass :
    public QObject
{
    Q_OBJECT
public:
    serverClass(QObject * parent = 0);
    void setServer();
    ~serverClass();
private:
    QTcpServer *server;
    vector<socketConnections*> connections;

public slots:
    void serverNewConnection();

};

#endif // SERVERCLASS_H
