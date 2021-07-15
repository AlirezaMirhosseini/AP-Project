#include "farm.h"
#include "ui_farm.h"
#include "cow_pasture.h"

#include "information.h"
#include <QIcon>

#include <login.h>


farm::farm(QWidget *parent, int _id) :
    QDialog(parent),
    ui(new Ui::farm)
{

    ui->setupUi(this);
    id = _id;
    QJsonObject _info = read_info();
     QJsonObject  info = (_info["User"].toArray())[id].toObject();
     time_t now = time(NULL)+info["time"].toInt();
     ui->exp_num->setText(QString::number(info["exp"].toInt()));
     ui->level_num->setText(QString::number(info["level_player"].toInt()));
     ui->day->setText(QString::number((int)((now-info["signup_time"].toInt())/86400)));

    if(info["gender"].toString()=="      Male")
        ui->profile_pushButton->setIcon(QIcon(":/game_backgrounds/pics_project/138manfarmer2_100718.png"));
    else
    ui->profile_pushButton->setIcon(QIcon(":/game_backgrounds/pics_project/139womanfarmer1_100885 (1).png"));
}



farm::~farm()
{
    delete ui;
}


void farm::on_sheep_pushButton_clicked()
{
    sheep_pasture * _sheep_pasture = new sheep_pasture(this , id);
    _sheep_pasture->show();
}


void farm::on_store_pushButton_clicked()
{
    store *Store=new store(this , id);
    Store->show();
}


void farm::on_chicken_pushButton_clicked()
{
    chicken_coop * _chicken_coop = new chicken_coop(this , id);
    _chicken_coop->show();
}



void farm::on_wheat_pushButton_clicked()
{
    wheat_field* wheatField = new wheat_field(this, id);
    wheatField->show();
}


void farm::on_barn_pushButton_clicked()
{
    barn* _barn = new barn(this, id);
    _barn->show();
}



void farm::on_cow_pushButton_clicked()
{
    cow_pasture* _cow_pasture = new cow_pasture(this , id);
    _cow_pasture->show();
}


void farm::on_silo_pushButton_clicked()
{
    silo* _silo = new silo(this, id);
    _silo->show();
}


void farm::on_alfalfa_pushButton_clicked()
{
    alfalfa_field* _alfalfa = new alfalfa_field(this , id);
    _alfalfa->show();
}


void farm::on_profile_pushButton_clicked()
{
    game* gamer = new game(this);
    gamer->show();
}



void farm::on_next_day_clicked()
{
    QJsonObject _info = read_info();
    QJsonObject  info = (_info["User"].toArray())[id].toObject();
    info["time"]=QJsonValue(info["time"].toInt() + 86400);
    QJsonArray info_2 = _info["User"].toArray();
    info_2[id] = QJsonValue(info);
    _info["User"] = info_2;
    write_info(_info);
}


void farm::on_back_clicked()
{
    this->close();
    login *_login = new login;
    _login->show();

}

