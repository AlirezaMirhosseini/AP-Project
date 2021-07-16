#pragma once

#ifndef WHEAT_FIELD_H
#define WHEAT_FIELD_H

#include <QDialog>
#include <QTimer>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {class wheat_field;}

class wheat_field : public QDialog
{
    Q_OBJECT

public:
    explicit wheat_field(QWidget *parent = nullptr, int = 0);
    ~wheat_field();

private slots:
    void on_upgrade_clicked();

    void on_seed_clicked();

    void on_Harvesting_clicked();

    void Refresh();


public slots:
    void increamenter_seed();

    void  increamenter_upgrade();

private:

    Ui::wheat_field *ui;
    int id ;
    QTimer* timer1 , *timer2 ;
    QJsonObject info ,_info ;
    QWidget *farm;

};

#endif // WHEAT_FIELD_H
