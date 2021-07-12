#include "silo.h"
#include "ui_silo.h"
#include"information.h"
#include<QMessageBox>
silo::silo(QWidget *parent, int _id) :
    QDialog(parent),
    ui(new Ui::silo)
{
       id = _id;
       ui->setupUi(this);
       _info = read_info();
        info = (_info["User"].toArray())[id].toObject();
       ui->capacity->setText(QString::number(5 * pow(2,info["silo_level"].toInt())));
       ui->level->setText(QString::number(info["silo_level"].toInt()));
       ui->wheat->setText(QString::number(info["wheat_count"].toInt()));
       if(info["silo_upgrade_time"] == -1)
           ui->silo_pro->hide();

}

silo::~silo()
{
    delete ui;
}

void silo::on_upgrade_clicked()
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this," ","Are you sure? you want to upgrade?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
         if((info["silo_level"].toInt() + 1 )>=info["level_palyer"].toInt())
            QMessageBox::warning(this , " " ," ");
         else{
             if((info["nail_count"].toInt()<(2*info["silo_level"].toInt()))||(info["shovel_count"].toInt()<(info["silo_level"].toInt()-2))||(info["coin"].toInt()<(100*pow((2*info["silo_level"].toInt()),2))))
                 QMessageBox::warning(this , " " ," ");
             else{
                 info["nail_count"]=QJsonValue(info["nail_count"].toInt()-2*info["silo_level"].toInt());
                 info["coin"]=QJsonValue( info["coin"].toInt() - (100*pow((2*info["silo_level"].toInt()),2)));
                 if(info["silo_level"].toInt()>2)
                     info["shovel_count"]=QJsonValue(info["shovel_count"].toInt()-(info["silo_level"].toInt()-2));
                 time_t _time = time(NULL);
                 info["silo_upgrade_time"] = _time;
                 QJsonArray info_2 = _info["User"].toArray();
                 info_2[id] = QJsonValue(info);
                 _info["User"] = info_2;
                 write_info(_info);
             }
         }
    }
}
