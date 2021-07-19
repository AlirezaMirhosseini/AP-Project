#pragma once

#ifndef BARN_H
#define BARN_H

#include <QDialog>
#include <QVector>
#include <deque>
#include <QJsonObject>
#include <QJsonArray>
#include<QTimer>

using namespace std;

namespace Ui {class barn;}

class barn : public QDialog
{
    Q_OBJECT

public:

    explicit barn(QWidget *parent = nullptr, int = 0);

    ~barn();

private slots:
    void on_upgrade_clicked();
    void increamenter_upgrade();
    void on_refresh_clicked();

private:

    Ui::barn *ui;
    int id;
    QJsonObject info ,_info ;
    QTimer *timer;
    QWidget *farm;

};

#endif // BARN_H
