#include "store.h"
#include "ui_store.h"
#include "information.h"
#include <QJsonObject>
#include <QMessageBox>
#include <math.h>

store::store(QWidget *parent, int _id) :
    QDialog(parent),
    ui(new Ui::store)
{
    id=_id;
    ui->setupUi(this);
     _info = read_info();
     info = (_info["User"].toArray())[id].toObject();
    ui->coin_label->setText(QString::number(info["coin"].toInt()));

    ui->alfalfa_label->setText(QString::number(info["alfalfa_count"].toInt()));
    ui->cow_label->setText(QString::number(info["cow_count"].toInt()));
    ui->wheat_label->setText(QString::number(info["wheat_count"].toInt()));
    ui->hen_label->setText(QString::number(info["chicken_count"].toInt()));
    ui->sheep_label->setText(QString::number(info["sheep_count"].toInt()));
    ui->nail_label->setText(QString::number(info["nail_count"].toInt()));
    ui->shovel_label->setText(QString::number(info["shovel_count"].toInt()));
    ui->wool_label->setText(QString::number(info["fleece_count"].toInt()));
    ui->milk_label->setText(QString::number(info["milk_count"].toInt()));
    ui->egg_label->setText(QString::number(info["egg_count"].toInt()));
}

store::~store()
{
    delete ui;

}



void store::on_sell_pushButton_clicked()
{

    int cow_num,hen_num,wool_num,sheep_num,nail_num,milk_num,egg_num,wheat_num,alfalfa_num,shovel_num;


    cow_num=ui->cow_spinBox->text().toInt();
    if(cow_num>info["cow_count"].toInt())
    {
        QMessageBox::warning(this," ","you don't have enough cow to sell :(");
        return;
    }


    hen_num=ui->hen_spinBox->text().toInt();
    if(hen_num>info["chicken_count"].toInt())
    {
        QMessageBox::warning(this," ","you don't have enough hen to sell :(");
        return;
    }


    sheep_num=ui->sheep_spinBox->text().toInt();
    if(sheep_num>info["sheep_count"].toInt())
    {
        QMessageBox::warning(this," ","you don't have enough sheep to sell :(");
        return;
    }


    nail_num=ui->nail_spinBox->text().toInt();
    if(nail_num>info["nail_count"].toInt())
    {
        QMessageBox::warning(this," ","you don't have enough neil to sell :(");
        return;
    }


    milk_num=ui->milk_spinBox->text().toInt();
    if(milk_num>info["milk_count"].toInt())
    {
        QMessageBox::warning(this," ","you don't have enough milk to sell :(");
        return;
    }


    egg_num=ui->egg_spinBox->text().toInt();
    if(egg_num>info["eggs_count"].toInt())
    {
        QMessageBox::warning(this," ","you don't have enough egg to sell :(");
        return;
    }


    wheat_num=ui->wheat_pinBox->text().toInt();
    if(wheat_num>info["wheat_count"].toInt())
    {
        QMessageBox::warning(this," ","you don't have enough wheat to sell :(");
        return;
    }


    alfalfa_num=ui->alfala_spinBox->text().toInt();
    if(alfalfa_num>info["alfalfa_count"].toInt())
    {
        QMessageBox::warning(this," ","you don't have enough alfalfa to sell :(");
        return;
    }


    shovel_num=ui->shovel_spinBox->text().toInt();
    if(shovel_num>info["shovel_counter"].toInt())
    {
        QMessageBox::warning(this," ","you don't have enough shovel to sell :(");
        return;
    }


    wool_num=ui->wool_spinBox->text().toInt();
    if(wool_num>info["fleece_count"].toInt())
    {
        QMessageBox::warning(this," ","you don't have enough wool to sell :(");
        return;
    }

    int reciving_coins=wool_num*23+shovel_num*30+nail_num*20+sheep_num*70+milk_num*12+cow_num*50+egg_num*8+hen_num*15+alfalfa_num*4+wheat_num*2;
    info["coin"]=info["coin"].toInt()+reciving_coins;

    info["fleece_count"]=info["fleece_count"].toInt()-wool_num;
    info["shovel_count"]=info["shovel_count"].toInt()-shovel_num;
    info["alfalfa_count"]=info["alfalfa_count"].toInt()-alfalfa_num;
    info["wheat_count"]=info["wheat_count"].toInt()-wheat_num;
    info["eggs_count"]=info["eggs_count"].toInt()-egg_num;
    info["milk_count"]=info["milk_count"].toInt()-milk_num;
    info["nail_count"]=info["nail_count"].toInt()-nail_num;
    info["sheep_count"]=info["sheep_count"].toInt()-sheep_num;
    info["cow_count"]=info["cow_count"].toInt()-cow_num;
    info["chicken_count"]=info["chicken_count"].toInt()-hen_num;


    ui->coin_label->setText(QString::number(info["coin"].toInt()));

    ui->alfalfa_label->setText(QString::number(info["alfalfa_count"].toInt()));
    ui->cow_label->setText(QString::number(info["cow_count"].toInt()));
    ui->wheat_label->setText(QString::number(info["wheat_count"].toInt()));
    ui->hen_label->setText(QString::number(info["chicken_count"].toInt()));
    ui->sheep_label->setText(QString::number(info["sheep_count"].toInt()));
    ui->nail_label->setText(QString::number(info["nail_count"].toInt()));
    ui->shovel_label->setText(QString::number(info["shovel_count"].toInt()));
    ui->wool_label->setText(QString::number(info["fleece_count"].toInt()));
    ui->milk_label->setText(QString::number(info["milk_count"].toInt()));
    ui->egg_label->setText(QString::number(info["egg_count"].toInt()));


    ui->alfala_spinBox->setValue(0);
    ui->cow_spinBox->setValue(0);
    ui->sheep_spinBox->setValue(0);
    ui->wheat_pinBox->setValue(0);
    ui->nail_spinBox->setValue(0);
    ui->shovel_spinBox->setValue(0);
    ui->hen_spinBox->setValue(0);
    ui->wool_spinBox->setValue(0);
    ui->egg_spinBox->setValue(0);
    ui->milk_spinBox->setValue(0);



    QJsonArray info_2 = _info["User"].toArray();
       info_2[id] = QJsonValue(info);
       _info["User"] = info_2;
        write_info(_info);

}




void store::on_buy_pushButton_clicked()
{

    int cow_num,hen_num,wool_num,sheep_num,nail_num,milk_num,egg_num,wheat_num,alfalfa_num,shovel_num;

    cow_num=ui->cow_spinBox->text().toInt();
    if(info["level_palyer"].toInt()<4&&cow_num>0)
    {
        QMessageBox::warning(this," ","your level is too low to have cow :(");
        return;
    }
    if(info["cow_level"].toInt()==0&&cow_num>0)
    {
        QMessageBox::warning(this," ","your don't have cow pasture :(");
        return;
    }
    if(cow_num>(pow(2,info["cow_level"].toInt())-info["cow_count"].toInt()))
    {
        QMessageBox::warning(this," ","you don't have enough space in cow pasture :(");
        return;
    }



    hen_num=ui->hen_spinBox->text().toInt();
    if(info["level_palyer"].toInt()<2&&hen_num>0)
    {
        QMessageBox::warning(this," ","your level is too low to have chicken :(");
        return;
    }
    if(info["chicken_level"].toInt()==0&&hen_num>0)
    {
        QMessageBox::warning(this," ","your don't have chicken coop :(");
        return;
    }
    if(hen_num>(pow(2,info["chicken_level"].toInt())-info["chicken_count"].toInt()))
    {
        QMessageBox::warning(this," ","you don't have enough space in chicken coop :(");
        return;
    }




    sheep_num=ui->sheep_spinBox->text().toInt();
    if(info["level_palyer"].toInt()<6&&sheep_num>0)
    {
        QMessageBox::warning(this," ","your level is too low to have sheep :(");
        return;
    }
    if(info["sheep_level"].toInt()==0&&sheep_num>0)
    {
        QMessageBox::warning(this," ","your don't have sheep pasture :(");
        return;
    }
    if(sheep_num>(pow(2,info["sheep_level"].toInt())-info["sheep_count"].toInt()))
    {
        QMessageBox::warning(this," ","you don't have enough space in sheep pasture :(");
        return;
    }



    milk_num=ui->milk_spinBox->text().toInt();
    if(milk_num>0)
    {
        QMessageBox::warning(this," ","you can't buy milk :(");
        return;
    }


    egg_num=ui->egg_spinBox->text().toInt();
    if(egg_num>0)
    {
        QMessageBox::warning(this," ","you can't buy egg :(");
        return;
    }

    wool_num=ui->wool_spinBox->text().toInt();
    if(wool_num>0)
    {
        QMessageBox::warning(this," ","you can't buy fleece :(");
        return;
    }



    wheat_num=ui->wheat_pinBox->text().toInt();
    if(wheat_num>(10*(pow(2,info["wheat_level"].toInt()-1))-info["wheat_count"].toInt()))
    {
        QMessageBox::warning(this," ","you don't have enough space in silo :(");
        return;
    }


    int barn_input_num=info["fleece_count"].toInt()+info["egg_count"].toInt()+info["alfalfa_count"].toInt()+info["milk_count"].toInt()+info["shovel_count"].toInt()+info["nail_count"].toInt();
    alfalfa_num=ui->alfala_spinBox->text().toInt();
    if(info["level_palyer"].toInt()<3&&alfalfa_num>0)
    {
        QMessageBox::warning(this," ","your level is too low to have alfalfa :(");
        return;
    }
    nail_num=ui->nail_spinBox->text().toInt();
    shovel_num=ui->shovel_spinBox->text().toInt();

    if(nail_num+shovel_num+alfalfa_num>5*pow(1.5,info["barn_level"].toInt())-barn_input_num)
    {

         QMessageBox::warning(this," ","There isn't enough space in barn :(");
         return;
    }



    int paying_coins=shovel_num*50+nail_num*30+sheep_num*80+cow_num*70+hen_num*20+alfalfa_num*6+wheat_num*3;
    if(paying_coins>info["coin"].toInt())
    {
        QMessageBox::warning(this," ","your money isn't enough :(");
        return;
    }
    info["coin"]=info["coin"].toInt()-paying_coins;

    info["fleece_count"]=info["fleece_count"].toInt()+wool_num;
    info["shovel_count"]=info["shovel_count"].toInt()+shovel_num;
    info["alfalfa_count"]=info["alfalfa_count"].toInt()+alfalfa_num;
    info["wheat_count"]=info["wheat_count"].toInt()+wheat_num;
    info["eggs_count"]=info["eggs_count"].toInt()+egg_num;
    info["milk_count"]=info["milk_count"].toInt()+milk_num;
    info["nail_count"]=info["nail_count"].toInt()+nail_num;
    info["sheep_count"]=info["sheep_count"].toInt()+sheep_num;
    info["cow_count"]=info["cow_count"].toInt()+cow_num;
    info["chicken_count"]=info["chicken_count"].toInt()+hen_num;


    ui->coin_label->setText(QString::number(info["coin"].toInt()));

    ui->alfalfa_label->setText(QString::number(info["alfalfa_count"].toInt()));
    ui->cow_label->setText(QString::number(info["cow_count"].toInt()));
    ui->wheat_label->setText(QString::number(info["wheat_count"].toInt()));
    ui->hen_label->setText(QString::number(info["chicken_count"].toInt()));
    ui->sheep_label->setText(QString::number(info["sheep_count"].toInt()));
    ui->nail_label->setText(QString::number(info["nail_count"].toInt()));
    ui->shovel_label->setText(QString::number(info["shovel_count"].toInt()));
    ui->wool_label->setText(QString::number(info["fleece_count"].toInt()));
    ui->milk_label->setText(QString::number(info["milk_count"].toInt()));
    ui->egg_label->setText(QString::number(info["egg_count"].toInt()));


    ui->alfala_spinBox->setValue(0);
    ui->cow_spinBox->setValue(0);
    ui->sheep_spinBox->setValue(0);
    ui->wheat_pinBox->setValue(0);
    ui->nail_spinBox->setValue(0);
    ui->shovel_spinBox->setValue(0);
    ui->hen_spinBox->setValue(0);
    ui->wool_spinBox->setValue(0);
    ui->egg_spinBox->setValue(0);
    ui->milk_spinBox->setValue(0);



    QJsonArray info_2 = _info["User"].toArray();
       info_2[id] = QJsonValue(info);
       _info["User"] = info_2;
        write_info(_info);
}
