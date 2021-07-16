#pragma once
#include "chicken_coop.h"
#include "ui_chicken_coop.h"
#include <QJsonObject>
#include "information.h"
#include <QMessageBox>
#include <ctime>
#include <time.h>
#include <cmath>
#include "farm.h"
#include<QThread>


chicken_coop::chicken_coop(QWidget *parent , int _id) :
    QDialog(parent),
    ui(new Ui::checken_coop)
{

    ui->setupUi(this);
    id = _id;
    farm = new QWidget;
    farm = parent;

    _info = read_info();
    info = (_info["User"].toArray())[id].toObject();

    timer1 = new QTimer();
    timer2 = new QTimer();


    if(info["chicken_level"].toInt() == 0){

        ui->collecteggs->setEnabled(false);
        ui->feed->setEnabled(false);
        ui->label->hide();
        ui->label_2->hide();
        ui->label_3->hide();
        ui->label_5->hide();
        ui->label_6->hide();
        ui->label_7->hide();
        ui->capacity->hide();
        ui->count->hide();
        ui->level->hide();
        if(info["chicken_upgrade_time"].toInt() != -1)
            ui->build_pushButton->setEnabled(false);
    }
    else
        ui->build_pushButton->hide();



    if(info["chicken_upgrade_time"].toInt() == -1)
        ui->chicken_pro->hide();
    else{
        ui->chicken_pro->setValue(info["chicken_upgrade_pro"].toInt());
         timer1->start(1000);
         ui->upgrade->setEnabled(false);
      }

    if(info["chicken_feed_time"].toInt() == -1)
        ui->eggs_pro->hide();
    else{
        ui->eggs_pro->setValue(info["chicken_eggs_pro"].toInt());
            timer2->start(1000);
            ui->feed->setEnabled(false);
     }

    ui->count->setText(QString::number(info["chicken_count"].toInt()));
    ui->capacity->setText(QString::number( pow(2,info["chicken_level"].toInt())));
    ui->level->setText(QString::number(info["chicken_level"].toInt()));



    connect(timer1,SIGNAL(timeout()),this,SLOT(increamenter_upgrade()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(increamenter_collect()));


}
chicken_coop::~chicken_coop()
{
    delete ui;
}

void chicken_coop::increamenter_upgrade()
{
    int aux = 0;
    aux = ui->chicken_pro->value();
    aux++;
    ui->chicken_pro->setValue(aux);
}
void chicken_coop::increamenter_collect()
{
    int aux = 0;
    aux = ui->eggs_pro->value();
    aux++;
    ui->eggs_pro->setValue(aux);

}

void chicken_coop::on_feed_clicked()
{
    if(info["chicken_count"].toInt() == 0)
        QMessageBox::warning(this , "You havent Chicken!" ,"You have to buy a chicken!");
    else if(info["chicken_feeded"].toBool())
        QMessageBox::warning(this , "Already done!" ,"Chickens already feeded !");
    else if(info["chicken_feed_time"].toInt() != -1){
        int sec = ui->eggs_pro->value() * 100 / 100; // after multiply
        int remain_hour = 0, remain_min = 0;
        while (sec > 3600) {
            remain_hour++;
            sec -= 3600;
        }
        while (sec > 60) {
            remain_min++;
            sec -= 60;
        }
        QString hstr = "hour";
        QString mstr = "minute";
        if(remain_hour > 1)
            hstr.append('s');
        if(remain_min > 1)
            mstr.append('s');
        QMessageBox::warning(this , "Come later!" ,
                             "You can feed " + QString::number(remain_hour) + hstr + " and " +
                             QString::number(remain_min) + mstr + " later !");
    }
    else{
        if(info["wheat_count"].toInt() < info["chicken_count"].toInt()){
            if(info["chicken_count"].toInt() - info["wheat_count"].toInt() == 1)
                QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more wheat !");
            else
                QMessageBox::warning(this , "Supply needed !" , "You need " +
                                     QString::number(info["chicken_count"].toInt() - info["wheat_count"].toInt()) + " more wheats !");
        }
        else{
            info["wheat_count"] = QJsonValue(info["wheat_count"].toInt() - info["chicken_count"].toInt());
            time_t _time = time(NULL) + info["time"].toInt();
            info["chicken_feed_time"] = _time;
            QJsonArray info_2 = _info["User"].toArray();
            info_2[id] = QJsonValue(info);
            _info["User"] = info_2;
            write_info(_info);
            Refresh();
        }
    }
}

void chicken_coop::on_upgrade_clicked()
{

    if(info["level_player"].toInt() < info["chicken_level"].toInt() + 1)
        QMessageBox::warning(this , "You must level up!" ,"You need to reach <b>level </b>" + QString::number(info["chicken_level"].toInt() + 1) + " !");
    else if(info["nail_count"].toInt()  < 1){
        if(1 - info["nail_count"].toInt() == 1)
            QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more nail !");
        else
            QMessageBox::warning(this , "Supply needed !" , "You need " +
                                 QString::number(1 - info["nail_count"].toInt()) + " more nails !");
    }
    else if(info["coin"].toInt() < 10){
        if(10 - info["coin"].toInt() == 1)
            QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more coin !");
        else
            QMessageBox::warning(this , "Supply needed !" , "You need " +
                                 QString::number(10 - info["coin"].toInt()) + " more coins !");
    }
    else{
        info["nail_count"] = QJsonValue (info["nail_count"].toInt() - 1 );
        info["coin"] = QJsonValue (info["coin"].toInt() - 10 );
        time_t _time = time(NULL) + info["time"].toInt();
        info["chicken_upgrade_time"] = _time;
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);
        Refresh();
    }
}



void chicken_coop::on_build_pushButton_clicked()
{
    if(info["level_player"].toInt() < 2)
        QMessageBox::warning(this , "You must level up!" ,"You need to reach <b>level 2</b>");
    else if(info["nail_count"].toInt()  < 2){
        if(2 - info["nail_count"].toInt() == 1)
            QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more nail !");
        else
            QMessageBox::warning(this , "Supply needed !" , "You need " +
                                 QString::number(2 - info["nail_count"].toInt()) + " more nails !");
    }
    else if(info["coin"].toInt() < 10){
        if(10 - info["coin"].toInt() == 1)
            QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more coin !");
        else
            QMessageBox::warning(this , "Supply needed !" , "You need " +
                                 QString::number(10 - info["coin"].toInt()) + " more coins !");
    }
    else{
        info["nail_count"] = QJsonValue (info["nail_count"].toInt() - 2 );
        info["coin"] = QJsonValue (info["coin"].toInt() - 10 );
        time_t _time = time(NULL) + info["time"].toInt();
        info["chicken_upgrade_time"] = _time;
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);
        QThread::msleep(100);
        this->close();
        chicken_coop *w = new chicken_coop(farm , id);
        w->show();
    }
}


void chicken_coop::on_collecteggs_clicked()
{

    time_t _time = time(NULL) + info["time"].toInt();
    if(info["chicken_feed_time"].toInt() != -1 && _time - info["chicken_feed_time"].toInt() < 100){
        int sec = ui->eggs_pro->value() * 100 / 100; // after multiply
        int remain_hour = 0, remain_min = 0;
        while (sec > 3600) {
            remain_hour++;
            sec -= 3600;
        }
        while (sec > 60) {
            remain_min++;
            sec -= 60;
        }
        QString hstr = "hour";
        QString mstr = "minute";
        if(remain_hour > 1)
            hstr.append('s');
        if(remain_min > 1)
            mstr.append('s');
        QMessageBox::warning(this , "Come later!" ,
                             "You can collect egg " + QString::number(remain_hour) + hstr + " and " +
                             QString::number(remain_min) + mstr + " later !");
    }
    else if(!info["chicken_feeded"].toBool())
        QMessageBox::warning(this , "Come later!" ,"You have to feed first!");
    else if(ceil(5 * pow(1.5, info["barn_level"].toInt() - 1)) <
            info["nail_count"].toInt() +
            info["shovel_count"].toInt() +
            info["alfalfa_count"].toInt() +
            info["eggs_count"].toInt() +
            info["milk_count"].toInt() +
            info["fleece_count"].toInt() +
            info["chicken_count"].toInt()) //chicken count for added eggs number)
        QMessageBox::warning(this , "Space needed" ,"You don't have enough space in barn !");
    else{
        info["chicken_feeded"] = false;
        info["eggs_count"] = QJsonValue(info["eggs_count"] .toInt() + info["chicken_count"].toInt());
        info["chicken_feed_time"] = -1;
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);
        Refresh();
    }

}

void chicken_coop::Refresh()
{
    QThread::msleep(100);
    this->close();
    chicken_coop *w = new chicken_coop(farm , id);
    w->show();
}

