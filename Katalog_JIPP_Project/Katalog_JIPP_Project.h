#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Katalog_JIPP_Project.h"

class Katalog_JIPP_Project : public QMainWindow
{
    Q_OBJECT

public:
    Katalog_JIPP_Project(QWidget *parent = nullptr);
    ~Katalog_JIPP_Project();

private:
    Ui::Katalog_JIPP_ProjectClass ui;
};
