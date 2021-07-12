#pragma once
    
#ifndef ALFALFA_FIELD_H
#define ALFALFA_FIELD_H
#include <QDialog>
#include<QTimer>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {class alfalfa_field;}

class alfalfa_field : public QDialog
{
    Q_OBJECT

public:
    explicit alfalfa_field(QWidget *parent = nullptr, int = 0);
    ~alfalfa_field();


private slots:
    void on_btn_upgrade_clicked();

    void on_btn_seed_clicked();

    void on_btn_harvesting_clicked();

    void on_btn_plow_clicked();
public slots:
    void increamenter_upgrade();
    void increamenter_plow();

private:

    Ui::alfalfa_field *ui;
    int id;
    QTimer* timer1 , *timer2 ;
    QJsonObject info ,_info ;

};

#endif // ALFALFA_FIELD_H
