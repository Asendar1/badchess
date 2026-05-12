#include "board.hpp"

int Board::minmax(int depth, bool whiteTurn)
{
	if (!depth) return evaluateBoard();

	std::vector<t_moveInfo> moves = getAllLegalMoves(whiteTurn);
	if (moves.empty())
	{
		if (whiteTurn)
			return isWhiteKingInCheck ? -10000 : 0; // black wins or stalemate
		else
			return isBlackKingInCheck ? 10000 : 0; // white wins or stalemate
	}

	int bestScore = whiteTurn ? -10000 : 10000;
	for (auto &move : moves)
	{
		selected_piece = grid[move.old_row][move.old_col];
		makeMove(move);
		int score = minmax(depth - 1, !whiteTurn);
		selected_piece = nullptr;
		undoLastMove();

		if (whiteTurn && score > bestScore)
			bestScore = score;
		else if (!whiteTurn && score < bestScore)
			bestScore = score;
	}
	return bestScore;
}

t_moveInfo Board::findBestMove(int depth, bool isWhite)
{
	std::vector<t_moveInfo> moves = getAllLegalMoves(isWhite);

	t_moveInfo bestMove = moves[0];
	int bestScore = isWhite ? -10000 : 10000;

	for (auto &move : moves)
	{
		selected_piece = grid[move.old_row][move.old_col];
		makeMove(move);
		int score = minmax(depth - 1, !isWhite);
		selected_piece = nullptr;
		undoLastMove();

		if (isWhite && score > bestScore)
		{
			bestScore = score;
			bestMove = move;
		}
		else if (!isWhite && score < bestScore)
		{
			bestScore = score;
			bestMove = move;
		}
	}

	return bestMove;
}
