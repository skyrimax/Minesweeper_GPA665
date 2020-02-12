#pragma once

#include <QGraphicsPixmapItem>

#include "Vector.h"

class Minefield;

class Box:public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

public:
	enum class Marking {
		Blank,
		Flag,
		QuestionMark
	};

	Box();
	Box(Minefield* minefield, int row, int col, int value = 0, bool exposed = false, Marking marked = Marking::Blank);
	~Box();

	// Accessors and mutators
	bool exposed();
	int value();
	void setValue(int value);
	Marking marked();

	// Methods for usages diring game
	void expose();
	void mark();
	void revealForEndOfGame();

	// Methods related to the neighbors
	void addNeighbors(Box* neighbor);
	void clearNeighbors();

	// Methods related to the value of the box
	void initialiseMines();

signals:
	void clicked();
	void clickedOnBomb();
	void released();

protected:
	// Events grabbers
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	void setImage();

private:
	int m_value;
	bool m_exposed;
	Marking m_marked;

	Minefield* m_minefield;

	Vector<Box*> m_neighbors;

	QPixmap m_sprite;
};

