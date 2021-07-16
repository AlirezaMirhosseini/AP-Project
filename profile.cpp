#include "profile.h"
#include "ui_profile.h"
#include "information.h"
profile::profile(QWidget *parent, int _id , QByteArray ranks) :
    QDialog(parent),
    ui(new Ui::profile)
{
    id=_id;
    ui->setupUi(this);
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
