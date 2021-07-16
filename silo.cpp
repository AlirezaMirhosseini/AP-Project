#include "silo.h"
#include "ui_silo.h"
#include "information.h"
#include <QMessageBox>
#include<QThread>

silo::silo(QWidget *parent, int _id) :
    QDialog(parent),
    ui(new Ui::silo)
{
    id = _id;
    ui->setupUi(this);
    farm  = new QWidget;
    farm = parent;
    _info = read_info();
    info = (_info["User"].toArray())[id].toObject();
    ui->capacity->setText(QString::number(5 * pow(2, info["silo_level"].toInt())));
    ui->level->setText(QString::number(info["silo_level"].toInt()));
    ui->wheat->setText(QString::number(info["wheat_count"].toInt()));

     timer = new QTimer;

     if(info["silo_upgrade_time"].toInt() != -1){
        ui->silo_pro->setValue(info["silo_upgrade_pro"].toInt());
         timer->start(1000);
     }
     else
         ui->silo_pro->hide();

     connect(timer,SIGNAL(timeout()),this,SLOT(increamenter_upgrade()));
}

silo::~silo()
{
    delete ui;
}

void silo::on_upgrade_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this," ","Are you sure ?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        if((info["silo_level"].toInt() + 1 ) >= info["level_player"].toInt())
            QMessageBox::warning(this , "You must level up!" ,"Silo level cannot be higher than your level !");
        else{
            if(info["coin"].toInt() < (100 * pow((2 * info["silo_level"].toInt()), 2))){
                if((100 * pow((2 * info["silo_level"].toInt()), 2)) - info["coin"].toInt() == 1)
                    QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more coin !");
                else
                    QMessageBox::warning(this , "Supply needed !" , "You need " +
                                         QString::number((100 * pow((2 * info["silo_level"].toInt()), 2)) - info["coin"].toInt()) + " more coins !");
            }
            else if((info["nail_count"].toInt() < (2 * info["silo_level"].toInt())))
                QMessageBox::warning(this , "Supply needed !" ,"<b>Nail</b> needed !");
            else if (info["shovel_count"].toInt() < (info["silo_level"].toInt()-2))
                QMessageBox::warning(this , "Supply needed !" ,"<b>Shovel</b> needed !");
            else{
                info["nail_count"] = QJsonValue(info["nail_count"].toInt() - 2 * info["silo_level"].toInt());
                info["coin"] = QJsonValue( info["coin"].toInt() - (100*pow((2*info["silo_level"].toInt()), 2)));
                if(info["silo_level"].toInt() > 2)
                    info["shovel_count"] = QJsonValue(info["shovel_count"].toInt() - (info["silo_level"].toInt() - 2));
                time_t _time = time(NULL) + info["time"].toInt();
                info["silo_upgrade_time"] = _time;
                QJsonArray info_2 = _info["User"].toArray();
                info_2[id] = QJsonValue(info);
                _info["User"] = info_2;
                write_info(_info);

                QThread::msleep(100);
                this->close();
                silo *w = new silo(farm , id);
                w->show();
            }
        }
    }
}
void silo::increamenter_upgrade()
{
    int aux = 0;
    aux = ui->silo_pro->value();
    aux++;
    ui->silo_pro->setValue(aux);
}
