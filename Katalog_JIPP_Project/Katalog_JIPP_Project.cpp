#include "Katalog_JIPP_Project.h"
#include <fstream>
#include <QMessageBox>
#include <iostream>
using namespace std;

class Person {
private:
    string firstName;
    string secondName;

public:
    Person(string firstName, string secondName)
    {
        this->firstName = firstName;
        this->secondName = secondName;
    }

    virtual string getFirstName() const {
        return firstName;
    }

    virtual string getSecondName() const {
        return secondName;
    }

    virtual void setFirstName(const string& firstName)
    {
        this->firstName = firstName;
    }

    virtual void setSecondName(const string& secondName)
    {
        this->secondName = secondName;
    }
};

class Student : public Person {
private:
    int index;
    bool isStillStudying;
    string currentStudyLevel;
    string studyMode;
    string fieldOfStudy;

public:
    Student(string firstName, string secondName, bool isStillStyding, string currentStudyLevel, string studyMode, string fieldOfStudy) :Person(firstName, secondName)
    {
        this->index = -1;
        this->isStillStudying = isStillStyding;
        this->currentStudyLevel = currentStudyLevel;
        this->studyMode = studyMode;
        this->fieldOfStudy = fieldOfStudy;
    }

    void setIndex(const int& index) {
        this->index = index;
    }//xx

    int getIndex() const {
        return index;
    }

    bool getIsStillStudying() const
    {
        return isStillStudying;
    }

    void setIsStillStudying(bool isStillStudying)
    {
        this->isStillStudying = isStillStudying;
    }

    string getCurrentStudyLevel() const
    {
        return currentStudyLevel;
    }

    void setCurrentStudyLevel(const string& currentStudyLevel)
    {
        this->currentStudyLevel = currentStudyLevel;
    }

    string get_studyMode() const
    {
        return studyMode;
    }

    void setStudyMode(const string& studyMode)
    {
        this->studyMode = studyMode;
    }


    string getFieldOfStudy() const
    {
        return fieldOfStudy;
    }

    void setFieldOfStudy(const string& fieldOfStudy)
    {
        this->fieldOfStudy = fieldOfStudy;
    }

    string getDataToWriteToFile() {
        string str_IsStillStudying = getIsStillStudying() ? "True" : "False";
        return std::to_string(getIndex()) + ";" + getFirstName() + ";" + getSecondName() + ";" + str_IsStillStudying + ";" + getCurrentStudyLevel() + ";" + get_studyMode() + ";" + getFieldOfStudy();
    }

    string getInfo() {
        return to_string(getIndex()) + "|\tImie:\t" + getFirstName() + ",\tNazwisko:\t" + getSecondName();
    }

    string getAdditionalInfo() {
        string doesStudy = isStillStudying ? "Studiuje" : "Nie studiuje";
        return "Status -> " + doesStudy + "\nStopien -> " + currentStudyLevel + "\nTryb -> " + studyMode + "\nKierunek -> " + fieldOfStudy;
    }
};


class IDataReader {
public:
    virtual vector<Student> readStudentsData() = 0;
};

class DataFileReader : public IDataReader {
private:
    vector<Student> students;

public:

    vector<Student> readStudentsData() override {
        students.clear();
        students.shrink_to_fit();

        ifstream file("students_list.txt");
        string line;

        if (file.is_open()) {
            while (getline(file, line))
            {
                string delimeter = ";";
                vector<string> studentData;
                auto start = 0;
                auto end = line.find(delimeter);
                while (end != std::string::npos)
                {
                    //czytaj dane z pliku -> stworz obiekt osoby i do konstrukota dodaj dane z pliku -> dodaj do listy
                    string cell = line.substr(start, end - start);
                    studentData.push_back(cell);
                    start = end + delimeter.length();
                    end = line.find(delimeter, start);
                    // cout << cell << 'n';
                }
                string field = line.substr(start, end);

                bool checkIfStillStudying = (studentData[3] == "True") ? true : false;
                //Student p1(personData[0], personData[1], checkIfStillStudying, personData[3], personData[4], kierunek);
                Student student = Student(studentData[1], studentData[2], checkIfStillStudying, studentData[4], studentData[5], field);
                student.setIndex(stoi(studentData[0]));
                students.push_back(student);
                // cout << line.substr(start, end) << "\n";
            }
            return students;
        }
        else
        {
            //error opening file
        }
        file.close();
    }

    bool checkIfFileEmpty()
    {
        ifstream file("students_list.txt");
        file.seekg(0, ios::end);
        if (file.tellg() == 0) {
            return true;
        }
        else
        {
            return false;
        }
        file.close();
    }
};

class IDataWriter {
public:
    virtual void saveStudentData(std::vector<Student> students) = 0;
};

class DataWriter : IDataWriter {
public:
    void saveStudentData(std::vector<Student> students) override {
        ofstream myfile;
        myfile.open("students_list.txt");

        for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
            myfile << it->getDataToWriteToFile() + "\n";
        }

        myfile.close();
    }
};


class DataProcessing {
private:
    std::vector<Student> students;
    DataFileReader dfr;
    DataWriter dw;

public:

    DataProcessing()
    {
        students = dfr.readStudentsData();
    }

    std::vector<Student> returnStudentsList() {
        return students;
    }

    void refreshTheList() {
        dw.saveStudentData(students);
        students.clear();
        students.shrink_to_fit();
        students = dfr.readStudentsData();
    }

    void removeTheStudent(int index)
    {
        for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
            if (it->getIndex() == index)
            {
                students.erase(it);
                dw.saveStudentData(students);
                refreshTheList();
                break;
            }
        }

    }

    void addTheStudent(string firstName, string secondName, bool isStillStudying, string studyLevel, string studyMode, string fieldOfStudy) {
        int index;
        if (dfr.checkIfFileEmpty())
        {
            index = 1;
        }
        else {
            index = students.back().getIndex() + 1;
        }

        Student newStudent = Student(firstName, secondName, isStillStudying, studyLevel, studyMode, fieldOfStudy);
        newStudent.setIndex(index);
        students.push_back(newStudent);
        refreshTheList();
    };

    void editTheStudent(int index, string firstName, string secondName, bool isStillStudying, string studyLevel, string studyMode, string fieldOfStudy)
    {
        for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
            if (it->getIndex() == index)
            {
                it->setFirstName(firstName);
                it->setSecondName(secondName);
                it->setIsStillStudying(isStillStudying);
                it->setCurrentStudyLevel(studyLevel);
                it->setStudyMode(studyMode);
                it->setFieldOfStudy(fieldOfStudy);
                break;
            }
        }
        refreshTheList();

    }

    std::vector<Student> returnFilteredData(string text, int option) {
        std::vector<Student> temporary_students;

        switch (option)
        {
        case 0:

            for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                string index = std::to_string(it->getIndex());
                std::transform(index.begin(), index.end(), index.begin(), ::tolower);
                std::transform(text.begin(), text.end(), text.begin(), ::tolower);

                if (index.find(text) != std::string::npos) {
                    temporary_students.push_back(*it);
                }
            }
            break;

        case 1:
            for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                string firstName = it->getFirstName();
                std::transform(firstName.begin(), firstName.end(), firstName.begin(), ::tolower);
                std::transform(text.begin(), text.end(), text.begin(), ::tolower);

                if (firstName.find(text) != std::string::npos) {
                    temporary_students.push_back(*it);
                }
            }

            break;

        case 2:
            for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                string secondName = it->getSecondName();
                std::transform(secondName.begin(), secondName.end(), secondName.begin(), ::tolower);
                std::transform(text.begin(), text.end(), text.begin(), ::tolower);

                if (secondName.find(text) != std::string::npos) {
                    temporary_students.push_back(*it);
                }
            }
            break;
        }

        return temporary_students;
    }
};

DataProcessing dataProcess;

std::vector<Student>students = dataProcess.returnStudentsList();

Katalog_JIPP_Project::Katalog_JIPP_Project(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    

    for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
        ui.listWidget->addItem(QString::fromStdString(it->getInfo()));
    }
}

Katalog_JIPP_Project::~Katalog_JIPP_Project()
{}

void Katalog_JIPP_Project::addStudentButton_Clicked() {
    NewStudent_Form* addingForm = new NewStudent_Form(this);
    connect(addingForm, &NewStudent_Form::sendData, this, &Katalog_JIPP_Project::addingNewStudent);
    addingForm->setWindowModality(Qt::ApplicationModal);
    addingForm->show();
}

void Katalog_JIPP_Project::addingNewStudent(const string& newFirstName, const string& newSecondName, const bool& newIsStillStudying, const string& newCurrentStudyLevel, const string& newStudyMode, const string& newFieldOfStudy) {
    dataProcess.addTheStudent(newFirstName, newSecondName, newIsStillStudying, newCurrentStudyLevel, newStudyMode, newFieldOfStudy);

    ui.listWidget->clear();
    students = dataProcess.returnStudentsList();

    for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
        ui.listWidget->addItem(QString::fromStdString(it->getInfo()));
    }
    ui.filtrowanie_lineEdit->setText("");
}
