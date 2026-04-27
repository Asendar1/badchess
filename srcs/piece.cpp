#include "piece.hpp"

void Piece::drawPiece(int x, int y, sf::RenderWindow &window)
{
	if (dynamic_cast<Pawn *>(this))
	{
		image.setPosition(sf::Vector2f(x, y));
		window.draw(image);
	}
}
