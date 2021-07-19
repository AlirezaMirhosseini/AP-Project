#pragma once

#ifndef SHEEP_PASTURE_H
#define SHEEP_PASTURE_H

#include <QDialog>
#include <QTimer>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {class sheep_pasture;}

class sheep_pasture : public QDialog
{
    Q_OBJECT

public:

    explicit sheep_pasture(QWidget *parent = nullptr , int = 0);

    ~sheep_pasture();

private slots:
    void on_feed_clicked();

    void on_upgrade_clicked();

    void on_Fleece_Shave_clicked();

    void increamenter_upgrade();

    void increamenter_collect();

    void on_build_clicked();

    void Refresh();

    void on_refresh_clicked();

private:
    int id;

    Ui::sheep_pasture *ui;

    QTimer *timer1 , *timer2;
    QJsonObject info ,_info ;
    QWidget *farm;
};

#endif // SHEEP_PASTURE_H
