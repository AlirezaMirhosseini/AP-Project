#include "login.h"
#include "ui_login.h"
#include <QLabel>
#include <QMessageBox>
#include "information.h"
#include "game.h"
#include <math.h>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty()){
        QMessageBox::warning(this," ","username or password is empty please fill both of them");
    }
    else{
        bool temp=1;
        QJsonObject _info=read_info();
        QJsonArray info = _info["User"].toArray();
        for(int counter = 0; counter < info.size(); counter++){
            if( (info[counter].toObject())["username"]==ui->lineEdit->text() &&
                    (info[counter].toObject())["password"] == ui->lineEdit_2->text()){
                this->close();
                temp = 0;
                farm *w = new farm( counter);
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

