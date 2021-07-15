#include "alfalfa_field.h"
#include "ui_alfalfa_field.h"
#include "information.h"
#include "cmath"
#include <QMessageBox>
#include <time.h>
#include <QThread>

int min2(int a ,int b){return a > b ? b : a ; }

alfalfa_field::alfalfa_field(QWidget *parent, int _id):
    QDialog(parent),
    ui(new Ui::alfalfa_field)
{
    ui->setupUi(this);
    id = _id;
    _info = read_info();
    info = (_info["User"].toArray())[id].toObject();
    farm = parent;

    if(!info["alfalfa_in_use"].toBool()){
        ui->lbl_cultivated_area->hide();
        ui->lbl_cultivated_area_value->hide();
    }

    if(info["alfalfa_upgrade_time"].toInt() == -1)
        ui->alfalfa_upgrade_pro->hide();
    else
        ui->btn_upgrade->setEnabled(false);

    if(info["alfalfa_plow_time"].toInt() == -1)
        ui->plow_pro->hide();
    else
        ui->btn_plow->setEnabled(false);

    if(info["alfalfa_seed_time"].toInt() == -1)
        ui->seed_pro->hide();
    else
        ui->btn_seed->setEnabled(false);

    ui->spinBox->setMaximum(min2(info["alfalfa_count"].toInt(),4 * pow(2, info["alfalfa_level"].toInt() - 1)));
    ui->lbl_area_value->setText(QString::number(4 * pow(2, info["alfalfa_level"].toInt() - 1)));
    ui->lbl_level_value->setText(QString::number(info["alfalfa_level"].toInt()));
    ui->lbl_cultivated_area_value->setText(QString::number(info["alfalfa_cultivated_area"].toInt()));
    ui->alfalfa_upgrade_pro->setValue(info["alfalfa_upgrade_pro"].toInt());

    ui->plow_pro->setValue(info["alfalfa_plow_pro"].toInt());

    ui->seed_pro->setValue(info["alfalfa_seed_pro"].toInt());

    timer1 = new QTimer();
    timer2 = new QTimer();
    timer3 = new QTimer();

    if(info["alfalfa_upgrade_time"].toInt() != -1)
        timer1->start(1000);
    if(info["alfalfa_plow_time"].toInt() != -1)
        timer2->start(1000);
    if(info["alfalfa_seed_time"].toInt() != -1)
        timer3->start(1000);

    connect(timer1,SIGNAL(timeout()),this,SLOT(increamenter_upgrade()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(increamenter_plow()));
    connect(timer3,SIGNAL(timeout()),this,SLOT(increamenter_seed()));
}

alfalfa_field::~alfalfa_field()
{
    delete ui;
}

void alfalfa_field::increamenter_upgrade()
{
    int aux1 = 0;
    aux1 = ui->alfalfa_upgrade_pro->value();
    aux1++;
    ui->alfalfa_upgrade_pro->setValue(aux1);
}

void alfalfa_field::increamenter_plow()
{
    int aux2 = 0;
    aux2 = ui->plow_pro->value();
    aux2++;
    ui->plow_pro->setValue(aux2);
}

void alfalfa_field::increamenter_seed(){
    int aux3 = 0;
    aux3 = ui->seed_pro->value();
    aux3++;
    ui->seed_pro->setValue(aux3);
}

void alfalfa_field::on_btn_upgrade_clicked()
{
    if(info["level_player"].toInt() < 4)
        QMessageBox::warning(this , "You must level up!" , "You need to reach <b>level 4</b> !!!" );
    else if(info["coin"].toInt() < 5 *(4 * pow(2, info["alfalfa_level"].toInt() - 1)))
        QMessageBox::warning(this , " " , "<b>Coin</b> needed !" );
    else if(info["shovel_count"].toInt() < 2 * (4 * pow(2, info["alfalfa_level"].toInt() - 1)))
        QMessageBox::warning(this , " " , "<b>Shovel</b> needed !" );
    else{
        info["shovel_count"] = QJsonValue(info["shovel_count"].toInt() - 2 * (4 * pow(2, info["alfalfa_level"].toInt() - 1)));
        info["coin"] = QJsonValue(info["coin"].toInt() - 5 * (4 * pow(2, info["alfalfa_level"].toInt() - 1)));
        time_t _time = time(NULL) + info["time"].toInt();
        info["alfalfa_upgrade_time"] = QJsonValue(_time);
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);
        QThread::msleep(100);
        this->close();
        alfalfa_field*  alfalfaField = new alfalfa_field(farm, id);
        alfalfaField->show();
    }
}

void alfalfa_field::on_btn_seed_clicked()
{

    if(info["alfalfa_in_use"].toBool() && info["alfalfa_seed_time"].toInt() == -1)
        QMessageBox::warning(this , " " , "After harvesting, you can seed !");
    else if(!info["alfalfa_plowed"].toBool())
        QMessageBox::warning(this , " " , "You have to plow field first !");
    else{
        info["alfalfa_plowed"] = false;
        time_t _time = time(NULL) + info["time"].toInt();
        info["alfalfa_cultivated_area"] = QJsonValue(ui->spinBox->value());
        info["alfalfa_seed_time"] = QJsonValue(_time);
        info["alfalfa_count"] = QJsonValue(info["alfalfa_count"].toInt() - ui->spinBox->value());
        info["alfalfa_in_use"] = QJsonValue(true);
        info["exp"] = QJsonValue(info["exp"].toInt() + 4 * pow(2 , info["alfalfa_level"].toInt() - 1));
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);

        QThread::msleep(100);
        this->close();
        alfalfa_field*  alfalfaField = new alfalfa_field(farm, id);
        alfalfaField->show();
    }
}

void alfalfa_field::on_btn_harvesting_clicked()
{

    if(!info["alfalfa_in_use"].toBool())
        QMessageBox::warning(this , " " , "You havent seed yet !");
    else if(info["alfalfa_in_use"].toBool() && info["alfalfa_seed_time"].toInt() != -1 )
        QMessageBox::warning(this , " " , "Alfalfa isn't ripe");
    else{
        info["alfalfa_count"] = QJsonValue(info["alfalfa_count"].toInt() + 2 * info["alfalfa_cultivated_area"].toInt());
        info["alfalfa_in_use"] = QJsonValue(false);
        info["exp"] = QJsonValue(info["exp"].toInt() + 2 * 4 * pow(2, info["alfalfa_level"].toInt() - 1));
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);
        QThread::msleep(100);
        this->close();
        alfalfa_field*  alfalfaField = new alfalfa_field(farm, id);
        alfalfaField->show();
    }
}

void alfalfa_field::on_btn_plow_clicked()
{
    if(info["alfalfa_plowed"].toBool() )
        QMessageBox::warning(this , " " , "You have already plowed !");
    else if(info["alfalfa_in_use"].toBool() && info["alfalfa_seed_time"].toInt() != -1 )
        QMessageBox::warning(this , " " , "You cant plow , alfalfa isn't ripe !");
    else if(info["alfalfa_in_use"].toBool() && info["alfalfa_seed_time"].toInt() == -1)
        QMessageBox::warning(this , " " , "you cant plow , You havent harvesting yet !");
    else
    {
        time_t _time = time(NULL) + info["time"].toInt();
        info["alfalfa_plow_time"] = QJsonValue(_time);
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);
        QThread::msleep(100);
        this->close();
        alfalfa_field*  alfalfaField = new alfalfa_field(farm, id);
        alfalfaField->show();
    }
}

void alfalfa_field::on_build_clicked()
{
    if(info["level_player"].toInt() < 3)
        QMessageBox::warning(this , "You must level up!" ,"You need to reach <b>level 3</b> !");
    else if(info["nail_count"].toInt() < 1)
        QMessageBox::warning(this , " " , "<b>Nail</b> needed !" );
    else if(info["coin"].toInt() < 15)
        QMessageBox::warning(this , " " , "<b>Coin</b> needed !" );
    else if(info["shovel_count"].toInt() < 1 )
        QMessageBox::warning(this , " " , "<b>Shovel</b> needed !" );
    else{
        info["shovel_count"] = QJsonValue(info["shovel_count"].toInt() - 1);
        info["nail_count"] = QJsonValue(info["nail_count"].toInt() - 1);
        info["coin"] = QJsonValue(info["coin"].toInt() - 15);
        time_t _time = time(NULL) + info["time"].toInt();
        info["alfalfa_upgrade_time"] = QJsonValue(_time);
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);
        QThread::msleep(100);
        this->close();
        alfalfa_field*  alfalfaField = new alfalfa_field(farm, id);
        alfalfaField->show();
    }
}


