#include "Minefield.h"



Minefield::Minefield()
{

}

Minefield::Minefield(size_type nbRows, size_type nbCols)
{
}


Minefield::Minefield(size_type nbRows, size_type nbCols, DifficultyLevel diff)
{
}

Minefield::Minefield(size_type nbRows, size_type nbCols, double mineDensity)
{
}

Minefield::Minefield(size_type nbRows, size_type nbCols, int nbMines)
{
}

Minefield::~Minefield()
{
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
