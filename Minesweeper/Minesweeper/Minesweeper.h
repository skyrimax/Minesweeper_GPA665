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

public slots:
	void newGame();
	void superEasyGame();
	void easyGame();
	void mediumGame();
	void hardGame();
	void superHardGame();
	void customGame();

private:
	Ui::MinesweeperClass ui;
	Minefield* m_game;
	QActionGroup* difficultyGroup;

	Minefield::DifficultyLevel diff;
	int nbRows;
	int nbCols;
};
