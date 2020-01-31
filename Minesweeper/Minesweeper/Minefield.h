#pragma once

#include"Grid.h"
#include"Box.h"
#include"Coordinates.h"

class Minefield
{
public:
	//Type to indicate size of container
	typedef unsigned int size_type;

	enum class DifficultyLevel {
		TresFacile,
		Facile,
		Moyen,
		Difficile,
		TresDifficile
	};
	static double difficultyToDouble(DifficultyLevel diff);

	enum class UIType {
		Synchronous,
		Asynchronous
	};

	enum class State {
		InGame,
		Defeat,
		Victory
	};

	Minefield();
	Minefield(size_type nbRows, size_type nbCols);
	Minefield(size_type nbRows, size_type nbCols, DifficultyLevel diff);
	Minefield(size_type nbRows, size_type nbCols, double mineDensity);
	Minefield(size_type nbRows, size_type nbCols, int nbMines);
	~Minefield();

	State gameState();

	void explore(Coordinates pos);
	void mark(Coordinates pos);

	void boxExplored();

	void initialiseNeighbors();
	void initialiseMines();
	
private:
	void evaluateState();

	Grid<Box*>* m_field;
	Vector<Box*>* m_mines;

	State m_gameState;

	int m_nbBowUnexplored;
	int m_nbMines;

	UIType m_uiType;
};

