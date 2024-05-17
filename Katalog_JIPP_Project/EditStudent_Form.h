#pragma once

#include <QMainWindow>
#include "ui_EditStudent_Form.h"

class EditStudent_Form : public QMainWindow
{
	Q_OBJECT

public:
	EditStudent_Form(QWidget *parent = nullptr);
	~EditStudent_Form();

private:
	Ui::EditStudent_FormClass ui;
};
