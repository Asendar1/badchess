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

	int dir = isWhite ? -1 : 1;
	int forward_one = info.old_row + dir;
	int forward_two = info.old_row + (2 * dir);

	// * Capture
	// TODO i need a way to broadcast captures for points calculations
	if ((info.col == info.old_col + 1 || info.col == info.old_col - 1) &&
		info.row == forward_one && grid[info.row][info.col] != nullptr)
	{
		if (!(isWhite == grid[info.row][info.col]->getIsWhite()))
			return 1;
	}

	// Pawns only move vertically (up and down)
	if (info.col != info.old_col)
		return 0;

	if (info.row == forward_one && grid[info.row][info.col] == nullptr)
		return 1;

	if (!hasMoved && info.row == forward_two &&
		grid[info.row][info.col] == nullptr &&
		grid[forward_one][info.col] == nullptr)
	{
		hasMoved = true;
		return 1;
	}

	return 0;
}

int King::checkValidAndMove(t_moveInfo &info, std::array<std::array<Piece *, 8>, 8> &grid)
{
	// TODO add an check if the king will be attack on his move
	bool valid_move = (std::abs(info.row - info.old_row) <= 1) &&
					  (std::abs(info.col - info.old_col) <= 1);
	if (!valid_move) return 0;

	if (grid[info.row][info.col] == nullptr)
		return 1;

	if (!(grid[info.row][info.col]->getIsWhite() == isWhite))
		return 1;
	return 0;
}

int Rook::checkValidAndMove(t_moveInfo &info, std::array<std::array<Piece *, 8>, 8> &grid)
{
	(void)info;
	(void)grid;
	return 0;
}

int Knight::checkValidAndMove(t_moveInfo &info, std::array<std::array<Piece *, 8>, 8> &grid)
{
	(void)info;
	(void)grid;
	return 0;
}

int Bishop::checkValidAndMove(t_moveInfo &info, std::array<std::array<Piece *, 8>, 8> &grid)
{
	(void)info;
	(void)grid;
	return 0;
}

int Queen::checkValidAndMove(t_moveInfo &info, std::array<std::array<Piece *, 8>, 8> &grid)
{
	(void)info;
	(void)grid;
	return 0;
}
