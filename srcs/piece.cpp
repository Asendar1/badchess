#include "piece.hpp"
#include "board.hpp"

bool isPathClear(int from_row, int from_col, int to_row, int to_col,
				 const std::array<std::array<Piece *, 8>, 8> &grid)
{
	// i don't think the user can reach this point but just in case
	if (to_row > 7 || to_row < 0 || to_col > 7 || to_col < 0)
		return false;

	// this means is row > old_row ? then 1. not bigger? then -1. Either? then 0. Same goes for col
	int row_step = (to_row > from_row) ? 1 : (to_row < from_row) ? -1
																 : 0;
	int col_step = (to_col > from_col) ? 1 : (to_col < from_col) ? -1
																 : 0;

	int curr_row = from_row + row_step;
	int curr_col = from_col + col_step;

	while (curr_row != to_row || curr_col != to_col)
	{
		if (grid[curr_row][curr_col] != nullptr)
			return false;
		curr_row += row_step;
		curr_col += col_step;
	}
	return true;
}

int isKingCheck(int king_row, int king_col, bool isWhite, std::array<std::array<Piece *, 8>, 8> &grid)
{
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if (grid[row][col] != nullptr && grid[row][col]->getIsWhite() != isWhite)
			{
				t_moveInfo info = {row, col, king_col, king_row};
				if (grid[row][col]->checkValidAndMove(info, grid))
					return 1;
			}
		}
	}
	return 0;
}

void Piece::drawPiece(float, float, sf::RenderWindow &)
{
}

void Pawn::drawPiece(float x, float y, sf::RenderWindow &window)
{
	image.setPosition(sf::Vector2f(x * BOARD_SIZE / 8 + 24, y * BOARD_SIZE / 8 + 12));
	window.draw(image);
}

void Knight::drawPiece(float x, float y, sf::RenderWindow &window)
{
	image.setPosition(sf::Vector2f(x * BOARD_SIZE / 8 + 24, y * BOARD_SIZE / 8 + 12));
	window.draw(image);
}

void Bishop::drawPiece(float x, float y, sf::RenderWindow &window)
{
	image.setPosition(sf::Vector2f(x * BOARD_SIZE / 8 + 24, y * BOARD_SIZE / 8 + 12));
	window.draw(image);
}

void Queen::drawPiece(float x, float y, sf::RenderWindow &window)
{
	image.setPosition(sf::Vector2f(x * BOARD_SIZE / 8 + 24, y * BOARD_SIZE / 8 - 5));
	window.draw(image);
}

void King::drawPiece(float x, float y, sf::RenderWindow &window)
{
	image.setPosition(sf::Vector2f(x * BOARD_SIZE / 8 + 24, y * BOARD_SIZE / 8 - 5));
	window.draw(image);
}

void Rook::drawPiece(float x, float y, sf::RenderWindow &window)
{
	image.setPosition(sf::Vector2f(x * BOARD_SIZE / 8 + 24, y * BOARD_SIZE / 8 + 12));
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

	// * EnPassant
	// thing so hard coded lol
	if (info.col == info.old_col + 1 || info.col == info.old_col - 1)
	{
		if (info.row == forward_one && grid[info.old_row][info.col] != nullptr)
		{
			Pawn *adjacent_pawn = dynamic_cast<Pawn *>(grid[info.old_row][info.col]);
			if (adjacent_pawn != nullptr && adjacent_pawn->hasEnPassant &&
				isWhite != adjacent_pawn->getIsWhite())
			{
				return 1;
			}
		}
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
		return 1;
	}

	return 0;
}

int King::checkValidAndMove(t_moveInfo &info, std::array<std::array<Piece *, 8>, 8> &grid)
{
	// Castling
	if (!hasMoved && info.row == info.old_row && std::abs(info.col - info.old_col) == 2)
	{
		int rook_col = (info.col > info.old_col) ? 7 : 0;
		Rook *rook = dynamic_cast<Rook *>(grid[info.old_row][rook_col]);
		if (rook != nullptr && !rook->hasMoved && isWhite == rook->getIsWhite())
		{
			// check for pieces in between
			for (int c = std::min(info.old_col, rook_col) + 1; c < std::max(info.old_col, rook_col); c++)
			{
				if (grid[info.old_row][c] != nullptr)
					return 0;
			}
			// check if its dangerous to castle
			int dir = (info.col > info.old_col) ? 1 : -1;
			for (int c = info.old_col; c != info.old_col + (dir * 3); c += dir)
			{
				if (isKingCheck(info.old_row, c, isWhite, grid))
					return 0;
			}
			return 1;
		}
	}

	bool valid_move = (std::abs(info.row - info.old_row) <= 1) &&
					  (std::abs(info.col - info.old_col) <= 1);
	if (!valid_move)
		return 0;

	if (grid[info.row][info.col] == nullptr)
		return 1;

	if (!(grid[info.row][info.col]->getIsWhite() == isWhite))
		return 1;
	return 0;
}

int Rook::checkValidAndMove(t_moveInfo &info, std::array<std::array<Piece *, 8>, 8> &grid)
{
	bool valid_move = (info.row == info.old_row || info.col == info.old_col);
	if (!valid_move)
		return 0;

	if (isPathClear(info.old_row, info.old_col, info.row, info.col, grid) == false)
		return 0;

	if (grid[info.row][info.col] == nullptr)
		return 1;
	if (!(grid[info.row][info.col]->getIsWhite() == isWhite))
		return 1;

	return 0;
}

int Knight::checkValidAndMove(t_moveInfo &info, std::array<std::array<Piece *, 8>, 8> &grid)
{
	bool validMove = (std::abs(info.row - info.old_row) == 2 && std::abs(info.col - info.old_col) == 1) ||
					 (std::abs(info.row - info.old_row) == 1 && std::abs(info.col - info.old_col) == 2);
	if (!validMove)
		return 0;

	if (grid[info.row][info.col] == nullptr)
		return 1;
	if (!(grid[info.row][info.col]->getIsWhite() == isWhite))
		return 1;

	return 0;
}

int Bishop::checkValidAndMove(t_moveInfo &info, std::array<std::array<Piece *, 8>, 8> &grid)
{
	bool valid_move = (std::abs(info.row - info.old_row) == std::abs(info.col - info.old_col));
	if (!valid_move)
		return 0;

	if (isPathClear(info.old_row, info.old_col, info.row, info.col, grid) == false)
		return 0;

	if (grid[info.row][info.col] == nullptr)
		return 1;
	if (!(grid[info.row][info.col]->getIsWhite() == isWhite))
		return 1;

	return 0;
}

int Queen::checkValidAndMove(t_moveInfo &info, std::array<std::array<Piece *, 8>, 8> &grid)
{
	bool valid_move = (std::abs(info.row - info.old_row) == std::abs(info.col - info.old_col)) ||
					  (info.row == info.old_row || info.col == info.old_col);
	if (!valid_move)
		return 0;

	if (isPathClear(info.old_row, info.old_col, info.row, info.col, grid) == false)
		return 0;

	if (grid[info.row][info.col] == nullptr)
		return 1;
	if (!(grid[info.row][info.col]->getIsWhite() == isWhite))
		return 1;

	return 0;
}
