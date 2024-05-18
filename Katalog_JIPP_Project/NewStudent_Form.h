#pragma once

#include <QMainWindow>
#include "ui_NewStudent_Form.h"
using namespace std;

class NewStudent_Form : public QMainWindow
{
	Q_OBJECT

public:
	NewStudent_Form(QWidget* parent = nullptr);
	~NewStudent_Form();

signals:
	void sendData(const string& newFirstName, const string& newSecondName, const bool& newIsStillStudying, const string& newCurrentStudyLevel, const string& newStudyMode, const string& newFieldOfStudy);

private slots:
	void sendStudentDataBack();

private:
	Ui::NewStudent_FormClass ui;
};
