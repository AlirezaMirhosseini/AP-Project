#include "login.h"
#include "ui_login.h"
#include<QLabel>
#include<QMessageBox>
#include"information.h"
#include"game.h"
#include<math.h>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    QJsonObject _info=read_info();
     QJsonArray info_2 ;
      time_t _time = time(NULL);
    for(int i = 0; i < _info["User"].toArray().size() ; i++){
         QJsonObject info = _info["User"].toArray()[i].toObject();
        if(info["chicken_upgrade_time"].toInt() != -1 && _time - info["chicken_upgrade_time"].toInt() >= 259200 )
        {
            info["chicken_upgrade_time"] = -1;
        info["chicken_level"] = QJsonValue(info["chicken_level"].toInt() + 1); //when upgrade finished
          info["exp"] = QJsonValue(info["exp"].toInt() + 5);
    }

         else if(info["chicken_upgrade_time"].toInt() != -1){
             int dif_time = _time - info["chicken_upgrade_time"].toInt();
             info["chicken_upgrade_pro"] = (dif_time * 100 /259200);
        }

        if(info["cow_upgrade_time"].toInt() != -1 && _time - info["cow_upgrade_time"].toInt() >= 432000 )
        {
            info["cow_upgrade_time"] = -1;
        info["cow_level"] = QJsonValue(info["cow_level"].toInt() + 1); //when upgrade finished
          info["exp"] = QJsonValue(info["exp"].toInt() + 6);
    }
        else if(info["cow_upgrade_time"].toInt() != -1){
             int dif_time = _time - info["cow_upgrade_time"].toInt();
            info["cow_upgrade_pro"] =  dif_time * 100 /432000;
        }

        if(info["sheep_upgrade_time"].toInt() != -1 && _time - info["sheep_upgrade_time"].toInt() >= 777600 )
        {
         info["sheep_upgrade_time"] = -1;
         info["sheep_level"] = QJsonValue(info["sheep_level"].toInt() + 1); //when upgrade finished
           info["exp"] = QJsonValue(info["exp"].toInt() + 15);

        }
        else if(info["sheep_upgrade_time"].toInt() != -1){
             int dif_time = _time - info["sheep_upgrade_time"].toInt();
             info["sheep_upgrade_pro"]  = dif_time * 100 /777600 ;
        }



        if(info["wheat_upgrade_time"].toInt() != -1 && _time - info["wheat_upgrade_time"].toInt() >= 172800 )
        {
            info["wheat_upgrade_time"] = -1;
        info["wheat_level"] = QJsonValue(info["wheat_level"].toInt() + 1); //when upgrade finished
          info["exp"] = QJsonValue(info["exp"].toInt() + 3 * 5 * pow(2, info["wheat_level"].toInt() - 2));
         }
        else if(info["wheat_upgrade_time"].toInt() != -1){
             int dif_time = _time - info["wheat_upgrade_time"].toInt();
            info["wheat_upgrade_pro"] = dif_time * 100 /172800 ;
        }

        if(info["wheat_seed_time"].toInt() != -1 && _time - info["wheat_seed_time"].toInt() >= 172800)
          {
            info["wheat_seed_time"] = -1;
            info["wheat_in_use"] = false;
          }

        else if(info["wheat_seed_time"].toInt() != -1){
           int dif_time = _time - info["wheat_seed_time"].toInt();
            info["wheat_seed_pro"] = dif_time * 100 /172800 ;
        }


        if(info["alfalfa_seed_time"].toInt() != -1 && _time - info["alfalfa_seed_time"].toInt() >= 345600)
        {
            info["alfalfa_seed_time"] = -1;
            info["alfalfa_in_use"] = false;
        }
        else if(info["alfalfa_seed_time"].toInt() != -1){
           int dif_time = _time - info["alfalfa_seed_time"].toInt();
            info["alfalfa_seed_pro"] = dif_time * 100 /345600 ;
        }


        if(info["alfalfa_upgrade_time"].toInt() != -1 && _time - info["alfalfa_upgrade_time"].toInt() >= 259200  )
        {
           info["alfalfa_upgrade_time"] = -1;
           info["exp"] = QJsonValue(info["exp"].toInt() + 3 *(4 * pow (2, info["alfalfa_level"].toInt() - 1))); //when upgrade finished
           info["alfalfa_level"] = QJsonValue(info["alfalfa_level"].toInt() + 1);
        }
        else if(info["alfalfa_upgrade_time"].toInt() != -1)
        {
             int dif_time = _time - info["alfalfa_upgrade_time"].toInt();
             info["alfalfa_upgrade_pro"]  = dif_time * 100 /259200;
        }

        if(info["barn_upgrade_time"].toInt() != -1 && _time - info["barn_upgrade_time"].toInt() > 432000)
        {
            info["barn_upgrade_time"] = -1;
            info["exp"] = QJsonValue(info["exp"].toInt() + 3 *(info["barn_level"].toInt())); //when upgrade finished
            info["barn_level"] =  QJsonValue(info["barn_level"].toInt() + 1) ;
        }
        else if(info["barn_upgrade_time"].toInt() != -1)
        {
            int dif_time = _time - info["barn_upgrade_time"].toInt();
            info["barn_upgrade_pro"]  = dif_time * 100 /432000;

        }


        if(info["silo_upgrade_time"].toInt() != -1 && _time - info["silo_upgrade_time"].toInt() > 345600)
        {
            info["silo_upgrade_time"] = -1;
            info["exp"] = QJsonValue(info["exp"].toInt() + 2 *(info["silo_level"].toInt())); //when upgrade finished
            info["silo_level"] =  QJsonValue(info["silo_level"].toInt() + 1);
        }
        else if(info["silo_upgrade_time"].toInt() != -1)
        {
            int dif_time = _time - info["silo_upgrade_time"].toInt();
            info["silo_upgrade_pro"]  = dif_time * 100 /345600;

        }

        if(info["alfalfa_plow_time"].toInt() != -1 && _time - info["alfalfa_plow_time"].toInt() >= 86400)
                    info["alfalfa_plow_time"] = -1;
         else if(info["alfalfa_plow_time"].toInt() != -1){
                   int dif_time = _time - info["alfalfa_plow_time"].toInt();
                    info["alfalfa_plow_pro"] = dif_time * 100 /86400 ;
         }

        if(info["alfalfa_plow_time"].toInt() != -1 && _time - info["alfalfa_plow_time"].toInt() >= 86400)
        {
          info["alfalfa_plow_time"] = -1;
          info["alfalfa_plowed"] = QJsonValue(true);
         }
        else if(info["alfalfa_plow_time"].toInt() != -1)
        {
            int dif_time = _time - info["alfalfa_plow_time"].toInt();
            info["alfalfa_plow_pro"] = dif_time * 100 /86400 ;
        }





        for(int j= 0 ; j < info["milks"].toArray().size() ; j++ )
        {
           if(_time - info["milks"].toArray()[j].toInt() >= 864000)
               info["milks"].toArray().erase(info["milks"].toArray().begin() + j);
        }
            info_2.push_back(QJsonValue(info));
    }
      check_level();
    _info["User"] = info_2;
    write_info(_info);
}

login::~login()

{
    delete ui;
}

void login::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty()||ui->lineEdit_2->text().isEmpty()){
        QMessageBox::warning(this," ","username or password is empty please fill both of them");
    }
    else{
        bool temp=1;
        QJsonObject _info=read_info();
        QJsonArray info = _info["User"].toArray();
        for(int counter = 0; counter < info.size(); counter++){
            if( (info[counter].toObject())["username"]==ui->lineEdit->text() && (info[counter].toObject())["password"] == ui->lineEdit_2->text()){
                this->close();
                temp = 0;
                farm *w = new farm(this, counter);
                w->show();
            }
        }
        if(temp){
            QMessageBox::warning(this," ","there is no any account with these username and password");
        }
    }
}

void login::on_pushButton_2_clicked()
{
    register_info* w = new register_info;
    w->show();
    this->close();
}

