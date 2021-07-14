#include "wheat_field.h"
#include "ui_wheat_field.h"
#include "information.h"
#include "cmath"
#include <QMessageBox>
#include <time.h>

int min1(int a , int b){return a > b ? b : a ;}

using namespace std;

wheat_field::wheat_field(QWidget *parent, int _id) :
    QDialog(parent),
    ui(new Ui::wheat_field)
{
    ui->setupUi(this);
    id = _id;
    _info = read_info();
    info = (_info["User"].toArray())[id].toObject();

    if(info["wheat_upgrade_time"].toInt() == -1)
        ui->wheat_upgrade_pro->hide();

    if(info["wheat_seed_time"].toInt() != -1)
        ui->seed->setEnabled(false);
    else
        ui->seed_progress->hide();

    ui->spinBox->setMaximum(min1(info["wheat_count"].toInt(),5 * pow(2, info["wheat_level"].toInt() - 1)));
    ui->label_3->setText(QString::number(5 * pow(2, info["wheat_level"].toInt() - 1)));
    ui->label_4->setText(QString::number(info["wheat_level"].toInt()));
    ui->label_6->setText(QString::number( info["wheat_cultivated_area"].toInt()));
    ui->wheat_upgrade_pro->setValue(info["wheat_upgrade_pro"].toInt());
    ui->seed_progress->setValue(info["wheat_seed_pro"].toInt());

    timer1 = new QTimer();
    timer2 = new QTimer();

    if(info["wheat_upgrade_time"].toInt() != -1)
        timer1->start(1728000);
    if(info["wheat_seed_time"].toInt() != -1)
        timer2->start(1728000);

    connect(timer1,SIGNAL(timeout()),this,SLOT(increamenter_upgrade()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(increamenter_seed()));
}

wheat_field::~wheat_field()
{
    delete ui;
}

void wheat_field::increamenter_upgrade()
{
    int aux1 = 0;
    aux1 = ui->wheat_upgrade_pro->value();
    aux1++;
    ui->wheat_upgrade_pro->setValue(aux1);
}

void wheat_field::increamenter_seed()
{
    int aux2 = 0;
    aux2 = ui->seed_progress->value();
    aux2++;
    ui->seed_progress->setValue(aux2);
}

void wheat_field::on_upgrade_clicked()
{

    if(info["level_player"].toInt() < 2 )
        QMessageBox::warning(this , " " , "You have not reached <b>level 2</b> yet!!!" );
    else if(info["coin"].toInt() < 5)
        QMessageBox::warning(this , " " , "<b>Coin</b> needed!" );
    else if(info["shovel_count"].toInt() < 1)
        QMessageBox::warning(this , " " , "<b>Shovel</b> needed!" );
    else{
        info["shovel_count"] = QJsonValue(info["shovel_count"].toInt() - 1);
        info["coin"] = QJsonValue(info["coin"].toInt() - 5);
        time_t _time = time(NULL) + info["time"].toInt();
        info["wheat_upgrade_time"] = QJsonValue(_time);
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);
    }
}

void wheat_field::on_seed_clicked()
{
    if(info["wheat_in_use"].toBool())
        QMessageBox::warning(this , " " , "After harvesting, you can seed");
    else{
        time_t _time = time(NULL) + info["time"].toInt();
        info["wheat_cultivated_area"] = ui->spinBox->value();
        info["wheat_seed_time"] = QJsonValue(_time);
        info["wheat_count"] = info["wheat_count"].toInt() - ui->spinBox->value();
        info["wheat_in_use"] = true;
        info["exp"] = QJsonValue(info["exp"].toInt() + ui->spinBox->value());
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);
    }
}

void wheat_field::on_Harvesting_clicked()
{
    if(!info["wheat_in_use"].toBool())
        QMessageBox::warning(this , " " , "You havent seed yet!");

    else if(info["wheat_seed_time"].toInt() != -1 && info["wheat_in_use"].toBool())
        QMessageBox::warning(this , " " , "Wheat isn't ripe");

    else if(5 * pow(2,info["silo_level"].toInt())  < info["wheat_count"].toInt() + 2 * info["wheat_cultivated_area"].toInt())
        QMessageBox::warning(this , " " , "You dont have enough space in silo");

    else{
        info["wheat_count"] = info["wheat_count"].toInt() + 2 * info["wheat_cultivated_area"].toInt();
        info["wheat_in_use"] = false;
        info["exp"] =QJsonValue(info["exp"].toInt() + info["wheat_cultivated_area"].toInt());
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);
    }
}
