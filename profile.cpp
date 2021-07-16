#include "profile.h"
#include "ui_profile.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPixmap>

profile::profile(QWidget *parent, int _id) :
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

}

profile::~profile()
{
    delete ui;
}
