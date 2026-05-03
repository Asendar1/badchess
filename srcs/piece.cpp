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

int Piece::checkValidAndMove(t_moveInfo &info, std::array<std::array<Piece *, 8>, 8> &grid)
{
	(void)info;
	(void)grid;
	return 0;
}

int Pawn::checkValidAndMove(t_moveInfo &info, std::array<std::array<Piece *, 8>, 8> &grid)
{
	if (info.col != info.old_col)
		return 0;

	if (isWhite)
	{
		// * imma keep this but there is no way for an white pawn to capture another white pawn since they all move up
		// if (grid[info.row][info.col] != nullptr && grid[info.row][info.col]->getIsWhite())
		// {
		// 	return 0;
		// }
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
