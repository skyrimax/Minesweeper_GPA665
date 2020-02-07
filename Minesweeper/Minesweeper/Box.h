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

	bool exposed();
	int value();
	void setValue(int value);
	Marking marked();

	void expose();
	void mark();

	void addNeighbors(Box* neighbor);
	void clearNeighbors();

	void initialiseMines();

signals:
	void clicked();
	void released();

protected:
	// Events grabbers
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	void setImage();

private:
	int m_value;
	bool m_exposed;
	bool m_clicked;
	Marking m_marked;

	Minefield* m_minefield;

	Vector<Box*> m_neighbors;

	QPixmap m_sprite;
};

