#include "cow_pasture.h"
#include "ui_cow_pasture.h"
#include "information.h"
#include <QMessageBox>
#include <cmath>
#include<QThread>
cow_pasture::cow_pasture(QWidget *parent , int _id) :
    QDialog(parent),
    ui(new Ui::cow_pasture)
{
    ui->setupUi(this);
    id = _id;
    farm = new QWidget;
    farm = parent;
    _info = read_info();
    info = (_info["User"].toArray())[id].toObject();

    timer1 = new QTimer();
    timer2 = new QTimer();

    if(info["cow_level"].toInt() == 0){
        ui->feed->setEnabled(false);
        ui->collect_milk->setEnabled(false);
        ui->feed->setEnabled(false);

        ui->label->hide();
        ui->label_2->hide();
        ui->label_3->hide();
        ui->label->hide();
        ui->label_6->hide();
        ui->label_7->hide();
        ui->label_8->hide();
        ui->count->hide();
        ui->capacity->hide();
        ui->level->hide();
        if(info["cow_upgrade_time"].toInt() != -1)
           ui->build->setEnabled(false);
    }
    else
        ui->build->hide();

    ui->count->setText(QString::number(info["cow_count"].toInt()));
    ui->capacity->setText(QString::number( pow(2,info["cow_level"].toInt())));
    ui->level->setText(QString::number(info["cow_level"].toInt()));

    if(info["cow_upgrade_time"].toInt() == -1)
        ui->cow_pro->hide();
    else{
        ui->upgrade->setEnabled(false);
        ui->cow_pro->setValue(info["cow_upgrade_pro"].toInt());
        timer1->start(1000);
        }

    if(info["cow_feed_time"].toInt() == -1)
        ui->milk_pro->hide();
    else{
        ui->milk_pro->setValue(info["cow_milk_pro"].toInt());
        ui->feed->setEnabled(false);
        timer2->start(1000);
         }

    connect(timer1,SIGNAL(timeout()),this,SLOT(increamenter_upgrade()));
    connect(timer2 , SIGNAL(timeout()),this,SLOT(increamenter_collect()));
}
cow_pasture::~cow_pasture()
{
    delete ui;
}

void cow_pasture::increamenter_upgrade()
{
    int aux = 0;
    aux = ui->cow_pro->value();
    aux++;
    ui->cow_pro->setValue(aux);
}

void cow_pasture::increamenter_collect()
{
    int aux = 0;
    aux = ui->milk_pro->value();
    aux++;
    ui->milk_pro->setValue(aux);
}

void cow_pasture::on_upgrade_clicked()
{
    if(info["level_player"].toInt() < info["cow_level"].toInt() + 4)
        QMessageBox::warning(this , "You must level up!" ,"You need to reach <b>level </b>" + QString::number(info["cow_level"].toInt() + 4) + " !");
    else if(info["coin"].toInt() < 15){
        if(15 - info["coin"].toInt() == 1)
            QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more coin !");
        else
            QMessageBox::warning(this , "Supply needed !" , "You need " +
                                 QString::number(15 - info["coin"].toInt()) + " more coins !");
    }
    else if(info["nail_count"].toInt()  < 2){
        if(2 - info["nail_count"].toInt() == 1)
            QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more nail !");
        else
            QMessageBox::warning(this , "Supply needed !" , "You need " +
                                 QString::number(2 - info["nail_count"].toInt()) + " more nails !");
    }
    else{
        info["nail_count"] = info["nail_count"].toInt() - 2 ;
        info["coin"] = info["coin"].toInt() - 15 ;
        time_t _time = time(NULL) + info["time"].toInt();
        info["cow_upgrade_time"] = _time;
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);

        Refresh();
    }
}

void cow_pasture::on_feed_clicked()
{
    if(info["cow_count"].toInt() == 0)
        QMessageBox::warning(this , "You havent Cow!" ,"You have to buy a Cow!");
    else if(info["cow_feeded"].toBool())
        QMessageBox::warning(this , "Already done!" ,"Cows already feeded !");
    else if(info["alfalfa_count"].toInt()  < 2 * info["cow_count"].toInt()){
        if(2 * info["cow_count"].toInt() - info["alfalfa_count"].toInt() == 1)
            QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more alfalfa !");
        else
            QMessageBox::warning(this , "Supply needed !" , "You need " +
                                 QString::number(2 * info["cow_count"].toInt() - info["alfalfa_count"].toInt()) + " more alfalfas !");
    }
    else{
        info["alfalfa_count"] = QJsonValue(info["alfalfa_count"].toInt() - 2 * info["cow_count"].toInt());
        time_t _time = time(NULL) + info["time"].toInt();
        info["cow_feed_time"] = _time;
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);
        Refresh();
    }
}

void cow_pasture::on_collect_milk_clicked()
{
    QJsonArray milk_array = info["milks"].toArray();
    time_t _time = time(NULL) + info["time"].toInt();

    if(info["cow_feed_time"].toInt() != -1 && _time - info["cow_feed_time"].toInt() < 100){
        int sec = (100 - ui->milk_pro->value()) * 100 / 100; // after multiply
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
                             "You can collect milk " + QString::number(remain_hour) + " " + hstr + " and " +
                             QString::number(remain_min) + " " + mstr + " later !");
    }
    else if(!info["cow_feeded"].toBool())
        QMessageBox::warning(this , "Come later!" ,"You heve to feed first!");
    else if(ceil(5 * pow(1.5, info["barn_level"].toInt() - 1)) <
            info["nail_count"].toInt() +
            info["shovel_count"].toInt() +
            info["alfalfa_count"].toInt() +
            info["eggs_count"].toInt() +
            info["milk_count"].toInt() +
            info["fleece_count"].toInt() +
            info["cow_count"].toInt())//cow count for added milk number)
        QMessageBox::warning(this , "Space needed !" ,"You don't have enough space in barn !");
    else{
        QMessageBox::information(this, tr("Done Successfully !"), tr("Product Transferred to Barn !"), QMessageBox::Ok);
        info["cow_feeded"] = false;
        time_t _time = time(NULL) + info["time"].toInt();
        for(int i =0 ; i < info["cow_count"].toInt() ; i++)
        milk_array.push_back(QJsonValue(_time));
        info["milks"] = milk_array;
        info["milk_count"] = milk_array.size();
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);
        Refresh();
    }
}
void cow_pasture::on_build_clicked()
{
    if(info["level_player"].toInt() < 4 )
        QMessageBox::warning(this , "You must level up!" ,"You need to reach <b>level 4</b> !");
    else if(info["nail_count"].toInt() < 3){
        if(3 - info["nail_count"].toInt() == 1)
            QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more nail !");
        else
            QMessageBox::warning(this , "Supply needed !" , "You need " +
                                 QString::number(3 - info["nail_count"].toInt()) + " more nails !");
    }
    else if(info["coin"].toInt() < 20){
        if(20 - info["coin"].toInt() == 1)
            QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more coin !");
        else
            QMessageBox::warning(this , "Supply needed !" , "You need " +
                                 QString::number(20 - info["coin"].toInt()) + " more coins !");
    }
    else if(info["shovel_count"].toInt() < 1){
        if(1 - info["shovel_count"].toInt() == 1)
            QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more shovel !");
        else
            QMessageBox::warning(this , "Supply needed !" , "You need " +
                                 QString::number(1 - info["shovel_count"].toInt()) + " more shovels !");
    }
    else{
        info["nail_count"] = info["nail_count"].toInt() - 3 ;
        info["shovel_count"] = info["shovel_count"].toInt() - 1 ;
        info["coin"] = info["coin"].toInt() - 20 ;
        time_t _time = time(NULL) + info["time"].toInt();
        info["cow_upgrade_time"] = _time;
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);

        Refresh();
    }
}

void cow_pasture::Refresh()
{
    QThread::msleep(100);
    this->close();
    cow_pasture *w = new cow_pasture(farm , id);
    w->show();
}

