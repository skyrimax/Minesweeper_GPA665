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

	//Connect the timer to the slot incrementing the time
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(incTime()));
	connect(ui.lcdTime, SIGNAL(overflow()), &m_timer, SLOT(stop()));

	m_game = nullptr;
	superEasyGame();
}

void Minesweeper::newGame()
{
	m_timer.stop();
	ui.lcdTime->display(0);

	if (m_game != nullptr) {
		delete m_game;
	}

	QPixmap image;
	image.load(":/Minesweeper/sprites/smile.png");
	QIcon icon(image);
	ui.newGameButton->setIcon(icon);
	ui.newGameButton->setIconSize(image.rect().size());

	m_game = new Minefield(nbRows, nbCols, diff);
	ui.minefieldView->setScene(m_game);

	connect(m_game, SIGNAL(victory()), this, SLOT(victory()));
	connect(m_game, SIGNAL(loss()), this, SLOT(loss()));
	connect(m_game, SIGNAL(nbMinesChanged(int)), ui.lcdNbBombs, SLOT(display(int)));

	//Connecting the Mark(?) menu action to the function enabling and disabling the use of ?
	connect(ui.actionMarks, SIGNAL(triggered(bool)), m_game, SLOT(setQuestionMarkAvailability(bool)));

	//Connect the pressing of the first tile to the start of the game
	connect(m_game, SIGNAL(clicked()), this, SLOT(startGame()));

	ui.lcdNbBombs->display(m_game->shownNbMines());
	minimalSize();
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

	newGame();
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
	nbRows = 30;
	nbCols = 16;
	diff = Minefield::DifficultyLevel::Hard;

	newGame();
}

void Minesweeper::superHardGame()
{
	nbRows = 30;
	nbCols = 16;
	diff = Minefield::DifficultyLevel::SuperHard;

	newGame();
}

void Minesweeper::customGame()
{
	m_timer.stop();
	ui.lcdTime->display(0);

	CustomGameParamWindow* w = new CustomGameParamWindow(this);

	if (w->exec()) {
		nbCols = w->height();
		nbRows = w->width();

		if (m_game != nullptr) {
			delete m_game;
		}

		QPixmap image;
		image.load(":/Minesweeper/sprites/smile.png");
		QIcon icon(image);
		ui.newGameButton->setIcon(icon);
		ui.newGameButton->setIconSize(image.rect().size());

		switch (w->qtyMinesMethod())
		{
		case 0:
			m_game = new Minefield(nbRows, nbCols, w->nbMines());
			break;
		case 1:
			m_game = new Minefield(nbRows, nbCols, w->densityMines());
			break;
		case 2:
			m_game = new Minefield(nbRows, nbCols, w->difficulty());
			break;
		default:
			break;
		}

		ui.minefieldView->setScene(m_game);

		connect(m_game, SIGNAL(victory()), this, SLOT(victory()));
		connect(m_game, SIGNAL(loss()), this, SLOT(loss()));

		//Connecting the Mark(?) menu action to the function enabling and disabling the use of ?
		connect(ui.actionMarks, SIGNAL(triggered(bool)), m_game, SLOT(setQuestionMarkAvailability(bool)));

		//Connect the pressing of the first tile to the start of the game
		connect(m_game, SIGNAL(clicked()), this, SLOT(startGame()));

		ui.lcdNbBombs->display(m_game->shownNbMines());
		minimalSize();
	}
	else
		m_timer.start();

	delete w;
}

void Minesweeper::victory()
{
	m_timer.stop();
	QPixmap image;
	image.load(":/Minesweeper/sprites/victory.png");
	QIcon icon(image);
	ui.newGameButton->setIcon(icon);
	ui.newGameButton->setIconSize(image.rect().size());
}

void Minesweeper::loss()
{

	m_timer.stop();
	QPixmap image;
	image.load(":/Minesweeper/sprites/dead.png");
	QIcon icon(image);
	ui.newGameButton->setIcon(icon);
	ui.newGameButton->setIconSize(image.rect().size());
}

void Minesweeper::incTime()
{
	ui.lcdTime->display(ui.lcdTime->intValue() + 1);
}

void Minesweeper::startGame()
{
	disconnect(m_game, SIGNAL(clicked()), this, SLOT(startGame()));
	m_timer.start(1000);
}

void Minesweeper::minimalSize()
{
	//Widgets in main frame
	ui.minefieldView->setFixedSize(16 * nbRows + 4, 16 * nbCols + 4);
	ui.minefieldView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.minefieldView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.frame_2->adjustSize();

	ui.centralWidget->adjustSize();
	this->adjustSize();
}
