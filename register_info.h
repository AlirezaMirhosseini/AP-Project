#pragma once

#ifndef REGISTER_INFO_H
#define REGISTER_INFO_H

#include <QDialog>

namespace Ui {class register_info;}

class register_info : public QDialog
{
    Q_OBJECT

public:
    explicit register_info(QWidget *parent = nullptr);

    ~register_info();



private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:

    Ui::register_info *ui;


};

#endif // REGISTER_INFO_H
