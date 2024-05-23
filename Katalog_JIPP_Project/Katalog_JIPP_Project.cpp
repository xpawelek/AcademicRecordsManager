#include "Katalog_JIPP_Project.h"
#include <fstream>
#include <QMessageBox>
#include <iostream>
#include <filesystem>
#include <regex> 


using namespace std;

class InvalidLenght : public exception
{
public:
public:
    virtual const char* InvalidLengthError() const throw() {
        return "Zbyt krotka dlugosc";
    }
};

class Person {
private:
    string firstName;
    string secondName;

public:
    Person(string firstName, string secondName)
    {
        if (firstName.length() <= 2) {
            throw InvalidLenght();
        }
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
        if (firstName.length() <= 2) {
            throw InvalidLenght();
        }
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
        string doesStudy = getIsStillStudying() ? "Studiuje" : "Nie studiuje";
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
    string fileName;
public:
    DataFileReader() {}

    DataFileReader(string fileName) {
        this->fileName = fileName;
    }

    string getFileName() const
    {
        return this->fileName;
    }

    vector<Student> readStudentsData() override {
        students.clear();
        students.shrink_to_fit();

        ifstream file(getFileName());
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
                try {
                    Student student = Student(studentData[1], studentData[2], checkIfStillStudying, studentData[4], studentData[5], field);
                    student.setIndex(stoi(studentData[0]));
                    students.push_back(student);
                }
                catch (InvalidLenght& ex) {
                    cout << ex.InvalidLengthError() << endl;
                }
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
        ifstream file(getFileName());
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
private:
    string fileName;
public:

    DataWriter() {};

    DataWriter(string fileName)
    {
        this->fileName = fileName;
    }

    string getFileName() const
    {
        return this->fileName;
    }

    void saveStudentData(std::vector<Student> students) override {
        ofstream myfile;
        myfile.open(getFileName());

        for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
            myfile << it->getDataToWriteToFile() + "\n";
        }

        myfile.close();
    }

    void saveStudentData(std::vector<Student> students, string newFileName)
    {
        ofstream newFile(newFileName);

        for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
            newFile << it->getDataToWriteToFile() + "\n";
        }

        newFile.close();
    }
};


class DataProcessing {
private:
    std::vector<Student> students;
    DataFileReader dfr;
    DataWriter dw;
    string fileName;
public:

    DataProcessing() {};
    DataProcessing(string fileName)
    {
        this->fileName = fileName;
        this->dfr = DataFileReader(fileName);
        this->dw = DataWriter(fileName);
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
        try {
            Student newStudent = Student(firstName, secondName, isStillStudying, studyLevel, studyMode, fieldOfStudy);
            newStudent.setIndex(index);
            students.push_back(newStudent);
        }
        catch (InvalidLenght& ex) {
            QMessageBox::critical(nullptr, "Error", ex.InvalidLengthError());
        }

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

    void savingStudentDataToFile(string fileName)
    {
        dw.saveStudentData(students, fileName);
    }
};

DataProcessing dataProcess;

std::vector<Student>students;

Katalog_JIPP_Project::Katalog_JIPP_Project(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //to do search for .txt files in directory
    updateComboBox();
    ui.chooseFile_comboBox->setCurrentIndex(0);

    dataProcess = DataProcessing(ui.chooseFile_comboBox->currentText().toStdString());
    students = dataProcess.returnStudentsList();
    
    ui.comboBox_filtrowanie->addItem("Index");
    ui.comboBox_filtrowanie->addItem("Imie");
    ui.comboBox_filtrowanie->addItem("Nazwisko");
    ui.comboBox_filtrowanie->setCurrentIndex(-1);
    ui.lineEdit_newFileName->setVisible(false);

    ui.listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui.listWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

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

void Katalog_JIPP_Project::editStudentButton_Clicked() {
    if (selectedItem != -1) {
        QListWidgetItem* item = ui.listWidget->currentItem();
        QString text = item->text();
        QStringList pieces = text.split("|");

        for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
            if (it->getIndex() == pieces[0].toInt())
            {
                QListWidgetItem* item = ui.listWidget->currentItem();
                QString text = item->text();
                QStringList pieces = text.split("|");
                int index = pieces[0].toInt();

                EditStudent_Form* editForm = new EditStudent_Form(index, it->getFirstName(), it->getSecondName(), it->getIsStillStudying(), it->getCurrentStudyLevel(), it->get_studyMode(), it->getFieldOfStudy(), this);
                connect(editForm, &EditStudent_Form::sendEditedDataBack, this, &Katalog_JIPP_Project::editingStudent);
                editForm->setWindowModality(Qt::ApplicationModal);
                editForm->show();
            }
        }
    }
    else {
        QMessageBox::information(this, "Nie wybrano studenta", "Wybierz studenta!");
    }
}

void Katalog_JIPP_Project::editingStudent(const int& indexReceived, const string& firstNameReceived, const string& secondNameReceived, const bool& isStillStudyingReceived, const string& currentStudyLevelReceived, const string& studyModeReceived, const string& fieldOfStudyReceived) {

    dataProcess.editTheStudent(indexReceived, firstNameReceived, secondNameReceived, isStillStudyingReceived, currentStudyLevelReceived, studyModeReceived, fieldOfStudyReceived);
    ui.listWidget->clear();
    students = dataProcess.returnStudentsList();

    for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
        ui.listWidget->addItem(QString::fromStdString(it->getInfo()));
    }

    ui.filtrowanie_lineEdit->setText("");
}

void Katalog_JIPP_Project::removeStudentButton_Clicked() {
    if (selectedItem != -1) {
        auto reply = QMessageBox::question(this, "Zatwierdzenie", "Czy na pewno chcesz usunac studenta z listy?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            QListWidgetItem* item = ui.listWidget->currentItem();
            QString text = item->text();
            QStringList pieces = text.split("|");

            dataProcess.removeTheStudent(pieces[0].toInt());
            ui.listWidget->clear();
            students = dataProcess.returnStudentsList();

            for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                ui.listWidget->addItem(QString::fromStdString(it->getInfo()));
            }
            QMessageBox::information(this, "", "Usunieto pomyslnie.");
        }
        ui.listWidget->setCurrentRow(-1);
        selectedItem = ui.listWidget->currentRow();
        ui.filtrowanie_lineEdit->setText("");
    }
    else
    {
        QMessageBox::information(this, "Nie wybrano studenta", "Wybierz studenta!");
    }
}

void Katalog_JIPP_Project::chosenStudentDoubleClicked() {
    QListWidgetItem* item = ui.listWidget->currentItem();
    QString text = item->text();
    QStringList pieces = text.split("|");


    for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
        if (it->getIndex() == pieces[0].toInt())
        {
            QString additionalInfo = QString::fromStdString(it->getAdditionalInfo());
            QMessageBox::information(this, "Dodatkowe informacje", additionalInfo);
        }
    }
}

void Katalog_JIPP_Project::rowChanged() {
    selectedItem = ui.listWidget->currentRow();
}

void Katalog_JIPP_Project::filtering_textChanged() {
    if (ui.comboBox_filtrowanie->currentIndex() != -1)
    {
        if (ui.filtrowanie_lineEdit->text() == "") {
            ui.listWidget->clear();
            students = dataProcess.returnStudentsList();

            for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                ui.listWidget->addItem(QString::fromStdString(it->getInfo()));
            }
        }
        else
        {
            ui.listWidget->clear();
            students = dataProcess.returnFilteredData(ui.filtrowanie_lineEdit->text().toStdString(), ui.comboBox_filtrowanie->currentIndex());

            for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                ui.listWidget->addItem(QString::fromStdString(it->getInfo()));
            }
        }
    }
}

void Katalog_JIPP_Project::showContextMenu(const QPoint& pos)
{
    QPoint globalPos = ui.listWidget->mapToGlobal(pos);
    QMenu myMenu;
    myMenu.addAction("View more details", this, SLOT(chosenStudentDoubleClicked()));
    myMenu.addAction("Edit", this, SLOT(editStudentButton_Clicked()));
    myMenu.addAction("Remove", this, SLOT(removeStudentButton_Clicked()));
    myMenu.exec(globalPos);
}

void  Katalog_JIPP_Project::readFromFile_Clicked() {
    dataProcess = DataProcessing(ui.chooseFile_comboBox->currentText().toStdString());
    students = dataProcess.returnStudentsList();

    ui.listWidget->clear();
    students = dataProcess.returnStudentsList();

    for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
        ui.listWidget->addItem(QString::fromStdString(it->getInfo()));
    }

    QMessageBox::information(this, "Sukces", "Wczytano dane");
}

void Katalog_JIPP_Project::writeToFile_Clicked() {
    if (ui.ifWriteToNewFile_checkbox->isChecked())
    {
        //dodaj regexa
        string newFileName = ui.lineEdit_newFileName->text().toStdString() + ".txt";
        regex fileNameRegex(R"(^[\w\s-]+\.txt$)");
        if (std::regex_match(newFileName, fileNameRegex) == false || newFileName.length() <= 0)
        {
            QMessageBox::information(this, "B??d", "Nie mozna utworzyc pliku o takiej nazwie.");
        }
        else
        {
            dataProcess.savingStudentDataToFile(newFileName);
            ui.chooseFile_comboBox->addItem(QString::fromStdString(newFileName));
            QMessageBox::information(this, "Sukces", "Zapisano dane do pliku");
            updateComboBox();
        }
    }
    else {
        auto reply = QMessageBox::question(this, "Zatwierdzenie", "Czy na pewno chcesz nadpisac istniejacy plik?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            dataProcess.savingStudentDataToFile(ui.chooseFile_comboBox->currentText().toStdString());
            QMessageBox::information(this, "Sukces", "Zapisano dane do pliku");
        }       
    }
}

void Katalog_JIPP_Project::showAreaToEnterFileName_Clicked() {
    ui.lineEdit_newFileName->setVisible(false);
    if (ui.ifWriteToNewFile_checkbox->isChecked())
    {
        ui.lineEdit_newFileName->setVisible(true);
    }
}

void Katalog_JIPP_Project::updateComboBox(const std::string& path) {
    std::vector<std::filesystem::directory_entry> entries;

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ".txt") {
            entries.push_back(entry);
        }
    }

    std::sort(entries.begin(), entries.end(),   
        [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b) {
            return std::filesystem::last_write_time(a) > std::filesystem::last_write_time(b);
        }
    );

    ui.chooseFile_comboBox->clear();
    for (const auto& entry : entries) {
        std::string fileName = entry.path().string();
        fileName = fileName.substr(2);
        ui.chooseFile_comboBox->addItem(QString::fromStdString(fileName));
    }
}