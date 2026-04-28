#include "piece.hpp"

void Piece::drawPiece(float x, float y, sf::RenderWindow &window)
{
	if (dynamic_cast<Pawn *>(this))
	{
		image.setPosition(sf::Vector2f(x * 120 + 24, y * 120 + 12));
		window.draw(image);
	}
}
