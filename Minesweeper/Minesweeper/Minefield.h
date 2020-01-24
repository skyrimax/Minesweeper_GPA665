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
		ndTresFacile,
		ndFacile,
		ndMoyen,
		ndDifficile,
		ndTresDifficile
	};

	enum class UIType {
		synchronous,
		asynchronous
	};

	Minefield();
	Minefield(size_type nbRows, size_type nbCols);
	Minefield(size_type nbRows, size_type nbCols, DifficultyLevel diff);
	Minefield(size_type nbRows, size_type nbCols, double mineDensity);
	Minefield(size_type nbRows, size_type nbCols, int nbMines);
	~Minefield();

	void explore(Coordinates pos);
	
private:
	Grid<Box*> m_field;

	UIType m_uiType;
};

