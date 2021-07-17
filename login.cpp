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

    // Username Validation
    QRegularExpression validate_username("\\b[A-Z0-9]{1,50}\\b",
                          QRegularExpression::CaseInsensitiveOption);
    ui->lineEdit->setValidator(new QRegularExpressionValidator(validate_username, this));
    // Password Validation
    QRegularExpression validate_password("\\b[A-Z0-9+!@#$%^&*()<>{}.?;=_:/'\"]{1,50}\\b",
                          QRegularExpression::CaseInsensitiveOption);
    ui->lineEdit_2->setValidator(new QRegularExpressionValidator(validate_password, this));
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty())
        QMessageBox::warning(this,"Fill the blanks!","Username is empty! please fill it !");
    else if(ui->lineEdit_2->text().isEmpty())
        QMessageBox::warning(this,"Fill the blanks!","Password is empty please fill it !");
    else{
        bool temp = 1;
        QJsonObject _info = read_info();
        QJsonArray info = _info["User"].toArray();
        for(int counter = 0; counter < info.size(); counter++){
            if( (info[counter].toObject())["username"] == ui->lineEdit->text() &&
                    (info[counter].toObject())["password"] == ui->lineEdit_2->text()){
                this->close();
                temp = 0;
                farm *w = new farm( counter);
                w->show();
            }
        }
        if(temp){
            QMessageBox::warning(this,"Not found !","There is no any account with these Username and Password !");
        }
    }
}

void login::on_pushButton_2_clicked()
{
    register_info* w = new register_info;
    w->show();
    this->close();
}

