#pragma once

#include <QMainWindow>
#include "ui_EditStudent_Form.h"

class EditStudent_Form : public QMainWindow
{
	Q_OBJECT

public:
	EditStudent_Form(QWidget *parent = nullptr);
	~EditStudent_Form();

signals:
	void sendEditedDataBack(const int& index, const string& firstNameReceived, const string& secondNameReceived, const bool& isStillStudyingReceived, const string& currentStudyLevelReceived, const string& studyModeReceived, const string& fieldOfStudyReceived);

private slots:
	void editButton_Clicked();

private:
	Ui::EditStudent_FormClass ui;
};
