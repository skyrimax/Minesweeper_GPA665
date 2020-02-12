#include "Minefield.h"
#include <random>
#include <immintrin.h>

// Convenience fonction converting the difficulty to a double representing the associated density
double Minefield::difficultyToDouble(DifficultyLevel diff)
{
	switch (diff)
	{
	case Minefield::DifficultyLevel::SuperEasy:
		return 0.05;
		break;
	case Minefield::DifficultyLevel::Easy:
		return 0.10;
		break;
	case Minefield::DifficultyLevel::Medium:
		return 0.15;
		break;
	case Minefield::DifficultyLevel::Hard:
		return 0.20;
		break;
	case Minefield::DifficultyLevel::SuperHard:
		return 0.25;
		break;
	default:
		return 0;
		break;
	}
}

// Default cunstructor for the Minefield class
Minefield::Minefield()
	: QGraphicsScene()
{
	// Temporary Box pointer to hold last created Box object
	Box* tile;

	m_field = new Grid<Box*>;
	m_mines = new Vector<Box*>;

	// Initializing internal variables to coherent defaults values
	m_gameState = State::InGame;
	m_nbBowUnexplored = 1;
	m_nbMines = 0;
	m_shownNbMines = m_nbMines;
	m_questionMarkAvailability = true;

	// Creates the only Box in the default minefield
	tile = new Box(this, 0, 0);
	m_field->at(0, 0) = tile;
	addItem(tile);

	// Connect the released signal from the Box to the slot to evaluate the state of the game
	connect(tile, SIGNAL(released()), this, SLOT(evaluateState()));

	// Connect the click reladed signals from the Box to the equivalent signals in the Minefield
	connect(tile, SIGNAL(clicked()), this, SIGNAL(clicked()));
	connect(tile, SIGNAL(released()), this, SIGNAL(released()));

	// Connect the end of game signals to the end of game functions
	connect(this, SIGNAL(victory()), this, SLOT(endOfGame()));
	connect(this, SIGNAL(loss()), this, SLOT(endOfGame()));

	// Places the mines on the board
	initialiseMines();

	// Link the Boxes to their neighbors
	initialiseNeighbors();
}

// Cunstructor enabling the passing of height and width at declaration
Minefield::Minefield(size_type nbRows, size_type nbCols)
	: QGraphicsScene()
{
	// Temporary Box pointer to hold last created Box object
	Box* tile;

	m_field = new Grid<Box*>(nbRows, nbCols);
	m_mines = new Vector<Box*>;

	// Initializing internal variables to coherent defaults values
	m_gameState = State::InGame;
	m_nbMines = 0;
	m_shownNbMines = m_nbMines;
	//Initialised based on height and width
	m_nbBowUnexplored = nbRows * nbCols - m_nbMines;
	m_questionMarkAvailability = true;

	// Creates every Boxes
	for (int i = 0; i < nbRows; ++i) {
		for (int j = 0; j < nbCols; ++j) {
			// Creates the Box with its coodinates in the scene
			tile = new Box(this, i, j);
			m_field->at(i, j) = tile;
			addItem(tile);

			// Connect the released signal from the Box to the slot to evaluate the state of the game
			connect(tile, SIGNAL(released()), this, SLOT(evaluateState()));

			// Connect the click reladed signals from the Box to the equivalent signals in the Minefield
			connect(tile, SIGNAL(clicked()), this, SIGNAL(clicked()));
			connect(tile, SIGNAL(released()), this, SIGNAL(released()));
		}
	}

	// Connect the end of game signals to the end of game functions
	connect(this, SIGNAL(victory()), this, SLOT(endOfGame()));
	connect(this, SIGNAL(loss()), this, SLOT(endOfGame()));

	// Places the mines on the board
	initialiseMines();

	// Link the Boxes to their neighbors
	initialiseNeighbors();
}

// Cunstructor enabling the passing of height and width and difficulty at declaration
Minefield::Minefield(size_type nbRows, size_type nbCols, DifficultyLevel diff)
	: QGraphicsScene()
{
	// Temporary Box pointer to hold last created Box object
	Box* tile;

	// Initialise internal values base on passed parameters
	m_gameState = State::InGame;
	m_nbMines = nbRows * nbCols*difficultyToDouble(diff);
	m_shownNbMines = m_nbMines;
	m_nbBowUnexplored = nbRows * nbCols - m_nbMines;
	m_questionMarkAvailability = true;

	m_field = new Grid<Box*>(nbRows, nbCols);
	m_mines = new Vector<Box*>;

	// Creates every Boxes
	for (int i = 0; i < nbRows; ++i) {
		for (int j = 0; j < nbCols; ++j) {
			// Creates the Box with its coodinates in the scene
			tile = new Box(this, i, j);
			m_field->at(i, j) = tile;
			addItem(tile);

			// Connect the released signal from the Box to the slot to evaluate the state of the game
			connect(tile, SIGNAL(released()), this, SLOT(evaluateState()));

			// Connect the click reladed signals from the Box to the equivalent signals in the Minefield
			connect(tile, SIGNAL(clicked()), this, SIGNAL(clicked()));
			connect(tile, SIGNAL(released()), this, SIGNAL(released()));
		}
	}

	// Connect the end of game signals to the end of game functions
	connect(this, SIGNAL(victory()), this, SLOT(endOfGame()));
	connect(this, SIGNAL(loss()), this, SLOT(endOfGame()));

	// Places the mines on the board
	initialiseMines();

	// Link the Boxes to their neighbors
	initialiseNeighbors();
}

// Cunstructor enabling the passing of height and width and mine density at declaration
Minefield::Minefield(size_type nbRows, size_type nbCols, double mineDensity)
	: QGraphicsScene()
{
	// Temporary Box pointer to hold last created Box object
	Box* tile;

	m_field = new Grid<Box*>(nbRows, nbCols);
	m_mines = new Vector<Box*>;

	// Initialise internal values base on passed parameters
	m_gameState = State::InGame;
	int m_nbMines = nbRows * nbCols*mineDensity;
	m_shownNbMines = m_nbMines;
	m_nbBowUnexplored = nbRows * nbCols - m_nbMines;
	m_questionMarkAvailability = true;

	// Creates every Boxes
	for (int i = 0; i < nbRows; ++i) {
		for (int j = 0; j < nbCols; ++j) {
			// Creates the Box with its coodinates in the scene
			tile = new Box(this, i, j);
			m_field->at(i, j) = tile;
			addItem(tile);

			// Connect the released signal from the Box to the slot to evaluate the state of the game
			connect(tile, SIGNAL(released()), this, SLOT(evaluateState()));

			// Connect the click reladed signals from the Box to the equivalent signals in the Minefield
			connect(tile, SIGNAL(clicked()), this, SIGNAL(clicked()));
			connect(tile, SIGNAL(released()), this, SIGNAL(released()));
		}
	}

	// Connect the end of game signals to the end of game functions
	connect(this, SIGNAL(victory()), this, SLOT(endOfGame()));
	connect(this, SIGNAL(loss()), this, SLOT(endOfGame()));

	// Places the mines on the board
	initialiseMines();

	// Link the Boxes to their neighbors
	initialiseNeighbors();
}

// Cunstructor enabling the passing of height and width and number of mines at declaration
Minefield::Minefield(size_type nbRows, size_type nbCols, int nbMines)
	: QGraphicsScene()
{
	// Temporary Box pointer to hold last created Box object
	Box* tile;

	m_field = new Grid<Box*>(nbRows, nbCols);
	m_mines = new Vector<Box*>;

	// Initialise internal values base on passed parameters
	m_gameState = State::InGame;
	m_nbMines = nbMines;
	m_shownNbMines = m_nbMines;
	m_nbBowUnexplored = nbRows * nbCols - m_nbMines;
	m_questionMarkAvailability = true;

	// Creates every Boxes
	for (int i = 0; i < nbRows; ++i) {
		for (int j = 0; j < nbCols; ++j) {
			// Creates the Box with its coodinates in the scene
			tile = new Box(this, i, j);
			m_field->at(i, j) = tile;
			addItem(tile);

			// Connect the released signal from the Box to the slot to evaluate the state of the game
			connect(tile, SIGNAL(released()), this, SLOT(evaluateState()));

			// Connect the click reladed signals from the Box to the equivalent signals in the Minefield
			connect(tile, SIGNAL(clicked()), this, SIGNAL(clicked()));
			connect(tile, SIGNAL(released()), this, SIGNAL(released()));
		}
	}

	// Connect the end of game signals to the end of game functions
	connect(this, SIGNAL(victory()), this, SLOT(endOfGame()));
	connect(this, SIGNAL(loss()), this, SLOT(endOfGame()));

	// Places the mines on the board
	initialiseMines();

	// Link the Boxes to their neighbors
	initialiseNeighbors();
}

Minefield::~Minefield()
{
	delete m_mines;

	// Deletes all Boxes from the minefield
	Vector<size_type> size = m_field->size();
	for (int i = 0; i < size[0]; ++i) {
		for (int j = 0; j < size[1]; ++j) {
			delete m_field->at(i, j);
		}
	}

	delete m_field;
}

// Accessor for the game state
Minefield::State Minefield::gameState()
{
	return m_gameState;
}

// Accessor retruning if ? are available
bool Minefield::questionMarkAvailability()
{
	return m_questionMarkAvailability;
}

// Accesor returning the number of mines to be dispalyed
int Minefield::shownNbMines()
{
	return m_shownNbMines;
}

// Methode to explore the Boc at the specified coordinates
void Minefield::explore(Coordinates pos)
{
	// Explores Box
	m_field->at(pos.row(), pos.col())->expose();

	// Check if player has won of lost
	evaluateState();
}

// Method to toggle the Marked state of specified Box
void Minefield::mark(Coordinates pos)
{
	m_field->at(pos.row(), pos.col())->mark();

	boxExplored();
}

// Method decrementing the number of unexplored boxes, called everytime a box is revealed
void Minefield::boxExplored()
{
	m_nbBowUnexplored--;
}

// Method incrementing the number of mines, called when a box is no longer marked as flagged
void Minefield::incShownNbMines()
{
	++m_shownNbMines;
	emit nbMinesChanged(m_shownNbMines);
}

// Method decrementing the number of mines, called when a box is no longer marked as flagged
void Minefield::decShownNbMines()
{
	--m_shownNbMines;
	emit nbMinesChanged(m_shownNbMines);
}

// Methode to link every boxes to their neighbors
void Minefield::initialiseNeighbors()
{
	// Get the size of the grid
	Vector<size_type> size = m_field->size();

	// GO trhough every boxes in the grid
	for (int i = 0; i < size[0]; ++i) {
		for (int j = 0; j < size[1]; ++j) {
			// Clear neighbors from grid, reset
			m_field->at(i, j)->clearNeighbors();

			// If not on top row
			if (i > 0) {
				// Add boxe above
				m_field->at(i, j)->addNeighbors(m_field->at(i - 1, j));
			}
			// If not in top-left corner
			if (i > 0 && j>0) {
				// Add box above to the left
				m_field->at(i, j)->addNeighbors(m_field->at(i - 1, j - 1));
			}
			// If not in top-right corner
			if (i > 0 && j+1 < size[1]) {
				// Add box above to the right
				m_field->at(i, j)->addNeighbors(m_field->at(i - 1, j + 1));
			}
			// If not on the left most column
			if (j > 0) {
				// Add the box to the left
				m_field->at(i, j)->addNeighbors(m_field->at(i, j - 1));
			}
			// If not on the right most column
			if (j+1 < size[1]) {
				// Add the box to the right
				m_field->at(i, j)->addNeighbors(m_field->at(i, j + 1));
			}
			// If not on the last row
			if (i + 1 < size[0]) {
				// Add box below
				m_field->at(i, j)->addNeighbors(m_field->at(i + 1, j));
			}
			// If not in the botton-left corner
			if (i + 1 < size[0] && j > 0) {
				// Add the box bellow to the left
				m_field->at(i, j)->addNeighbors(m_field->at(i + 1, j - 1));
			}
			// If not in the bottom-right corner
			if (i + 1 < size[0] && j+1 < size[1]) {
				// Add the box bellow to the right
				m_field->at(i, j)->addNeighbors(m_field->at(i + 1, j + 1));
			}

			// Set value based in the neighboring mines
			m_field->at(i, j)->initialiseMines();
		}
	}
}

// Methode to randomly place the mines in the minefield
void Minefield::initialiseMines()
{
	// Get the size of the grid
	Vector<size_type> size = m_field->size();

	// Go through all the boxes and reset their value to 0
	for (int i = 0; i < size[0]; ++i) {
		for (int j = 0; j < size[1]; ++j) {
			m_field->at(i, j)->setValue(0);
		}
	}

	// Creation of the 2 distributions that will be used to generate random valid coodinates
	std::uniform_int_distribution<int> xRandDist(0, size[0] - 1);
	std::uniform_int_distribution<int> yRandDist(0, size[1] - 1);

	// Creation and filling of the seed
	unsigned long long  seed;
	// MUST BE RUN ON INTEL 5TH GEN OR NEWER (BROADWELL)
	// OR AMD ZEN PROCESSOR
	_rdseed64_step(&seed);

	// Creation and seeding of the random nomber generator
	std::mt19937_64 gen(seed);

	int row;
	int col;

	// Clear the array containing reference to all boxes with a mine
	m_mines->clear();

	// Counter of the number of mines placed
	int i = 0;

	// As long as the requiered number of mines hasn't been placed
	while(i < m_nbMines) {
		// Generate a random coordinate
		row = xRandDist(gen);
		col = yRandDist(gen);

		// If the random coordinate does not already hold a mine
		if (m_field->at(row, col)->value() != -1) {
			// Put mine at random coordinate
			m_field->at(row, col)->setValue(-1);
			// Add box to the list on boxes with mines
			m_mines->push_back(m_field->at(row, col));
			// INcrement the number of mines placed
			i++;
		}
	}
}

// Return if the ? marking is available
void Minefield::setQuestionMarkAvailability(bool availability) {
	m_questionMarkAvailability = availability;
}

// Check if the game should en or continue
void Minefield::evaluateState()
{
	// Go through the list of boxes containing mines
	for (int i = 0; i < m_mines->size(); ++i) {
		// If one of the mines has been exposed
		if (m_mines->at(i)->exposed()) {
			// The player losses the game
			m_gameState = State::Defeat;

			// Emit signal that the player has lost
			emit loss();
			return;
		}
	}

	// If all boxes not holding mines have been exposed
	if (!m_nbBowUnexplored) {
		// The player wins
		m_gameState = State::Victory;

		// Emit signal that the player has won
		emit victory();
	}
	else {

		// Else the game is still going
		m_gameState = State::InGame;
	}
}

// At the end of the game, exposed all the mines
void Minefield::endOfGame()
{
	// Get the size of the grid
	Vector<size_type> size = m_field->size();

	// Go through all the boxes and reveal their content
	for (int i = 0; i < size[0]; ++i) {
		for (int j = 0; j < size[1]; ++j) {
			m_field->at(i, j)->revealForEndOfGame();
		}
	}
}