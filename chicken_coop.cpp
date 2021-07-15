#pragma once
#include "chicken_coop.h"
#include "ui_chicken_coop.h"
#include <QJsonObject>
#include "information.h"
#include <QMessageBox>
#include <ctime>
#include <time.h>
#include <cmath>

chicken_coop::chicken_coop(QWidget *parent , int _id) :
    QDialog(parent),
    ui(new Ui::checken_coop)
{
    ui->setupUi(this);
    id = _id;

    _info = read_info();
    info = (_info["User"].toArray())[id].toObject();

    ui->count->setText(QString::number(info["chicken_count"].toInt()));
    ui->capacity->setText(QString::number( pow(2,info["chicken_level"].toInt())));
    ui->level->setText(QString::number(info["chicken_level"].toInt()));


    if(info["chicken_upgrade_time"].toInt() == -1)
        ui->chicken_pro->hide();


    timer = new QTimer();

    ui->chicken_pro->setValue(info["chicken_upgrade_pro"].toInt());

    if(info["chicken_upgrade_time"].toInt() != -1)
        timer->start(2592000);

    connect(timer,SIGNAL(timeout()),this,SLOT(increamenter()));


}
chicken_coop::~chicken_coop()
{
    delete ui;
}

void chicken_coop::increamenter()
{
    int aux = 0;
    aux = ui->chicken_pro->value();
    aux++;
    ui->chicken_pro->setValue(aux);
}


void chicken_coop::on_feed_clicked()
{
    if(info["chicken_feed_time"].toInt() != -1)
        QMessageBox::warning(this , " " ,"Chickens are feeding!");
    else{
        if(info["wheat_count"].toInt() < info["chicken_count"].toInt()){
            QMessageBox::warning(this , " " ,"<b>Wheat</b> needed!");
        }
        else{
            info["wheat_count"] = QJsonValue(info["wheat_count"].toInt() - info["chicken_count"].toInt());
            time_t _time = time(NULL) + info["time"].toInt();
            info["chicken_feed_time"] = _time;
            QJsonArray info_2 = _info["User"].toArray();
            info_2[id] = QJsonValue(info);
            _info["User"] = info_2;
            write_info(_info);
        }
    }
}


void chicken_coop::on_collect_eggs_clicked()
{
    time_t _time = time(NULL) + info["time"].toInt();
    if(_time - info["chicken_feed_time"].toInt() >= 172800){
        if(ceil(5 * pow(1.5, info["barn_level"].toInt() - 1)) <
                info["nail_count"].toInt() +
                info["shovel_count"].toInt() +
                info["alfalfa_count"].toInt() +
                info["eggs_count"].toInt() +
                info["milk_count"].toInt() +
                info["fleece_count"].toInt() +
                info["chicken_count"].toInt())//chicken count for added eggs number)
            QMessageBox::warning(this , " " ,"You don't have enough space in barn!");
        else{
            info["eggs_count"] = QJsonValue(info["eggs_count"] .toInt() + info["chicken_count"].toInt());
            info["chicken_feed_time"] = -1;
            QJsonArray info_2 = _info["User"].toArray();
            info_2[id] = QJsonValue(info);
            _info["User"] = info_2;
            write_info(_info);
        }
    }
    else
        QMessageBox::warning(this , " " ,"Chickens are feeding!");
}


void chicken_coop::on_upgrade_clicked()
{
    if(info["level_player"].toInt() < info["chicken_level"].toInt() + 1)
        QMessageBox::warning(this , " " ,"You need to reach <b>level </b>" + QString::number(info["chicken_level"].toInt() + 1));
    else if(info["nail_count"].toInt()  < 1)
        QMessageBox::warning(this , " " ,"<b>Nail</b> needed!");
    else if(info["coin"].toInt() < 10)
        QMessageBox::warning(this , " " ,"<b>Coin</b> needed!");
    else{
        info["nail_count"] = QJsonValue (info["nail_count"].toInt() - 1 );
        info["coin"] = QJsonValue (info["coin"].toInt() - 10 );
        time_t _time = time(NULL) + info["time"].toInt();
        info["chicken_upgrade_time"] = _time;
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);
    }
}

void chicken_coop::on_build_pushButton_clicked()
{
    if(info["level_player"].toInt() < 2)
        QMessageBox::warning(this , " " ,"You need to reach <b>level 2</b>");

    else if(info["nail_count"].toInt()  < 2)
        QMessageBox::warning(this , " " ,"<b>Nail</b> needed!");
    else if(info["coin"].toInt() < 10)
        QMessageBox::warning(this , " " ,"<b>Coin</b> needed!");
    else{
        info["nail_count"] = QJsonValue (info["nail_count"].toInt() - 2 );
        info["coin"] = QJsonValue (info["coin"].toInt() - 10 );
        time_t _time = time(NULL) + info["time"].toInt();
        info["chicken_upgrade_time"] = _time;
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);
    }
}

