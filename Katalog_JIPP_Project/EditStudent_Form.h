#pragma once

#include <QMainWindow>
#include "ui_EditStudent_Form.h"
using namespace std;

class EditStudent_Form : public QMainWindow
{
	Q_OBJECT
		int passedIndex;
public:
	EditStudent_Form(int index, string passedFirstName, string passedSecondName, bool passedIsStillStudying, string passedStudyLevel, string passedStudyMode, string passedFieldOfStudy, QWidget* parent = nullptr);
	~EditStudent_Form();

signals:
	void sendEditedDataBack(const int& index, const string& firstNameReceived, const string& secondNameReceived, const bool& isStillStudyingReceived, const string& currentStudyLevelReceived, const string& studyModeReceived, const string& fieldOfStudyReceived);

private slots:
	void editButton_Clicked();

private:
	Ui::EditStudent_FormClass ui;
};
