#include "Minesweeper.h"

Minesweeper::Minesweeper(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	difficultyGroup = new QActionGroup(this);
	difficultyGroup->addAction(ui.actionSuperEasy);
	difficultyGroup->addAction(ui.actionEasy);
	difficultyGroup->addAction(ui.actionMedium);
	difficultyGroup->addAction(ui.actionHard);
	difficultyGroup->addAction(ui.actionSuperHard);

	diff = Minefield::DifficultyLevel::TresFacile;

	//m_game = new Minefield(nbRows, nbCols, diff);

	//ui.minefieldView->setScene(m_game);
}
