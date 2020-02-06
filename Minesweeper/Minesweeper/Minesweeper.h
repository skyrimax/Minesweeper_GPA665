#pragma once

#include <QtWidgets/QMainWindow>
#include <QActionGroup>
#include "ui_Minesweeper.h"
#include "Minefield.h"

class Minesweeper : public QMainWindow
{
	Q_OBJECT

public:
	Minesweeper(QWidget *parent = Q_NULLPTR);

private:
	Ui::MinesweeperClass ui;
	Minefield* m_game;
	QActionGroup* difficultyGroup;

	Minefield::DifficultyLevel diff;
	int nbRows;
	int nbCols;
};
