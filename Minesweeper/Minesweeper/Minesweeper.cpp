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

	// Default game difficulty at start is super easy
	superEasyGame();
}

void Minesweeper::newGame()
{
	// Stop timer if in case it was still rinning from a previous game
	m_timer.stop();
	ui.lcdTime->display(0);

	// Prefenting memory leaks
	if (m_game != nullptr) {
		delete m_game;
	}

	// Reload game appearance to default state
	QPixmap image;
	image.load(":/Minesweeper/sprites/smile.png");
	QIcon icon(image);
	ui.newGameButton->setIcon(icon);
	ui.newGameButton->setIconSize(image.rect().size());

	// Creating the game with parameters in memory
	m_game = new Minefield(nbRows, nbCols, diff);
	ui.minefieldView->setScene(m_game);

	// Connecting signals from game ending to corresponding actions in the ui
	connect(m_game, SIGNAL(victory()), this, SLOT(victory()));
	connect(m_game, SIGNAL(loss()), this, SLOT(loss()));

	// Connecting the variation of mines to the indication in the UI
	connect(m_game, SIGNAL(nbMinesChanged(int)), ui.lcdNbBombs, SLOT(display(int)));

	//Connecting the Mark(?) menu action to the function enabling and disabling the use of ?
	connect(ui.actionMarks, SIGNAL(triggered(bool)), m_game, SLOT(setQuestionMarkAvailability(bool)));

	//Connect the pressing of the first tile to the start of the game
	connect(m_game, SIGNAL(clicked()), this, SLOT(startGame()));

	// Display the number of mines in the minefield
	ui.lcdNbBombs->display(m_game->shownNbMines());

	// Shrink window to minimal size
	minimalSize();
}

void Minesweeper::superEasyGame()
{
	// Sets parameters for super easy difficulty
	nbRows = 9;
	nbCols = 9;
	diff = Minefield::DifficultyLevel::SuperEasy;

	// Launch the new game
	newGame();
}

void Minesweeper::easyGame()
{
	// Sets parameters for easy difficulty
	nbRows = 9;
	nbCols = 9;
	diff = Minefield::DifficultyLevel::Easy;

	// Launch the new game
	newGame();
}

void Minesweeper::mediumGame()
{
	// Sets parameters for medium difficulty
	nbRows = 16;
	nbCols = 16;
	diff = Minefield::DifficultyLevel::Medium;

	// Launch the new game
	newGame();
}

void Minesweeper::hardGame()
{
	// Sets parameters for hard difficulty
	nbRows = 30;
	nbCols = 16;
	diff = Minefield::DifficultyLevel::Hard;

	// Launch the new game
	newGame();
}

void Minesweeper::superHardGame()
{
	// Sets parameters for super hard difficulty
	nbRows = 30;
	nbCols = 16;
	diff = Minefield::DifficultyLevel::SuperHard;

	// Launch the new game
	newGame();
}

void Minesweeper::customGame()
{
	// Stop timer if in case it was still rinning from a previous game
	m_timer.stop();
	ui.lcdTime->display(0);

	// Instantiate a dialog box for custom game creation
	CustomGameParamWindow* w = new CustomGameParamWindow(this);

	// If the user does not cancel the game
	if (w->exec()) {
		// Retrieve size paremters
		nbCols = w->height();
		nbRows = w->width();

		// Prefenting memory leaks
		if (m_game != nullptr) {
			delete m_game;
		}

		// Reload game appearance to default state
		QPixmap image;
		image.load(":/Minesweeper/sprites/smile.png");
		QIcon icon(image);
		ui.newGameButton->setIcon(icon);
		ui.newGameButton->setIconSize(image.rect().size());

		// Depending on the method the user requests for the quantity of mines
		switch (w->qtyMinesMethod())
		{
		case 0:
			// Create the minefield with a specified number of mines
			m_game = new Minefield(nbRows, nbCols, w->nbMines());
			break;
		case 1:
			// Create the minefield with a specified density of mines
			m_game = new Minefield(nbRows, nbCols, w->densityMines());
			break;
		case 2:
			//create the minefield with a specified difficulty
			m_game = new Minefield(nbRows, nbCols, w->difficulty());
			break;
		default:
			break;
		}

		// Set the minefield to the grpahicla viewl
		ui.minefieldView->setScene(m_game);

		connect(m_game, SIGNAL(victory()), this, SLOT(victory()));
		connect(m_game, SIGNAL(loss()), this, SLOT(loss()));

		//Connecting the Mark(?) menu action to the function enabling and disabling the use of ?
		connect(ui.actionMarks, SIGNAL(triggered(bool)), m_game, SLOT(setQuestionMarkAvailability(bool)));

		//Connect the pressing of the first tile to the start of the game
		connect(m_game, SIGNAL(clicked()), this, SLOT(startGame()));

		// Display the number of mines in the minefield
		ui.lcdNbBombs->display(m_game->shownNbMines());

		// Shrink window to minimal size
		minimalSize();
	}
	else {
		// Restarts timer if the user cancels the creation of a niew game
		m_timer.start();
	}

	// Suppression du dialogue
	delete w;
}

// Sequence for victory
void Minesweeper::victory()
{
	// Stop timer
	m_timer.stop();

	// Change the smiley face on the new game button
	QPixmap image;
	image.load(":/Minesweeper/sprites/victory.png");
	QIcon icon(image);
	ui.newGameButton->setIcon(icon);
	ui.newGameButton->setIconSize(image.rect().size());
}

void Minesweeper::loss()
{
	// Stop timer
	m_timer.stop();

	// Change the smiley face on the new game button
	QPixmap image;
	image.load(":/Minesweeper/sprites/dead.png");
	QIcon icon(image);
	ui.newGameButton->setIcon(icon);
	ui.newGameButton->setIconSize(image.rect().size());
}

// Increments the timer display every second
void Minesweeper::incTime()
{
	ui.lcdTime->display(ui.lcdTime->intValue() + 1);
}

// Starts timer on first tile pressed
void Minesweeper::startGame()
{
	// Disconnect this function to prevent constant restart of timer
	disconnect(m_game, SIGNAL(clicked()), this, SLOT(startGame()));
	// Set timer to pulse every second
	m_timer.start(1000);
}

// Set the windows to the minimal size to fit all items
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
