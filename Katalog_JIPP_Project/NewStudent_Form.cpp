#include "NewStudent_Form.h"
#include <QMessageBox>
#include <regex> 
#include "ownNamespace.h"

NewStudent_Form::NewStudent_Form(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.comboBox_stopnie->addItem("Licencjackie");
	ui.comboBox_stopnie->addItem("Inzynierskie");
	ui.comboBox_stopnie->addItem("Magisterskie");
	ui.comboBox_stopnie->addItem("Doktoranckie");

}

NewStudent_Form::~NewStudent_Form()
{}



void NewStudent_Form::sendStudentDataBack() {
	string firstName = ownNamespace::capitalizeFirstLetter(ui.lineEdit_firstName->text().toStdString());
	string secondName = ownNamespace::capitalizeFirstLetter(ui.lineEdit_secondName->text().toStdString());
	string fieldOfStudy = ownNamespace::capitalizeFirstLetter(ui.lineEdit_Field->text().toStdString());

	vector <string> errors = {};
	regex myStringsRegex("[a-zA-Z ]+");
	if (std::regex_match(firstName, myStringsRegex) == false || firstName.length() < 3)
	{
		errors.push_back("Imie zawiera niepoprawne dane.");
	}

	if (std::regex_match(secondName, myStringsRegex) == false || firstName.length() < 3)
	{
		errors.push_back("Nazwisko zawiera niepoprawne dane.");
	}

	if (std::regex_match(fieldOfStudy, myStringsRegex) == false)
	{
		errors.push_back("Kierunek studi\u00F3w zawiera niepoprawne dane.");
	}


	if (ui.comboBox_stopnie->currentIndex() == -1)
	{
		errors.push_back("Stopie\u0144 studi\u00F3w nie zosta\u0142 wybrany.");
	}

	if (ui.rd_niestacjonarnie->isChecked() == false && ui.rd_stacjonarnie->isChecked() == false) {
		errors.push_back("Nie wybrano trybu studiowania.");
	}

	if (errors.size() == 0)
	{
		bool ifStillStudy = ui.checkBox_IfStillStudy->isChecked() ? true : false;
		string studyMode = ui.rd_stacjonarnie->isChecked() ? "Stacjonarnie" : "Niestacjonarnie";
		emit sendData(firstName, secondName, ifStillStudy, ui.comboBox_stopnie->currentText().toStdString(), studyMode, fieldOfStudy);
		QMessageBox::information(this, "Sukces", "Nowy student zosta\u0142 dodany");
		this->close();
	}
	else {
		string errorMessage;
		for (auto it = begin(errors); it != end(errors); ++it) {
			errorMessage += *it + " \n";
		}

		QMessageBox::information(this, "Popraw wprowadzone dane.", QString::fromStdString(errorMessage));
	}
}