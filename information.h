#ifndef INFORMATION_H
#define INFORMATION_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include <math.h>

static QJsonObject read_info(){
    QFile file_info("../AP_Project/file.json");
    file_info.open(QIODevice::ReadOnly);
    QByteArray byte = file_info.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(byte);
    QJsonObject file_obj = doc.object();
    file_info.close();
    return file_obj;
}

static void write_info(QJsonObject j){
    QJsonDocument doc(j);
    QFile file_info("../AP_Project/file.json");
    file_info.open(QIODevice::WriteOnly);
    file_info.write(doc.toJson());
    file_info.close();
}
static void check_level(){
    QJsonObject _info=read_info();
     QJsonArray info_2 ;
    for(int i = 0; i < _info["User"].toArray().size() ; i++){
        QJsonObject info = _info["User"].toArray()[i].toObject();
        for(int j=  info["level_player"].toInt() ; true ; j++){
            if(info["exp"].toInt() < (pow(2 , j) -1)*10){
                info["level_player"] = j ;
                break;
            }

        }
        info_2.push_back(QJsonValue(info));
    }
    _info["User"] = info_2;
    write_info(_info);


}

#endif // INFORMATION_H
