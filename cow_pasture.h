#pragma once

#ifndef COW_PASTURE_H
#define COW_PASTURE_H

#include <QDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>


namespace Ui {class cow_pasture;}

class cow_pasture : public QDialog
{
    Q_OBJECT

public:
    explicit cow_pasture(QWidget *parent = nullptr , int = 0);



    ~cow_pasture();


private slots:
    void on_upgrade_clicked();

    void on_feed_clicked();

    void on_collect_milk_clicked();

    void increamenter_upgrade();

    void increamenter_collect();

    void on_build_clicked();

private:

    Ui::cow_pasture *ui;

    int id ;
    QTimer *timer1  , *timer2;
    QJsonObject info ,_info ;
    QWidget *farm;

};

#endif // COW_PASTURE_H
