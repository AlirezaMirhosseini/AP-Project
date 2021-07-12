#pragma once

#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "register_info.h"
#include "farm.h"

QT_BEGIN_NAMESPACE
namespace Ui { class game; }
QT_END_NAMESPACE

class game : public QWidget
{
    Q_OBJECT

public:
    game(QWidget *parent = nullptr);
    ~game();





private:

    Ui::game *ui;


};
#endif // GAME_H
