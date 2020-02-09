#include "Minefield.h"
#include <random>
#include <immintrin.h>

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

Minefield::Minefield()
	: QGraphicsScene()
{
	Box* tile;

	m_field = new Grid<Box*>;
	m_mines = new Vector<Box*>;

	m_gameState = State::InGame;
	m_nbBowUnexplored = 1;
	m_nbMines = 0;

	tile = new Box(this, 0, 0);
	m_field->at(0, 0) = tile;
	addItem(tile);

	connect(tile, SIGNAL(released()), this, SLOT(evaluateState()));

	initialiseMines();
	initialiseNeighbors();
}

Minefield::Minefield(size_type nbRows, size_type nbCols)
	: QGraphicsScene()
{
	Box* tile;

	m_field = new Grid<Box*>(nbRows, nbCols);
	m_mines = new Vector<Box*>;

	m_gameState = State::InGame;
	m_nbMines = 0;
	m_nbBowUnexplored = nbRows*nbCols-m_nbMines;

	for (int i = 0; i < nbRows; ++i) {
		for (int j = 0; j < nbCols; ++j) {
			tile = new Box(this, i, j);
			m_field->at(i, j) = tile;
			addItem(tile);

			connect(tile, SIGNAL(released()), this, SLOT(evaluateState()));
		}
	}

	initialiseMines();
	initialiseNeighbors();
}


Minefield::Minefield(size_type nbRows, size_type nbCols, DifficultyLevel diff)
	: QGraphicsScene()
{
	Box* tile;

	m_gameState = State::InGame;
	m_nbMines = nbRows * nbCols*difficultyToDouble(diff);
	m_nbBowUnexplored = nbRows * nbCols-m_nbMines;

	m_field = new Grid<Box*>(nbRows, nbCols);
	m_mines = new Vector<Box*>;

	for (int i = 0; i < nbRows; ++i) {
		for (int j = 0; j < nbCols; ++j) {
			tile = new Box(this, i, j);
			m_field->at(i, j) = tile;
			addItem(tile);

			connect(tile, SIGNAL(released()), this, SLOT(evaluateState()));
		}
	}

	initialiseMines();
	initialiseNeighbors();
}

Minefield::Minefield(size_type nbRows, size_type nbCols, double mineDensity)
	: QGraphicsScene()
{
	Box* tile;

	m_field = new Grid<Box*>(nbRows, nbCols);
	m_mines = new Vector<Box*>;

	m_gameState = State::InGame;
	m_nbBowUnexplored = nbRows * nbCols;

	int m_nbMines = nbRows * nbCols*mineDensity;

	for (int i = 0; i < nbRows; ++i) {
		for (int j = 0; j < nbCols; ++j) {
			tile = new Box(this, i, j);
			m_field->at(i, j) = tile;
			addItem(tile);

			connect(tile, SIGNAL(released()), this, SLOT(evaluateState()));
		}
	}

	initialiseMines();
	initialiseNeighbors();
}

Minefield::Minefield(size_type nbRows, size_type nbCols, int nbMines)
	: QGraphicsScene()
{
	Box* tile;
	m_field = new Grid<Box*>(nbRows, nbCols);
	m_mines = new Vector<Box*>;

	m_gameState = State::InGame;
	m_nbBowUnexplored = nbRows * nbCols;

	m_nbMines = nbMines;

	for (int i = 0; i < nbRows; ++i) {
		for (int j = 0; j < nbCols; ++j) {
			tile = new Box(this, i, j);
			m_field->at(i, j) = tile;
			addItem(tile);

			connect(tile, SIGNAL(released()), this, SLOT(evaluateState()));
		}
	}

	initialiseMines();
	initialiseNeighbors();
}

Minefield::~Minefield()
{
	delete m_mines;

	Vector<size_type> size = m_field->size();
	for (int i = 0; i < size[0]; ++i) {
		for (int j = 0; j < size[1]; ++j) {
			delete m_field->at(i, j);
		}
	}

	delete m_field;
}

Minefield::State Minefield::gameState()
{
	return State();
}

void Minefield::explore(Coordinates pos)
{
	m_field->at(pos.row(), pos.col())->expose();

	evaluateState();
}

void Minefield::mark(Coordinates pos)
{
	m_field->at(pos.row(), pos.col())->mark();
}

void Minefield::boxExplored()
{
	m_nbBowUnexplored--;
}

void Minefield::initialiseNeighbors()
{
	Vector<size_type> size = m_field->size();

	for (int i = 0; i < size[0]; ++i) {
		for (int j = 0; j < size[1]; ++j) {
			m_field->at(i, j)->clearNeighbors();

			if (i > 0) {
				m_field->at(i, j)->addNeighbors(m_field->at(i - 1, j));
			}
			if (i > 0 && j>0) {
				m_field->at(i, j)->addNeighbors(m_field->at(i - 1, j - 1));
			}
			if (i > 0 && j+1 < size[1]) {
				m_field->at(i, j)->addNeighbors(m_field->at(i - 1, j + 1));
			}
			if (j > 0) {
				m_field->at(i, j)->addNeighbors(m_field->at(i, j - 1));
			}
			if (j+1 < size[1]) {
				m_field->at(i, j)->addNeighbors(m_field->at(i, j + 1));
			}
			if (i + 1 < size[0]) {
				m_field->at(i, j)->addNeighbors(m_field->at(i + 1, j));
			}
			if (i + 1 < size[0] && j > 0) {
				m_field->at(i, j)->addNeighbors(m_field->at(i + 1, j - 1));
			}
			if (i + 1 < size[0] && j+1 < size[1]) {
				m_field->at(i, j)->addNeighbors(m_field->at(i + 1, j + 1));
			}

			m_field->at(i, j)->initialiseMines();
		}
	}
}

void Minefield::initialiseMines()
{
	Vector<size_type> size = m_field->size();
	for (int i = 0; i < size[0]; ++i) {
		for (int j = 0; j < size[1]; ++j) {
			m_field->at(i, j)->setValue(0);
		}
	}

	std::uniform_int_distribution<int> xRandDist(0, size[0] - 1);
	std::uniform_int_distribution<int> yRandDist(0, size[1] - 1);

	unsigned long long  seed;
	_rdseed64_step(&seed);

	std::mt19937_64 gen(seed);

	int row;
	int col;

	m_mines->clear();

	int i = 0;
	while(i < m_nbMines) {
		row = xRandDist(gen);
		col = yRandDist(gen);

		if (m_field->at(row, col)->value() != -1) {
			m_field->at(row, col)->setValue(-1);
			m_mines->push_back(m_field->at(row, col));
			i++;
		}
	}
}

void Minefield::evaluateState()
{
	for (int i = 0; i < m_mines->size(); ++i) {
		if (m_mines->at(i)->exposed()) {
			m_gameState = State::Defeat;

			emit loss();
			return;
		}
	}

	if (!m_nbBowUnexplored) {
		m_gameState = State::Victory;
		emit victory();
	}
	else {
		m_gameState = State::InGame;
	}
}
