#include "CustomGameParamWindow.h"

CustomGameParamWindow::CustomGameParamWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// Adds the radio button to a button group
	ui.methodButtonGroup->setId(ui.nbMinesRadioButton, 0);
	ui.methodButtonGroup->setId(ui.densityRadioButton, 1);
	ui.methodButtonGroup->setId(ui.difficultyRadioButton, 2);

	// Connect their checked state to the enable state of their corresponding input widgets
	connect(ui.nbMinesRadioButton, SIGNAL(toggled(bool)), ui.nbMinesSpinBox, SLOT(setEnabled(bool)));
	connect(ui.densityRadioButton, SIGNAL(toggled(bool)), ui.densitySpinBox, SLOT(setEnabled(bool)));
	connect(ui.difficultyRadioButton, SIGNAL(toggled(bool)), ui.difficultyComboBox, SLOT(setEnabled(bool)));
}

CustomGameParamWindow::~CustomGameParamWindow()
{
}

// Retreive the with asked by the user
int CustomGameParamWindow::width()
{
	return ui.widthSpinBox->value();
}

// Retreive the height asked by the user
int CustomGameParamWindow::height()
{
	return ui.heightSpinBox->value();
}

// Retreive the methode to calculate the number of mine
int CustomGameParamWindow::qtyMinesMethod()
{
	return ui.methodButtonGroup->checkedId();
}

// Retreive the number of mine asked by the user
int CustomGameParamWindow::nbMines()
{
	return ui.nbMinesSpinBox->value();
}

// Retreive the density of mine asked by the user
double CustomGameParamWindow::densityMines()
{
	return ui.densitySpinBox->value()/100.0;
}

// Retreive the difficulty asked by the user
Minefield::DifficultyLevel CustomGameParamWindow::difficulty()
{
	switch (ui.difficultyComboBox->currentIndex())
	{
	case 0:
		return Minefield::DifficultyLevel::SuperEasy;
		break;
	case 1:
		return Minefield::DifficultyLevel::Easy;
		break;
	case 2:
		return Minefield::DifficultyLevel::Medium;
		break;
	case 3:
		return Minefield::DifficultyLevel::Hard;
		break;
	case 4:
		return Minefield::DifficultyLevel::SuperHard;
		break;
	default:
		break;
	}
}
