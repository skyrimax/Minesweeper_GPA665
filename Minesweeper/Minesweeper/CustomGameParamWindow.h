#pragma once

#include <QDialog>
#include "ui_CustomGameParamWindow.h"
#include "Minefield.h"

class CustomGameParamWindow : public QDialog
{
	Q_OBJECT

public:
	CustomGameParamWindow(QWidget *parent = Q_NULLPTR);
	~CustomGameParamWindow();

	int width();
	int height();
	int qtyMinesMethod();
	int nbMines();
	double densityMines();
	Minefield::DifficultyLevel difficulty();
	bool canceled();

private:
	Ui::CustomGameParamWindow ui;

	bool m_canceled;
};
