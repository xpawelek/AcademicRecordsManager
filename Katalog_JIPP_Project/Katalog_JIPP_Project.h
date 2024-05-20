#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Katalog_JIPP_Project.h"
#include "NewStudent_Form.h"
#include "EditStudent_Form.h"

class Katalog_JIPP_Project : public QMainWindow
{
    Q_OBJECT

public:
    Katalog_JIPP_Project(QWidget *parent = nullptr);
    ~Katalog_JIPP_Project();

private slots:
    void addingNewStudent(const string& new_firstName, const string& new_secondName, const bool& new_isStillStudying, const string& new_currentStudyLevel, const string& new_studyMode, const string& new_fieldOfStudy);
    void addStudentButton_Clicked();
    void editStudentButton_Clicked();
    void editingStudent(const int& index, const string& new_firstName, const string& new_secondName, const bool& new_isStillStudying, const string& new_currentStudyLevel, const string& new_studyMode, const string& new_fieldOfStudy);
    void removeStudentButton_Clicked();
    void chosenStudentDoubleClicked();
    void rowChanged();
    void filtering_textChanged();
    void showContextMenu(const QPoint& pos);
    void readFromFile_Clicked();
    void writeToFile_Clicked();

private:
    Ui::Katalog_JIPP_ProjectClass ui;
    int selectedItem = -1;
};
