#include "CustomGameParamWindow.h"

CustomGameParamWindow::CustomGameParamWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.methodButtonGroup->setId(ui.nbMinesRadioButton, 0);
	ui.methodButtonGroup->setId(ui.densityRadioButton, 1);
	ui.methodButtonGroup->setId(ui.difficultyRadioButton, 2);

	connect(ui.nbMinesRadioButton, SIGNAL(toggled(bool)), ui.nbMinesSpinBox, SLOT(setEnabled(bool)));
	connect(ui.densityRadioButton, SIGNAL(toggled(bool)), ui.densitySpinBox, SLOT(setEnabled(bool)));
	connect(ui.difficultyRadioButton, SIGNAL(toggled(bool)), ui.difficultyComboBox, SLOT(setEnabled(bool)));
}

CustomGameParamWindow::~CustomGameParamWindow()
{
}

int CustomGameParamWindow::width()
{
	return ui.widthSpinBox->value();
}

int CustomGameParamWindow::height()
{
	return ui.heightSpinBox->value();
}

int CustomGameParamWindow::qtyMinesMethod()
{
	return ui.methodButtonGroup->checkedId();
}

int CustomGameParamWindow::nbMines()
{
	return ui.nbMinesSpinBox->value();
}

double CustomGameParamWindow::densityMines()
{
	return ui.densitySpinBox->value()/100.0;
}

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
