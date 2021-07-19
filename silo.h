#pragma once

#ifndef SILO_H
#define SILO_H

#include <QDialog>
#include <QJsonObject>
#include <QJsonArray>
#include<QTimer>

namespace Ui {class silo;}

class silo : public QDialog
{
    Q_OBJECT

public:
    explicit silo(QWidget *parent = nullptr, int = 0);

    ~silo();



private slots:
    void on_upgrade_clicked();
    void increamenter_upgrade();

    void on_refresh_clicked();

private:

    Ui::silo *ui;
    int id;
    QJsonObject info ,_info ;
    QWidget *farm;
    QTimer *timer;

};

#endif // SILO_H
