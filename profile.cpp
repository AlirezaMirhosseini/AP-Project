#include "profile.h"
#include "ui_profile.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPixmap>

#include "information.h"
profile::profile(QWidget *parent, int _id , QByteArray ranks) :

    QDialog(parent),
    ui(new Ui::profile)
{
    QJsonObject _info = read_info();
    QJsonObject  info = (_info["User"].toArray())[_id].toObject();
    id=_id;
    ui->setupUi(this);
    if(info["gender"].toString()=="      Male")
        ui->farmer->setPixmap(QPixmap(":/game_backgrounds/pics_project/profile use.png"));
    else
        ui->farmer->setPixmap(QPixmap(":/game_backgrounds/pics_project/woman farmer.png"));

    QJsonDocument doc = QJsonDocument::fromJson(ranks);
    QJsonObject file_obg = doc.object();
    QJsonArray file_Array = file_obg["User"].toArray();
    for(int counter=0;counter<file_Array.size();counter++){

    }
}

profile::~profile()
{
    delete ui;
}
