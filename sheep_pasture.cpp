#include "sheep_pasture.h"
#include "ui_sheep_pasture.h"
#include "information.h"
#include <QMessageBox>
#include <cmath>
#include<QThread>

sheep_pasture::sheep_pasture(QWidget *parent , int _id) :
    QDialog(parent),
    ui(new Ui::sheep_pasture)
{
    ui->setupUi(this);
    id=_id;
    farm = new QWidget;
    farm = parent;
    timer1 = new QTimer();
    timer2 = new QTimer();

    _info = read_info();
    info = (_info["User"].toArray())[id].toObject();

    if(info["sheep_level"].toInt() == 0){
        ui->Fleece_Shave->setEnabled(false);
        ui->feed->setEnabled(false);
        ui->capacity->hide();
        ui->count->hide();
        ui->label->hide();
        ui->label_3->hide();
        ui->label_5->hide();
        ui->label_6->hide();
        ui->label_7->hide();
        ui->label_8->hide();
        ui->count->hide();
        ui->capacity->hide();
        ui->level->hide();
    }
    else
        ui->build->hide();

    if(info["sheep_upgrade_time"].toInt() == -1)
        ui->sheep_pro->hide();
    else
        ui->sheep_pro->setValue(info["sheep_upgrade_pro"].toInt());


    if(info["sheep_feed_time"].toInt() == -1)
        ui->fleece_pro->hide();
    else
        ui->fleece_pro->setValue(info["sheep_fleece_pro"].toInt());


    ui->count->setText(QString::number(info["sheep_count"].toInt()));
    ui->capacity->setText(QString::number( pow(2,info["sheep_level"].toInt())));
    ui->level->setText(QString::number(info["sheep_level"].toInt()));

    if(info["sheep_upgrade_time"].toInt() == -1)
        ui->sheep_pro->hide();

    if(info["sheep_feed_time"] != -1)
        ui->feed->setEnabled(false);

    ui->sheep_pro->setValue(info["sheep_upgrade_pro"].toInt());

    if(info["sheep_upgrade_time"].toInt() != -1)
        timer1->start(1000);

    if(info["sheep_feed_time"].toInt() != -1)
        timer2->start(1000);


    connect(timer1,SIGNAL(timeout()),this,SLOT(increamenter_upgrade()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(increamenter_collect()));
}

sheep_pasture::~sheep_pasture()
{
    delete ui;
}

void sheep_pasture::increamenter_upgrade()
{
    int aux = 0;
    aux = ui->sheep_pro->value();
    aux++;
    ui->sheep_pro->setValue(aux);
}

void sheep_pasture::increamenter_collect()
{
    int aux = 0;
    aux = ui->fleece_pro->value();
    aux++;
    ui->fleece_pro->setValue(aux);
}

void sheep_pasture::on_feed_clicked()
{
    if(info["sheep_count"].toInt() == 0)
        QMessageBox::warning(this , "You havent Sheep!" ,"You have to buy a Sheep!");
    else if(info["sheep_feeded"].toBool())
        QMessageBox::warning(this , "Already done!" ,"Sheeps already feeded !");
    else  if(info["sheep_feed_time"].toInt() != -1){
        int sec = (100 - ui->fleece_pro->value()) * 100 / 100; // after multiply
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
                             "You can feed " + QString::number(remain_hour) + " " + hstr + " and " +
                             QString::number(remain_min) + " " + mstr + " later !");
    }
    else  if(info["alfalfa_count"].toInt() < info["sheep_count"].toInt()){
        if(info["sheep_count"].toInt() - info["alfalfa_count"].toInt() == 1)
            QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more alfalfa !");
        else
            QMessageBox::warning(this , "Supply needed !" , "You need " +
                                 QString::number(info["sheep_count"].toInt() - info["alfalfa_count"].toInt()) + " more alfalfas !");
    }
    else{
        info["alfalfa_count"] = QJsonValue(info["alfalfa_count"].toInt() - info["sheep_count"].toInt());
        time_t _time = time(NULL) + info["time"].toInt();
        info["sheep_feed_time"] = _time;
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);

        Refresh();
    }
}

void sheep_pasture::on_upgrade_clicked()
{
    if(info["level_player"].toInt() < info["sheep_level"].toInt() + 6)
        QMessageBox::warning(this , "You must level up!" ,"You need to reach <b>level </b>" + QString::number(info["sheep_level"].toInt() + 6) + " !");
    else if(info["nail_count"].toInt() < 3){
        if(3 - info["nail_count"].toInt() == 1)
            QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more nail !");
        else
            QMessageBox::warning(this , "Supply needed !" , "You need " +
                                 QString::number(3 - info["nail_count"].toInt()) + " more nails !");
    }
    else if(info["shovel_count"].toInt() < 1){
        if(1 - info["shovel_count"].toInt() == 1)
            QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more shovel !");
        else
            QMessageBox::warning(this , "Supply needed !" , "You need " +
                                 QString::number(1 - info["shovel_count"].toInt()) + " more shovels !");
    }
    else if(info["coin"].toInt() < 50){
        if(50 - info["coin"].toInt() == 1)
            QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more coin !");
        else
            QMessageBox::warning(this , "Supply needed !" , "You need " +
                                 QString::number(50 - info["coin"].toInt()) + " more coins !");
    }
    else{
        info["nail_count"] = QJsonValue (info["nail_count"].toInt() - 3 );
        info["shovel_count"] = QJsonValue (info["shovel_count"].toInt() - 1 );
        info["coin"] = QJsonValue (info["coin"].toInt() - 50 );
        time_t _time = time(NULL) + info["time"].toInt();
        info["sheep_upgrade_time"] = _time;
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);
        Refresh();
    }
}

void sheep_pasture::on_Fleece_Shave_clicked()
{
    time_t _time = time(NULL) + info["time"].toInt();
    if(info["sheep_feed_time"].toInt() != -1 && _time -  info["sheep_feed_time"].toInt() < 100){
        int sec = (100 - ui->fleece_pro->value()) * 100 / 100; // after multiply
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
                             "You can Shave " + QString::number(remain_hour) + " " + hstr + " and " +
                             QString::number(remain_min) + " " + mstr + " later !");
    }
    else if(!info["sheep_feeded"].toBool())
        QMessageBox::warning(this , "Come later!" ,"You heve to feed first!");

    else if(info["coin"].toInt() < info["sheep_count"].toInt()){
        if(info["sheep_count"].toInt() - info["coin"].toInt() == 1)
            QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more coin !");
        else
            QMessageBox::warning(this , "Supply needed !" , "You need " +
                                 QString::number(info["sheep_count"].toInt() - info["coin"].toInt()) + " more coins !");
    }
    else if(ceil(5 * pow(1.5, info["barn_level"].toInt() -1 )) <
            info["nail_count"].toInt() +
            info["shovel_count"].toInt() +
            info["alfalfa_count"].toInt() +
            info["eggs_count"].toInt() +
            info["milk_count"].toInt() +
            info["fleece_count"].toInt() +
            info["sheep_count"].toInt())//sheep count for added fleece number
        QMessageBox::warning(this , "Space needed !" ,"You don't have enough space in barn !");
    else{
        QMessageBox::information(this, tr("Done Successfully !"), tr("Product Transferred to Barn !"), QMessageBox::Ok);
        info["sheep_feeded"] = false;
        info["fleece_count"] = QJsonValue(info["fleece_count"] .toInt() + info["sheep_count"].toInt());
        info["sheep_feed_time"] = -1;
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);
        Refresh();
    }
}

void sheep_pasture::on_build_clicked()
{
    if(info["level_player"].toInt() < 6)
        QMessageBox::warning(this , "You must level up!" ,"You need to reach <b>level 6</b> !");
    else if(info["nail_count"].toInt()  < 4){
        if(4 - info["nail_count"].toInt() == 1)
            QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more nail !");
        else
            QMessageBox::warning(this , "Supply needed !" , "You need " +
                                 QString::number(4 - info["nail_count"].toInt()) + " more nails !");
    }
    else if(info["shovel_count"].toInt()  < 2){
        if(2 - info["shovel_count"].toInt() == 1)
            QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more shovel !");
        else
            QMessageBox::warning(this , "Supply needed !" , "You need " +
                                 QString::number(2 - info["shovel_count"].toInt()) + " more shovels !");
    }
    else if(info["coin"].toInt() < 50){
        if(50 - info["coin"].toInt() == 1)
            QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more coin !");
        else
            QMessageBox::warning(this , "Supply needed !" , "You need " +
                                 QString::number(50 - info["coin"].toInt()) + " more coins !");
    }
    else{
        info["nail_count"] = QJsonValue (info["nail_count"].toInt() - 4 );
        info["shovel_count"] = QJsonValue (info["shovel_count"].toInt() - 2 );
        info["coin"] = QJsonValue (info["coin"].toInt() - 50 );
        time_t _time = time(NULL) + info["time"].toInt();
        info["sheep_upgrade_time"] = _time;
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);

        Refresh();
    }
}

void sheep_pasture::Refresh()
{
    QThread::msleep(100);
    this->close();
    sheep_pasture *w = new sheep_pasture(farm , id);
    w->show();
}
