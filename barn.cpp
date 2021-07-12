#include "barn.h"
#include "ui_barn.h"
#include "information.h"
#include<cmath>
#include<QMessageBox>
barn::barn(QWidget *parent, int _id) :
    QDialog(parent),
    ui(new Ui::barn)
{
    id = _id;
    ui->setupUi(this);
    _info = read_info();
    info = (_info["User"].toArray())[id].toObject();
    ui->level->setText(QString::number(info["barn_level"].toInt()));
    ui->capacity->setText(QString::number(ceil(5*pow(1.5,info["barn_level"].toInt()-1))));
    ui->shovel->setText(QString::number(info["shovel_count"].toInt()));
    ui->nail->setText(QString::number(info["nail_count"].toInt()));
    ui->alfalfa->setText(QString::number(info["alfalfa_count"].toInt()));
    ui->egg->setText(QString::number(info["eggs_count"].toInt()));
    ui->milk->setText(QString::number(info["milks"].toArray().size()));
    ui->fleece->setText(QString::number(info["fleece_count"].toInt()));
       if(info["barn_upgrade_time"] == -1)
           ui->barn_pro->hide();

}

barn::~barn()
{
    delete ui;
}

void barn::on_upgrade_clicked()
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this," ","Are you sure? you want to upgrade?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        if(info["barn_level"].toInt()>=info["level_palyer"].toInt())
            QMessageBox::warning(this , " " ," ");
        else{
            if((info["nail_count"].toInt()<info["barn_level"].toInt())||(info["shovel_count"].toInt()<(info["barn_level"].toInt()-1))||(info["coin"].toInt()<(10*pow(info["barn_level"].toInt(),3))))
                QMessageBox::warning(this , " " ," ");
            else{
                info["nail_count"]=QJsonValue(info["nail_count"].toInt()-info["barn_level"].toInt());
                info["shovel_count"]=QJsonValue(info["shovel_count"].toInt()-(info["barn_level"].toInt()-1));
                info["coin"]=QJsonValue( info["coin"].toInt()-(10*pow(info["barn_level"].toInt(),3)));
                time_t _time = time(NULL);
                info["barn_upgrade_time"] = _time;
                QJsonArray info_2 = _info["User"].toArray();
                info_2[id] = QJsonValue(info);
                _info["User"] = info_2;
                write_info(_info);
            }
        }
    }
}
