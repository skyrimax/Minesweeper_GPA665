#include "Box.h"
#include "Minefield.h"
#include <QGraphicsSceneMouseEvent>

Box::Box()
	: QGraphicsPixmapItem()
{
	m_value = 0;
	m_exposed = false;
	m_marked = Marking::Blank;
	m_minefield = nullptr;

	setAcceptHoverEvents(true);

	setImage();
}

Box::Box(Minefield* minefield, int value, bool exposed, Marking marked)
	: QGraphicsPixmapItem()
{
	m_value = value;
	m_exposed = exposed;
	m_marked = marked;
	m_minefield = minefield;

	setAcceptHoverEvents(true);

	setImage();
}


Box::~Box()
{
}

bool Box::exposed()
{
	return m_exposed;
}

int Box::value()
{
	return m_value;
}

void Box::setValue(int value)
{
	m_value = value;
}

Box::Marking Box::marked()
{
	return m_marked;
}

void Box::expose()
{
	if (!m_exposed && m_marked == Marking::Blank) {
		m_exposed = true;
		m_minefield->boxExplored();

		if (m_value == 0) {
			for (int i=0; i < m_neighbors.size(); ++i) {
				m_neighbors[i]->expose();
			}
		}
	}

	setImage();
}

void Box::mark()
{
	if (m_marked == Marking::Blank) {
		m_marked = Marking::Flag;
	}
	else if (m_marked == Marking::Flag) {
		m_marked = Marking::QuestionMark;
	}
	else {
		m_marked = Marking::Blank;
	}
}

void Box::addNeighbors(Box * neighbor)
{
	m_neighbors.push_back(neighbor);
}

void Box::clearNeighbors()
{
	m_neighbors.clear();
}

void Box::initialiseMines()
{
	m_value = 0;

	for (int i = 0; i < m_neighbors.size(); ++i) {
		if (m_neighbors[i]->m_value = -1) {
			++m_value;
		}
	}
}

void Box::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
{
	
}

void Box::hoverLeaveEvent(QGraphicsSceneHoverEvent * event)
{
	if (m_clicked) {
		m_clicked = false;
		m_sprite.load(":/Minesweeper/sprites/block.png");
		setPixmap(m_sprite);
	}
}

void Box::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	switch (event->button())
	{
	case Qt::LeftButton:
		m_sprite.load(":/Minesweeper/sprites/empty.png");
		setPixmap(m_sprite);
		m_clicked = true;
		emit clicked();
		break;
	case Qt::RightButton:
		mark();
		break;
	case Qt::MidButton:
		m_sprite.load(":/Minesweeper/sprites/empty.png");
		setPixmap(m_sprite);
		m_clicked = true;
		emit clicked();
		break;
	default:
		break;
	}
}

void Box::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
	switch (event->button())
	{
	case Qt::LeftButton:
		m_clicked = false;
		expose();
		emit released();
		break;
	case Qt::RightButton:
		mark();
		break;
	case Qt::MidButton:
		m_clicked = false;
		// Implement a function to explore every tiles around this one
		// if there is time
		break;
	default:
		break;
	}
}

void Box::setImage()
{
	if (m_exposed) {
		switch (m_value)
		{
		case -1:
			if (m_marked == Marking::QuestionMark) {
				m_sprite.load(":/Minesweeper/sprites/mine_wrong_guess.png");
			}
			else {
				m_sprite.load(":/Minesweeper/sprites/mine.png");
			}
			break;
		case 0:
			m_sprite.load(":/Minesweeper/sprites/empty.png");
			break;
		case 1:
			m_sprite.load(":/Minesweeper/sprites/one.png");
			break;
		case 2:
			m_sprite.load(":/Minesweeper/sprites/two.png");
			break;
		case 3:
			m_sprite.load(":/Minesweeper/sprites/three.png");
			break;
		case 4:
			m_sprite.load(":/Minesweeper/sprites/four.png");
			break;
		case 5:
			m_sprite.load(":/Minesweeper/sprites/five.png");
			break;
		case 6:
			m_sprite.load(":/Minesweeper/sprites/six.png");
			break;
		case 7:
			m_sprite.load(":/Minesweeper/sprites/seven.png");
			break;
		case 8:
			m_sprite.load(":/Minesweeper/sprites/eight.png");
			break;
		default:
			break;
		}
	}
	else {
		switch (m_marked)
		{
		case Box::Marking::Blank:
			m_sprite.load(":/Minesweeper/sprites/block.png");
			break;
		case Box::Marking::Flag:
			m_sprite.load(":/Minesweeper/sprites/flagged.png");
			break;
		case Box::Marking::QuestionMark:
			m_sprite.load(":/Minesweeper/sprites/question_mark.png");
			break;
		default:
			break;
		}
	}

	setPixmap(m_sprite);
}
