#pragma once

#include <QMainWindow>
#include "ui_NewStudent_Form.h"

class NewStudent_Form : public QMainWindow
{
	Q_OBJECT

public:
	NewStudent_Form(QWidget *parent = nullptr);
	~NewStudent_Form();

private:
	Ui::NewStudent_FormClass ui;
};
