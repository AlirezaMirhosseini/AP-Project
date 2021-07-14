#include "sheep_pasture.h"
#include "ui_sheep_pasture.h"
#include "information.h"
#include <QMessageBox>
#include <cmath>

sheep_pasture::sheep_pasture(QWidget *parent , int _id) :
    QDialog(parent),
    ui(new Ui::sheep_pasture)
{
    ui->setupUi(this);
    id=_id;
    _info = read_info();
    info = (_info["User"].toArray())[id].toObject();
    ui->count->setText(QString::number(info["sheep_count"].toInt()));
    ui->capacity->setText(QString::number( pow(2,info["sheep_level"].toInt())));
    ui->level->setText(QString::number(info["sheep_level"].toInt()));

    if(info["sheep_upgrade_time"].toInt() == -1)
        ui->sheep_pro->hide();

    timer = new QTimer();
    ui->sheep_pro->setValue(info["sheep_upgrade_pro"].toInt());

    if(info["sheep_upgrade_time"].toInt() != -1)
        timer->start(7776000);

    connect(timer,SIGNAL(timeout()),this,SLOT(increamenter()));
    ui->label->setText("<b> exist sheep </b>");
}

sheep_pasture::~sheep_pasture()
{
    delete ui;
}

void sheep_pasture::increamenter()
{
    int aux = 0;
    aux = ui->sheep_pro->value();
    aux++;
    ui->sheep_pro->setValue(aux);
}

void sheep_pasture::on_feed_clicked()
{
    if(info["sheep_feed_time"].toInt() != -1)
        QMessageBox::warning(this , " " ,"Sheeps are feeding!");
    else{
        if(info["alfalfa_count"].toInt() < info["sheep_count"].toInt()){
            QMessageBox::warning(this , " " ,"<b>Alfalfa</b> needed!");
        }
        else{
            info["alfalfa_count"] = QJsonValue(info["alfalfa_count"].toInt() - info["sheep_count"].toInt());
            time_t _time = time(NULL) + info["time"].toInt();
            info["sheep_feed_time"] = _time;
            QJsonArray info_2 = _info["User"].toArray();
            info_2[id] = QJsonValue(info);
            _info["User"] = info_2;
            write_info(_info);
        }
    }
}


void sheep_pasture::on_upgrade_clicked()
{
    if(info["level_player"].toInt() < info["sheep_level"].toInt() + 6)
        QMessageBox::warning(this , " " ,"You need to reach <b>level </b>" + QString::number(info["sheep_level"].toInt() + 6));
    else if(info["nail_count"].toInt() < 3)
        QMessageBox::warning(this , " " ,"<b>Nail</b> needed!");
    else if(info["shovel_count"].toInt() < 1)
        QMessageBox::warning(this , " " ,"<b>Shovel</b> needed!");
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
    }
}


void sheep_pasture::on_Fleece_Shave_clicked()
{
    time_t _time = time(NULL) + info["time"].toInt();
    if(_time -  info["sheep_feed_time"].toInt() >= 864000){
        if(info["coin"].toInt() < info["sheep_count"].toInt()){
            QMessageBox::warning(this , " " ,"<b>Coin</b> needed!");
        }
        else{
            if(ceil(5 * pow(1.5, info["barn_level"].toInt() -1 )) <
                    info["nail_count"].toInt() +
                    info["shovel_count"].toInt() +
                    info["alfalfa_count"].toInt() +
                    info["eggs_count"].toInt() +
                    info["milk_count"].toInt() +
                    info["fleece_count"].toInt() +
                    info["sheep_count"].toInt()){//sheep count for added fleece number
                QMessageBox::warning(this , " " ,"You don't have enough space in barn!");
            }
            else{
                info["fleece_count"] = QJsonValue(info["fleece_count"] .toInt() + info["sheep_count"].toInt());
                info["sheep_feed_time"] = -1;
                QJsonArray info_2 = _info["User"].toArray();
                info_2[id] = QJsonValue(info);
                _info["User"] = info_2;
                write_info(_info);
            }
        }
    }
    else
        QMessageBox::warning(this , " " ,"Sheeps are feeding!");
}


void sheep_pasture::on_build_clicked()
{
    if(info["level_player"].toInt() < 6)
        QMessageBox::warning(this , " " ,"You need to reach <b>level 6</b>");
    else if(info["nail_count"].toInt()  < 4)
        QMessageBox::warning(this , " " ,"<b>Nail</b> needed!");
    else if(info["shovel_count"].toInt()  < 2)
        QMessageBox::warning(this , " " ,"<b>Shovel</b> needed!");
    else if(info["coin"].toInt() < 50)
        QMessageBox::warning(this , " " ,"<b>Coin</b> needed!");
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
    }
}
