#include "time_thread.h"
#include "information.h"

time_thread::time_thread(QObject *parent) : QThread(parent)
{

}

void time_thread::run()
{
    forever{
        QJsonObject _info  = read_info();
        QJsonArray info_2 ;

        for(int i = 0; i < _info["User"].toArray().size() ; i++){
            QJsonObject info = _info["User"].toArray()[i].toObject();

            time_t _time = time(NULL)  + info["time"].toInt();
            // Upgrade & Build
            if(info["chicken_upgrade_time"].toInt() != -1 && _time - info["chicken_upgrade_time"].toInt() >= 259200 ){
                info["chicken_upgrade_time"] = -1;
                info["chicken_level"] = QJsonValue(info["chicken_level"].toInt() + 1); //when upgrade finished
                info["exp"] = QJsonValue(info["exp"].toInt() + 5);
            }
            else if(info["chicken_upgrade_time"].toInt() != -1){
                int dif_time = _time - info["chicken_upgrade_time"].toInt();
                info["chicken_upgrade_pro"] = (dif_time * 100 /259200);
            }

            // Before Build
            if(info["cow_upgrade_time"].toInt() != -1 && info["cow_level"].toInt() == 0 && _time - info["cow_upgrade_time"].toInt() >= 432000 )
            {
                info["cow_upgrade_time"] = -1;
                info["cow_level"] = QJsonValue(1); //when upgrade finished
                info["exp"] = QJsonValue(info["exp"].toInt() + 10);
            }
            else if(info["cow_upgrade_time"].toInt() != -1 && info["cow_level"].toInt() == 0){
                int dif_time = _time - info["cow_upgrade_time"].toInt();
                info["cow_upgrade_pro"] =  dif_time * 100 /432000;
            }

            // After Build
            if(info["cow_upgrade_time"].toInt() != -1 && info["cow_level"].toInt() != 0 && _time - info["cow_upgrade_time"].toInt() >= 432000 ){
                info["cow_upgrade_time"] = -1;
                info["cow_level"] = QJsonValue(info["cow_level"].toInt() + 1); //when upgrade finished
                info["exp"] = QJsonValue(info["exp"].toInt() + 6);
            }
            else if(info["cow_upgrade_time"].toInt() != -1 && info["cow_level"].toInt() != 0){
                int dif_time = _time - info["cow_upgrade_time"].toInt();
                info["cow_upgrade_pro"] =  dif_time * 100 /432000;
            }

            // Before Build
            if(info["sheep_upgrade_time"].toInt() != -1 && info["sheep_level"].toInt() == 0 && _time - info["sheep_upgrade_time"].toInt() >= 777600 ){
                info["sheep_upgrade_time"] = -1;
                info["sheep_level"] = QJsonValue(1); //when upgrade finished
                info["exp"] = QJsonValue(info["exp"].toInt() + 20);
            }
            else if(info["sheep_upgrade_time"].toInt() != -1 && info["sheep_level"].toInt() == 0){
                int dif_time = _time - info["sheep_upgrade_time"].toInt();
                info["sheep_upgrade_pro"]  = dif_time * 100 /864000 ;
            }

            // After Build
            if(info["sheep_upgrade_time"].toInt() != -1 && info["sheep_level"].toInt() != 0  && _time - info["sheep_upgrade_time"].toInt() >= 777600 ){
                info["sheep_upgrade_time"] = -1;
                info["sheep_level"] = QJsonValue(info["sheep_level"].toInt() + 1); //when upgrade finished
                info["exp"] = QJsonValue(info["exp"].toInt() + 15);
            }
            else if(info["sheep_upgrade_time"].toInt() != -1 && info["sheep_level"].toInt() != 0){
                int dif_time = _time - info["sheep_upgrade_time"].toInt();
                info["sheep_upgrade_pro"]  = dif_time * 100 /777600 ;
            }

            // Exist from beginning
            if(info["wheat_upgrade_time"].toInt() != -1 && _time - info["wheat_upgrade_time"].toInt() >= 100 ){
                info["wheat_upgrade_time"] = -1;
                info["wheat_level"] = QJsonValue(info["wheat_level"].toInt() + 1); //when upgrade finished
                info["exp"] = QJsonValue(info["exp"].toInt() + 3 * 5 * pow(2, info["wheat_level"].toInt() - 2));
            }
            else if(info["wheat_upgrade_time"].toInt() != -1){
                int dif_time = _time - info["wheat_upgrade_time"].toInt();
                info["wheat_upgrade_pro"] = dif_time * 100 /100 ;
            }
            if(info["wheat_seed_time"].toInt() != -1 && _time - info["wheat_seed_time"].toInt() >= 100){
                info["wheat_seed_time"] = -1;
            }
            else if(info["wheat_seed_time"].toInt() != -1){
                int dif_time = _time - info["wheat_seed_time"].toInt();
                info["wheat_seed_pro"] = dif_time * 100 /100;
            }

            // Before Build
            if(info["alfalfa_upgrade_time"].toInt() != -1 && info["alfalfa_level"].toInt() == 0 && _time - info["alfalfa_upgrade_time"].toInt() >= 100  ){
                info["alfalfa_upgrade_time"] = -1;
                info["exp"] = QJsonValue(info["exp"].toInt() + 6); //when upgrade finished
                info["alfalfa_level"] = QJsonValue(1);
            }
            else if(info["alfalfa_upgrade_time"].toInt() != -1 && info["alfalfa_level"].toInt() == 0){
                int dif_time = _time - info["alfalfa_upgrade_time"].toInt();
                info["alfalfa_upgrade_pro"]  = dif_time * 100 /100;
            }

            // After Build
            if(info["alfalfa_upgrade_time"].toInt() != -1 && info["alfalfa_level"].toInt() != 0 && _time - info["alfalfa_upgrade_time"].toInt() >= 100  ){
                info["alfalfa_upgrade_time"] = -1;
                info["exp"] = QJsonValue(info["exp"].toInt() + 3 *(4 * pow (2, info["alfalfa_level"].toInt() - 1))); //when upgrade finished
                info["alfalfa_level"] = QJsonValue(info["alfalfa_level"].toInt() + 1);
            }
            else if(info["alfalfa_upgrade_time"].toInt() != -1 && info["alfalfa_level"].toInt() != 0){
                int dif_time = _time - info["alfalfa_upgrade_time"].toInt();
                info["alfalfa_upgrade_pro"]  = dif_time * 100 /100;
            }

            if(info["alfalfa_seed_time"].toInt() != -1 && _time - info["alfalfa_seed_time"].toInt() >= 100){
                info["alfalfa_seed_time"] = -1;
                info["alfalfa_in_use"] = false;
            }
            else if(info["alfalfa_seed_time"].toInt() != -1){
                int dif_time = _time - info["alfalfa_seed_time"].toInt();
                info["alfalfa_seed_pro"] = dif_time * 100 /100 ;
            }

            if(info["alfalfa_plow_time"].toInt() != -1 && _time - info["alfalfa_plow_time"].toInt() >= 100){
                info["alfalfa_plow_time"] = -1;
                info["alfalfa_plowed"] = QJsonValue(true);
            }
            else if(info["alfalfa_plow_time"].toInt() != -1){
                int dif_time = _time - info["alfalfa_plow_time"].toInt();
                info["alfalfa_plow_pro"] = dif_time * 100 /100 ;
            }

            if(info["barn_upgrade_time"].toInt() != -1 && _time - info["barn_upgrade_time"].toInt() > 432000){
                info["barn_upgrade_time"] = -1;
                info["exp"] = QJsonValue(info["exp"].toInt() + 3 *(info["barn_level"].toInt())); //when upgrade finished
                info["barn_level"] =  QJsonValue(info["barn_level"].toInt() + 1) ;
            }
            else if(info["barn_upgrade_time"].toInt() != -1){
                int dif_time = _time - info["barn_upgrade_time"].toInt();
                info["barn_upgrade_pro"]  = dif_time * 100 /432000;
            }

            if(info["silo_upgrade_time"].toInt() != -1 && _time - info["silo_upgrade_time"].toInt() > 345600){
                info["silo_upgrade_time"] = -1;
                info["exp"] = QJsonValue(info["exp"].toInt() + 2 *(info["silo_level"].toInt())); //when upgrade finished
                info["silo_level"] =  QJsonValue(info["silo_level"].toInt() + 1);
            }
            else if(info["silo_upgrade_time"].toInt() != -1){
                int dif_time = _time - info["silo_upgrade_time"].toInt();
                info["silo_upgrade_pro"]  = dif_time * 100 /345600;
            }

            for(int j= 0 ; j < info["milks"].toArray().size() ; j++ )
                if(_time - info["milks"].toArray()[j].toInt() >= 864000)
                    info["milks"].toArray().erase(info["milks"].toArray().begin() + j);

            for(int j=  info["level_player"].toInt() ; true ; j++){
                if(info["exp"].toInt() < (pow(2 , j) -1)*10){
                    info["level_player"] = QJsonValue(j) ;
                    break;
                }
            }
            info_2.push_back(QJsonValue(info));
        }
        _info["User"] = info_2;
        write_info(_info);
        this->msleep(100);
    }

}
