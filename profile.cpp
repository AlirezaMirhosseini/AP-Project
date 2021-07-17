#include "profile.h"
#include "ui_profile.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPixmap>
#include <QBrush>
#include "information.h"
#define color "green"
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

    QTableWidgetItem *item;
    QJsonDocument doc = QJsonDocument::fromJson(ranks);
    QJsonObject file_obg = doc.object();
    QJsonArray file_Array = file_obg["User"].toArray();
    ui->tableWidget->setRowCount(file_Array.size());
    ui->tableWidget->setColumnWidth(-1,150);
    for(int counter=0;counter<file_Array.size();counter++)
    {
        item = new QTableWidgetItem;
        item->setText(file_Array[counter].toString());
        ui->tableWidget->setItem(1,counter-1,item);
        if(file_Array[counter].toString()==info["username"].toString())
            ui->tableWidget->item(counter,0)->setBackground(QBrush(QColor(107, 255, 169)));
    }

    ui->level->setText(QString::number(info["level_player"].toInt()));
    ui->exp->setText(QString::number(info["exp"].toInt()));
}

profile::~profile()
{
    delete ui;
}
