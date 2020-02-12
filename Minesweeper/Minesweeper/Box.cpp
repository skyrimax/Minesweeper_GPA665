#include "Box.h"
#include "Minefield.h"
#include <QGraphicsSceneMouseEvent>

// Default cunstructor for the Box class
Box::Box()
	: QGraphicsPixmapItem()
{
	// Initializing internal variables to coherent defaults values
	m_value = 0;
	m_exposed = false;
	m_marked = Marking::Blank;
	m_minefield = nullptr;

	// Enable acceptance of hover events from GraphicsView framework
	// Might be useless, not brave enough to remove
	setAcceptHoverEvents(true);

	// Set the image to display with current default values
	setImage();
}

// Cunstructor enabling the passing of internal values at declaration
Box::Box(Minefield* minefield, int row, int col, int value, bool exposed, Marking marked)
	: QGraphicsPixmapItem()
{
	// Assigning passed parameters to internal values
	m_value = value;
	m_exposed = exposed;
	m_marked = marked;
	m_minefield = minefield;

	// Enable acceptance of hover events from GraphicsView framework
	// Might be useless, not brave enough to remove
	setAcceptHoverEvents(true);

	// Set the image to display with current values
	setImage();

	// Set position in graphics scene
	setPos(row*m_sprite.height(), col*m_sprite.width());
}


Box::~Box()
{
}

// Accessor returning if the Box should be exposed of remain hidden
bool Box::exposed()
{
	return m_exposed;
}

// Accessor returning the internal value of the box
int Box::value()
{
	return m_value;
}

// Motator setting the internal value of the Box
void Box::setValue(int value)
{
	m_value = value;
}

// Accessor returning the marking state of the Box
Box::Marking Box::marked()
{
	return m_marked;
}

// Recursive function exposing itself al all its neighbors
void Box::expose()
{
	// Expose self only if it is not already exposed (finishing condition)
	// and if it is not marked as  flagged
	if (!m_exposed && m_marked != Marking::Flag) {
		// Expose self
		m_exposed = true;

		// indicates to parent minefield that a Box as been exposed
		m_minefield->boxExplored();

		// Expose neighbors if self is not adjacent to a mine
		if (m_value == 0) {
			for (int i=0; i < m_neighbors.size(); ++i) {
				m_neighbors[i]->expose();
			}
		}
		// If self is a mine, show image of exploded mine
		else if (m_value == -1) {
			m_sprite.load(":/Minesweeper/sprites/mine_exploded.png");
			setPixmap(m_sprite);
			// emit signal signaling that a mine has been triggered
			emit clickedOnBomb();
			return;
		}
	}

	// Set the image to display with current values
	setImage();
}

// Fonction toggling between the different marked states
void Box::mark()
{
	// Blank --> Flagged
	if (m_marked == Marking::Blank) {
		m_marked = Marking::Flag;
		// Indicates to parent minefield that a box has been marked as flagged
		m_minefield->decShownNbMines();
	}
	else if (m_marked == Marking::Flag) {
		// Flagged --> ? if ? is allowed
		if (m_minefield->questionMarkAvailability()) {
			m_marked = Marking::QuestionMark;
		}
		// Else Flagged --> Blank
		else {
			m_marked = Marking::Blank;
		}
		m_minefield->incShownNbMines();
	}
	// ? --> Blank
	else {
		m_marked = Marking::Blank;
	}
}

// Fonction exposing the bow at the end of the game
// Does not trigger any signal or indication to parent minefield
void Box::revealForEndOfGame()
{
	m_exposed = true;

	// Set the image to display with current values
	setImage();
}

// Convenience function to add a neighbor to the box
void Box::addNeighbors(Box * neighbor)
{
	m_neighbors.push_back(neighbor);
}

// Convenience function to clear all neighbors
void Box::clearNeighbors()
{
	m_neighbors.clear();
}

// Sets the value depending on the amount of mines in neighboring boxes
void Box::initialiseMines()
{
	// Does nothing if box is a mine
	if (m_value != -1) {
		// Resets value
		m_value = 0;

		// Counts the number of mines around the box
		for (int i = 0; i < m_neighbors.size(); ++i) {
			if (m_neighbors[i]->m_value == -1) {
				++m_value;
			}
		}
	}
}

// Event handler for mouse press events received from the parent scene
void Box::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	// Does nothing if game is finished or already exposed
	if (m_minefield->gameState() != Minefield::State::InGame || m_exposed) {
		return;
	}

	// Depending on which button was pressed
	switch (event->button())
	{
	case Qt::LeftButton:
		// Shows pressed box on left click press
		if (m_marked != Marking::Flag) {
			m_sprite.load(":/Minesweeper/sprites/empty.png");
			setPixmap(m_sprite);
			// Emit signal that box was left clicked
			emit clicked();
		}
		break;
	case Qt::RightButton:
		// toggles marked state on right clic pressed
		mark();
		setImage();
		break;
	/**case Qt::MidButton:
		m_sprite.load(":/Minesweeper/sprites/empty.png");
		setPixmap(m_sprite);
		emit clicked();
		break;**/
	default:
		// Does nothing on other button pressed
		break;
	}
}

// Event handler for mouse release events received from the parent scene
void Box::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
	// Does nothing if game is finished
	if (m_minefield->gameState() != Minefield::State::InGame) {
		return;
	}

	// Depending on which button was pressed
	switch (event->button())
	{
	case Qt::LeftButton:
		// Triggers exploration of self and neighbors
		expose();
		// Emit signal that box was left released
		emit released();
		break;
	case Qt::RightButton:
		// Does nothing on right click release
		break;
	/**case Qt::MidButton:
		// Implement a function to explore every tiles around this one
		// if there is time
		break;**/
	default:
		// Does nothing on other button release
		break;
	}
}

// Function setting the displayed image depending on internal state
void Box::setImage()
{
	// If box is exposed, chooses depending on value
	if (m_exposed) {
		switch (m_value)
		{
		case -1:
			m_sprite.load(":/Minesweeper/sprites/mine.png");
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
	// If box is not exposed, chooses depending on maked state
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

	// Sets loaded image to the graphic item
	setPixmap(m_sprite);
}