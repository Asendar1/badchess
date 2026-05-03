#include "piece.hpp"

void Piece::drawPiece(float, float, sf::RenderWindow &)
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

void Bishop::drawPiece(float x, float y, sf::RenderWindow &window)
{
	image.setPosition(sf::Vector2f(x * 120 + 24, y * 120 + 12));
	window.draw(image);
}

void Queen::drawPiece(float x, float y, sf::RenderWindow &window)
{
	image.setPosition(sf::Vector2f(x * 120 + 24, y * 120 - 5));
	window.draw(image);
}

void King::drawPiece(float x, float y, sf::RenderWindow &window)
{
	image.setPosition(sf::Vector2f(x * 120 + 24, y * 120 - 5));
	window.draw(image);
}

void Rook::drawPiece(float x, float y, sf::RenderWindow &window)
{
	image.setPosition(sf::Vector2f(x * 120 + 24, y * 120 + 12));
	window.draw(image);
}

int Piece::checkValidAndMove(t_moveInfo &info)
{
	(void)info;
	return 0;
}

int Pawn::checkValidAndMove(t_moveInfo &info)
{
	if (isWhite)
	{
		if (hasMoved)
		{
			if (info.old_row - 1 == info.row)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			if (info.old_row - 2 == info.row || info.old_row - 1 == info.row)
			{
				hasMoved = true;
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		if (hasMoved)
		{
			if (info.old_row + 1 == info.row)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			if (info.old_row + 2 == info.row || info.old_row + 1 == info.row)
			{
				hasMoved = true;
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
}
