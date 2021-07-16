#include "barn.h"
#include "ui_barn.h"
#include "information.h"
#include <cmath>
#include <QMessageBox>
#include<QThread>
barn::barn(QWidget *parent, int _id) :
    QDialog(parent),
    ui(new Ui::barn)
{
    id = _id;
    ui->setupUi(this);

    _info = read_info();
    info = (_info["User"].toArray())[id].toObject();
    farm = new QWidget;
    farm = parent;

     timer = new QTimer;




     if(info["barn_upgrade_time"].toInt() != -1){
         ui->upgrade->setEnabled(false);
        ui->barn_pro->setValue(info["barn_upgrade_pro"].toInt());
         timer->start(1000);
     }
     else
         ui->barn_pro->hide();

     connect(timer,SIGNAL(timeout()),this,SLOT(increamenter_upgrade()));
    ui->level->setText(QString::number(info["barn_level"].toInt()));
    ui->capacity->setText(QString::number(ceil(5*pow(1.5,info["barn_level"].toInt()-1))));
    ui->shovel->setText(QString::number(info["shovel_count"].toInt()));
    ui->nail->setText(QString::number(info["nail_count"].toInt()));
    ui->alfalfa->setText(QString::number(info["alfalfa_count"].toInt()));
    ui->egg->setText(QString::number(info["eggs_count"].toInt()));
    ui->milk->setText(QString::number(info["milks"].toArray().size()));
    ui->fleece->setText(QString::number(info["fleece_count"].toInt()));
    int item = info["nail_count"].toInt() +
            info["shovel_count"].toInt() +
            info["alfalfa_count"].toInt() +
            info["eggs_count"].toInt() +
            info["milks"].toArray().size() +
            info["fleece_count"].toInt();
    ui->items->setText(QString::number(item));
}

barn::~barn()
{
    delete ui;
}

void barn::on_upgrade_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this," ","Are you sure?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        if(info["barn_level"].toInt() >= info["level_player"].toInt())
            QMessageBox::warning(this , "You must level up!" ,"Barn level cant be greater than Your Level!");
        else{
            if((info["nail_count"].toInt() < info["barn_level"].toInt())){
                if(info["barn_level"].toInt() - info["nail_count"].toInt() == 1)
                    QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more nail !");
                else
                    QMessageBox::warning(this , "Supply needed !" , "You need " +
                                         QString::number(info["barn_level"].toInt() - info["nail_count"].toInt()) + " more nails !");
            }
            else if((info["shovel_count"].toInt() < (info["barn_level"].toInt() - 1))){
                if((info["barn_level"].toInt() - 1) - info["shovel_count"].toInt() == 1)
                    QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more shovel !");
                else
                    QMessageBox::warning(this , "Supply needed !" , "You need " +
                                         QString::number((info["barn_level"].toInt() - 1) - info["shovel_count"].toInt()) + " more shovels !");
            }
            else if(info["coin"].toInt() < (10 * pow(info["barn_level"].toInt(), 3))){
                if((10 * pow(info["barn_level"].toInt(), 3)) - info["coin"].toInt() == 1)
                    QMessageBox::warning(this , "Supply needed !" , "You need <u>1</u> more coin !");
                else
                    QMessageBox::warning(this , "Supply needed !" , "You need " +
                                         QString::number((10 * pow(info["barn_level"].toInt(), 3)) - info["coin"].toInt()) + " more coins !");
            }
            else{
                info["nail_count"]=QJsonValue(info["nail_count"].toInt() - info["barn_level"].toInt());
                info["shovel_count"]=QJsonValue(info["shovel_count"].toInt() - (info["barn_level"].toInt()-1));
                info["coin"]=QJsonValue(info["coin"].toInt() - (10*pow(info["barn_level"].toInt(),3)));
                time_t _time = time(NULL) + info["time"].toInt();
                info["barn_upgrade_time"] = _time;
                QJsonArray info_2 = _info["User"].toArray();
                info_2[id] = QJsonValue(info);
                _info["User"] = info_2;
                write_info(_info);

                QThread::msleep(100);
                this->close();
                barn *w = new barn(farm , id);
                w->show();
            }
        }
    }
}

void barn::increamenter_upgrade()
{
    int aux = 0;
    aux = ui->barn_pro->value();
    aux++;
    ui->barn_pro->setValue(aux);
}
