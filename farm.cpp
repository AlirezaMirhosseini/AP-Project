#include "farm.h"
#include "ui_farm.h"
#include"cow_pasture.h"

farm::farm(QWidget *parent, int _id) :
    QDialog(parent),
    ui(new Ui::farm)
{
    ui->setupUi(this);
    id = _id;
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


void farm::on_profile_pushButton_clicked()
{
    game* gamer = new game(this);
    gamer->show();
}

