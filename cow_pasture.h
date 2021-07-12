#pragma once

#ifndef COW_PASTURE_H
#define COW_PASTURE_H

#include <QDialog>

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

private:

    Ui::cow_pasture *ui;

    int id ;

};

#endif // COW_PASTURE_H
