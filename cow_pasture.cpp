#include "cow_pasture.h"
#include "ui_cow_pasture.h"
#include "information.h"
#include <QMessageBox>
#include<cmath>
cow_pasture::cow_pasture(QWidget *parent , int _id) :
    QDialog(parent),
    ui(new Ui::cow_pasture)
{
     ui->setupUi(this);
     id = _id;
     _info = read_info();
     info = (_info["User"].toArray())[id].toObject();

     ui->count->setText(QString::number(info["cow_count"].toInt()));
     ui->capacity->setText(QString::number( pow(2,info["cow_level"].toInt())));
     ui->level->setText(QString::number(info["cow_level"].toInt()));

     if(info["cow_upgrade_time"].toInt() == -1)
           ui->cow_pro->hide();


     else
        ui->cow_pro->setValue(info["cow_upgrade_pro"].toInt());

     timer = new QTimer();


      if(info["cow_upgrade_time"].toInt() != -1)
        timer->start(4320000);

      connect(timer,SIGNAL(timeout()),this,SLOT(increamenter()));
}
cow_pasture::~cow_pasture()
{
    delete ui;
}

void cow_pasture::increamenter()
{
    int aux = 0;
    aux = ui->cow_pro->value();
    aux++;
    ui->cow_pro->setValue(aux);
}

void cow_pasture::on_upgrade_clicked()
{

    if(info["nail_count"].toInt()  < 2 || info["coin"].toInt() < 15 || info["level_palyer"].toInt() < 5 || info["level_palyer"].toInt() < info["chicken_level"].toInt() + 1 )
        QMessageBox::warning(this , " " ," ");
    else{
         info["nail_count"] = info["nail_count"].toInt() - 2 ;
         info["coin"] = info["coin"].toInt() - 15 ;
         time_t _time = time(NULL);
         info["cow_upgrade_time"] = _time;
         QJsonArray info_2 = _info["User"].toArray();
            info_2[id] = QJsonValue(info);
            _info["User"] = info_2;
             write_info(_info);

     }
  }


void cow_pasture::on_feed_clicked()
{


        if(info["alfalfa_count"].toInt()  < 2 * info["cow_count"].toInt()){
            QMessageBox::warning(this , " " ," ");

        }

        else{

             info["alfalfa_count"] = QJsonValue(info["alfalfa_count"].toInt() - 2 * info["cow_count"].toInt());
                  time_t _time = time(NULL);
                  info["cow_feed_time"] = _time;
                  QJsonArray info_2 = _info["User"].toArray();
                  info_2[id] = QJsonValue(info);
                  _info["User"] = info_2;
                  write_info(_info);

        }

}


void cow_pasture::on_collect_milk_clicked()
{


    QJsonArray milk_array = info["milks"].toArray();

    time_t _time = time(NULL);

    if(info["cow_feed_time"].toInt() == -1)
        QMessageBox::warning(this , " " ," ");
    else{

    if(_time - info["cow_feed_time"].toInt() <259200  )
        QMessageBox::warning(this , " " ," ");
    else{
        if(ceil(5*pow(1.5,info["barn_level"].toInt()-1))<info["nail_count"].toInt()+info["shovel_count"].toInt()+info["alfalfa_count"].toInt()+info["eggs_count"].toInt()+info["milk_count"].toInt()+info["fleece_count"].toInt() + info["cow_count"].toInt())//cow count for added milk number)
            QMessageBox::warning(this , " " ,"");
        else{
            time_t _time = time(NULL);
            for(int i =0 ; i < info["cow_count"].toInt() ; i++)
                milk_array.push_back(QJsonValue(_time));
            info["milks"] = milk_array;
            QJsonArray info_2 = _info["User"].toArray();
            info_2[id] = QJsonValue(info);
            _info["User"] = info_2;
            write_info(_info);

        }

    }
    }



}

