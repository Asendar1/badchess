#include "piece.hpp"

void Piece::drawPiece(float , float , sf::RenderWindow &)
{
}

void Pawn::drawPiece(float x, float y, sf::RenderWindow &window)
{
	image.setPosition(sf::Vector2f(x * 120 + 24, y * 120 + 12));
	window.draw(image);
}

void Knight::drawPiece(float x, float y, sf::RenderWindow &window)
{
	image.setPosition(sf::Vector2f(x * 120 + 24, y * 120 + 12));
	window.draw(image);
}
