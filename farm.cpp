#include "farm.h"
#include "ui_farm.h"
#include "cow_pasture.h"
#include "information.h"
#include "client.h"
#include <QIcon>
#include <login.h>
#include <QMessageBox>
#include "profile.h"
#include<QThread>

farm::farm( int _id) :
    QDialog(),
    ui(new Ui::farm)
{
    ui->setupUi(this);
    id = _id;
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/background sound/batchbug-sweet-dreams.mp2"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->setVolume(80);
    music->play();
    QJsonObject _info = read_info();
    QJsonObject  info = (_info["User"].toArray())[id].toObject();
    time_t now = time(NULL)+info["time"].toInt();
    //ui->exp_num->setText(QString::number(info["exp"].toInt()));
    //ui->level_num->setText(QString::number(info["level_player"].toInt()));
    ui->day->setText(QString::number((int)((now-info["signup_time"].toInt())/86400)));
    ui->name->setText(info["username"].toString());

    if(info["gender"].toString()=="      Male")
        ui->profile_pushButton->setIcon(QIcon(":/game_backgrounds/pics_project/138manfarmer2_100718.png"));
    else
        ui->profile_pushButton->setIcon(QIcon(":/game_backgrounds/pics_project/139womanfarmer1_100885 (1).png"));


    if(!info["store_lock"].toBool())
        ui->store_lock->hide();

    if(!info["cow_lock"].toBool())
        ui->cow_lock->hide();

    if(!info["sheep_lock"].toBool())
        ui->sheep_lock->hide();

    if(!info["chicken_lock"].toBool())
        ui->chicken_lock->hide();

    if(!info["alfalfa_lock"].toBool())
        ui->alfalfa_lock->hide();
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

void farm::on_next_day_clicked()
{
    QJsonObject _info = read_info();
    QJsonObject  info = (_info["User"].toArray())[id].toObject();
    info["time"]=QJsonValue(info["time"].toInt() + 86400);
    QJsonArray info_2 = _info["User"].toArray();
    info_2[id] = QJsonValue(info);
    _info["User"] = info_2;
    write_info(_info);
     Refresh();
}

void farm::on_back_clicked()
{
    this->close();
    login *_login = new login;
    _login->show();
}

void farm::on_store_lock_clicked()
{
    QJsonObject _info = read_info();
    QJsonObject  info = (_info["User"].toArray())[id].toObject();
    if(info["store_lock"].toBool())
        QMessageBox::warning(this,"You must level up!" , "Store unlocks at <b>level 2</b> !");
    else{
       Refresh();
    }
}

void farm::on_cow_lock_clicked()
{
    QJsonObject _info = read_info();
    QJsonObject  info = (_info["User"].toArray())[id].toObject();
    if(info["cow_lock"].toBool())
        QMessageBox::warning(this,"You must level up!" , "Cow Pasture unlocks at <b>level 4</b> !");
    else{
       Refresh();
    }
}

void farm::on_sheep_lock_clicked()
{
    QJsonObject _info = read_info();
    QJsonObject  info = (_info["User"].toArray())[id].toObject();
    if(info["sheep_lock"].toBool())
        QMessageBox::warning(this,"You must level up!" , "Sheep Pasture unlocks at <b>level 6</b> !");
    else{
        Refresh();
    }
}

void farm::on_chicken_lock_clicked()
{
    QJsonObject _info = read_info();
    QJsonObject  info = (_info["User"].toArray())[id].toObject();
    if(info["chicken_lock"].toBool())
        QMessageBox::warning(this,"You must level up!" , "Chicken Coop unlocks at <b>level 2</b> !");
    else{
       Refresh();
    }
}

void farm::on_alfalfa_lock_clicked()
{
    QJsonObject _info = read_info();
    QJsonObject  info = (_info["User"].toArray())[id].toObject();
    if(info["alfalfa_lock"].toBool())
        QMessageBox::warning(this,"You must level up!" , "Alfalfa Field unlocks at <b>level 3</b> !");
    else{
        Refresh();
    }
}

void farm::on_profile_pushButton_clicked()
{
    QByteArray data;
    client * window = new client (this , id);
    //profile* window2 = new profile(this,id,data);
    //window2->show();
    // window->show();
}


void farm::on_refresh_clicked()
{
    Refresh();

}

void farm::Refresh()
{
     QThread::msleep(100);
    this->close();
    farm *w = new farm(id);
    w->show();
}

