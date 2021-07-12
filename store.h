#ifndef STORE_H
#define STORE_H
#include "farm.h"
#include <QDialog>

namespace Ui {
class store;
}

class store : public QDialog
{
    Q_OBJECT
    int id;

public:
    explicit store(QWidget *parent = nullptr, int i=0);
    ~store();



private slots:
    void on_sell_pushButton_clicked();

    void on_buy_pushButton_clicked();

private:
    Ui::store *ui;
    QJsonObject info ,_info ;
};

#endif // STORE_H
