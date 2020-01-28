#include "Minefield.h"
#include <random>
#include <immintrin.h>

Minefield::Minefield()
{
	m_field = new Grid<Box*>;
	m_mines = new Vector<Box*>;

	m_gameState = State::InGame;
	m_nbBowUnexplored = 1;
	m_nbMines = 0;

	m_field->at(0, 0) = new Box(this);
}

Minefield::Minefield(size_type nbRows, size_type nbCols)
{
	m_field = new Grid<Box*>(nbRows, nbCols);
	m_mines = new Vector<Box*>;

	m_gameState = State::InGame;
	m_nbBowUnexplored = nbRows*nbCols;
	m_nbMines = 0;

	for (int i = 0; i < nbRows; ++i) {
		for (int j = 0; j < nbCols; ++j) {
			m_field->at(i, j) = new Box(this);
		}
	}
}


Minefield::Minefield(size_type nbRows, size_type nbCols, DifficultyLevel diff)
{

	m_field = new Grid<Box*>(nbRows, nbCols);
	m_mines = new Vector<Box*>;

	m_gameState = State::InGame;
	m_nbBowUnexplored = nbRows * nbCols;

	switch (diff)
	{
	case Minefield::DifficultyLevel::TresFacile:
		m_nbMines = nbRows * nbCols*0.05;
		break;
	case Minefield::DifficultyLevel::Facile:
		m_nbMines = nbRows * nbCols*0.10;
		break;
	case Minefield::DifficultyLevel::Moyen:
		m_nbMines = nbRows * nbCols*0.15;
		break;
	case Minefield::DifficultyLevel::Difficile:
		m_nbMines = nbRows * nbCols*0.20;
		break;
	case Minefield::DifficultyLevel::TresDifficile:
		m_nbMines = nbRows * nbCols*0.25;
		break;
	default:
		m_nbMines = 0;
		break;
	}

	for (int i = 0; i < nbRows; ++i) {
		for (int j = 0; j < nbCols; ++j) {
			m_field->at(i, j) = new Box(this);
		}
	}

	initialiseNeighbors();
	initialiseMines();
}

Minefield::Minefield(size_type nbRows, size_type nbCols, double mineDensity)
{
	m_field = new Grid<Box*>(nbRows, nbCols);
	m_mines = new Vector<Box*>;

	m_gameState = State::InGame;
	m_nbBowUnexplored = nbRows * nbCols;

	int m_nbMines = nbRows * nbCols*mineDensity;

	for (int i = 0; i < nbRows; ++i) {
		for (int j = 0; j < nbCols; ++j) {
			m_field->at(i, j) = new Box(this);
		}
	}

	initialiseNeighbors();
	initialiseMines();
}

Minefield::Minefield(size_type nbRows, size_type nbCols, int nbMines)
{
	m_field = new Grid<Box*>(nbRows, nbCols);
	m_mines = new Vector<Box*>;

	m_gameState = State::InGame;
	m_nbBowUnexplored = nbRows * nbCols;

	m_nbMines = nbMines;

	for (int i = 0; i < nbRows; ++i) {
		for (int j = 0; j < nbCols; ++j) {
			m_field->at(i, j) = new Box(this);
		}
	}

	initialiseNeighbors();
	initialiseMines();
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

	for (int i = 0; i < m_nbMines; ++i) {
		row = xRandDist(gen);
		col = yRandDist(gen);

		m_field->at(row, col)->setValue(-1);
		m_mines->push_back(m_field->at(row, col));
	}
}

void Minefield::evaluateState()
{
	for (int i = 0; i < m_mines->size(); ++i) {
		if (m_mines->at(i)->exposed()) {
			m_gameState = State::Defeat;

			return;
		}
	}

	if (m_nbBowUnexplored == m_nbMines) {
		m_gameState = State::Victory;
	}
	else {
		m_gameState = State::InGame;
	}
}
