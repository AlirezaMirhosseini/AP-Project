#include "profile.h"
#include "ui_profile.h"

profile::profile(QWidget *parent, int _id) :
    QDialog(parent),
    ui(new Ui::profile)
{
    id=_id;
    ui->setupUi(this);
}

profile::~profile()
{
    delete ui;
}
