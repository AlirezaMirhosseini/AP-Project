#ifndef INFORMATION_H
#define INFORMATION_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include <math.h>

static QJsonObject read_info(){
    QFile file_info("../AP-Project/file.json");
    file_info.open(QIODevice::ReadOnly);
    QByteArray byte = file_info.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(byte);
    QJsonObject file_obj = doc.object();
    file_info.close();
    return file_obj;
}

static void write_info(QJsonObject j){
    QJsonDocument doc(j);
    QFile file_info("../AP-Project/file.json");
    file_info.open(QIODevice::WriteOnly);
    file_info.write(doc.toJson());
    file_info.close();
}

#endif // INFORMATION_H
