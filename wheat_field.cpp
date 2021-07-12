#include "wheat_field.h"
#include "ui_wheat_field.h"
#include "information.h"
#include "cmath"
#include <QMessageBox>
#include <time.h>


using namespace std;

wheat_field::wheat_field(QWidget *parent, int _id) :
    QDialog(parent),
    ui(new Ui::wheat_field)
{
    ui->setupUi(this);
    id = _id;
    _info = read_info();
    info = (_info["User"].toArray())[id].toObject();

    if(info["wheat_upgrade_time"].toInt() == -1)
        ui->wheat_upgrade_pro->hide();


    ui->spinBox->setMaximum(5 * pow(2, info["wheat_level"].toInt() - 1));
    ui->label_3->setText(QString::number(5 * pow(2, info["wheat_level"].toInt() - 1)));
    ui->label_4->setText(QString::number(info["wheat_level"].toInt()));
    ui->label_6->setText(QString::number(info["wheat_cultivated_area"].toInt()));


    ui->wheat_upgrade_pro->setValue(info["wheat_upgrade_pro"].toInt());
     timer1 = new QTimer();


     if(info["wheat_upgrade_time"].toInt() != -1)
       timer1->start(1728000);

     connect(timer1,SIGNAL(timeout()),this,SLOT(increamenter()));
}


wheat_field::~wheat_field()
{
    delete ui;
}

void wheat_field::increamenter()
{
    int aux = 0;
    aux = ui->wheat_upgrade_pro->value();
    aux++;
    ui->wheat_upgrade_pro->setValue(aux);
}




void wheat_field::on_upgrade_clicked()
{

    if(info["level"].toInt() < 2)
        QMessageBox::warning(this , " " , "You have not reached <b>level 2</b> yet!!!" );
    else if(info["coin"].toInt() < 5)
        QMessageBox::warning(this , " " , "<b>Coin</b> needed!" );
    else if(info["shovel_count"].toInt() < 1)
        QMessageBox::warning(this , " " , "<b>Shovel</b> needed!" );
    else{
        info["shovel_count"] = QJsonValue(info["shovel_count"].toInt() - 1);
        info["coin"] = QJsonValue(info["coin"].toInt() - 5);
        //info["wheat_upgrading"] = QJsonValue(info["wheat_upgrading"].toBool());
        time_t _time = time(NULL);
        info["wheat_upgrade_time"] = _time;
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);
    }
}

void wheat_field::on_seed_clicked()
{

    if(info["wheat_in_use"].toBool())
        QMessageBox::warning(this , " " , "After harvesting, you can seed");
    else if(info["wheat_count"].toInt() < ui->spinBox->value())
        QMessageBox::warning(this , " " , "<b>Wheat</b> needed");
    else{
        time_t _time = time(NULL);
        info["wheat_cultivated_area"] = ui->spinBox->value();
        info["wheat_seed_time"] = _time;
        info["wheat_count"] = info["wheat_count"].toInt() - ui->spinBox->value();
        info["wheat_in_use"] = true;
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);
    }
}

void wheat_field::on_Harvesting_clicked()
{
    if(!info["wheat_in_use"].toBool())
        QMessageBox::warning(this , " " , "You havent seed yet!");
    else if(ui->seed_progress->value() != 100)
        QMessageBox::warning(this , " " , "Wheat isn't ripe");
    else{
        info["wheat_count"] = info["wheat_count"].toInt() + 2 * info["wheat_cultivated_area"].toInt();
        info["wheat_in_use"] = false;
        QJsonArray info_2 = _info["User"].toArray();
        info_2[id] = QJsonValue(info);
        _info["User"] = info_2;
        write_info(_info);
    }
}
