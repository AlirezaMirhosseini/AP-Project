#pragma once

#ifndef FARM_H
#define FARM_H
#include <QDialog>
#include "game.h"
#include "barn.h"
#include "silo.h"
#include "chicken_coop.h"
#include "cow_pasture.h"
#include "sheep_pasture.h"
#include "wheat_field.h"
#include "alfalfa_field.h"
#include "store.h"

namespace Ui {class farm;}

class farm : public QDialog
{
    Q_OBJECT

public:
    explicit farm(QWidget *parent = nullptr, int _id = 0);
    ~farm();


private slots:

    void on_sheep_pushButton_clicked();

    void on_store_pushButton_clicked();

    void on_chicken_pushButton_clicked();

    void on_wheat_pushButton_clicked();

    void on_barn_pushButton_clicked();

    void on_cow_pushButton_clicked();

    void on_silo_pushButton_clicked();

    void on_alfalfa_pushButton_clicked();

    void on_profile_pushButton_clicked();

private:

    Ui::farm *ui;
    int id;

};

#endif // FARM_H
