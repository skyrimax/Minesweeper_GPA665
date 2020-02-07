#include "Minesweeper.h"

Minesweeper::Minesweeper(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//Grouping all diffcutly related menu actions to make them mutially exclisive
	difficultyGroup = new QActionGroup(this);
	difficultyGroup->addAction(ui.actionSuperEasy);
	difficultyGroup->addAction(ui.actionEasy);
	difficultyGroup->addAction(ui.actionMedium);
	difficultyGroup->addAction(ui.actionHard);
	difficultyGroup->addAction(ui.actionSuperHard);
	difficultyGroup->addAction(ui.actionCustom);

	//Connecting all "New Game" related menu actions to their respective new game generating fucntion
	connect(ui.newGameButton, SIGNAL(clicked()), this, SLOT(newGame()));
	connect(ui.actionNewGame, SIGNAL(triggered()), this, SLOT(newGame()));
	connect(ui.actionSuperEasy, SIGNAL(triggered()), this, SLOT(superEasyGame()));
	connect(ui.actionEasy, SIGNAL(triggered()), this, SLOT(easyGame()));
	connect(ui.actionMedium, SIGNAL(triggered()), this, SLOT(mediumGame()));
	connect(ui.actionHard, SIGNAL(triggered()), this, SLOT(hardGame()));
	connect(ui.actionSuperHard, SIGNAL(triggered()), this, SLOT(superHardGame()));
	connect(ui.actionCustom, SIGNAL(triggered()), this, SLOT(customGame()));

	//Connecting the exit menu action to quitting the program
	connect(ui.actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));

	m_game = nullptr;
	superEasyGame();
}

void Minesweeper::newGame()
{
	if (m_game != nullptr) {
		delete m_game;
	}

	m_game = new Minefield(nbRows, nbCols, diff);

	ui.minefieldView->setScene(m_game);
}

void Minesweeper::superEasyGame()
{
	nbRows = 9;
	nbCols = 9;
	diff = Minefield::DifficultyLevel::SuperEasy;

	newGame();
}

void Minesweeper::easyGame()
{
	nbRows = 9;
	nbCols = 9;
	diff = Minefield::DifficultyLevel::Easy;

	objectName();
}

void Minesweeper::mediumGame()
{
	nbRows = 16;
	nbCols = 16;
	diff = Minefield::DifficultyLevel::Medium;

	newGame();
}

void Minesweeper::hardGame()
{
	nbRows = 16;
	nbCols = 30;
	diff = Minefield::DifficultyLevel::Hard;

	newGame();
}

void Minesweeper::superHardGame()
{
	nbRows = 16;
	nbCols = 30;
	diff = Minefield::DifficultyLevel::SuperHard;

	newGame();
}

void Minesweeper::customGame()
{

}
