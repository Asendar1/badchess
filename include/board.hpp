#pragma once

#include "piece.hpp"

#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

#ifndef BOARD_SIZE
#define BOARD_SIZE 960
#endif

struct undoMove
{
	t_moveInfo moveInfo;
	Piece *movedPiece;
	Piece *capturedPiece;

	bool wasFirstMove;
	bool wasEnPassant;

	Rook *castlingRook;
	bool wasCastling;

	Piece *promotedPiece;
	Pawn *enPassantdPawn;
};

class Board
{
private:
	Piece *selected_piece;
	int start_col;
	int start_row;
	int end_col;
	int end_row;
	bool isWhiteKingInCheck;
	bool isBlackKingInCheck;

	std::vector<undoMove> undoStack;

private:
	std::array<std::array<Piece *, 8>, 8> grid{};

	void draw_squares(sf::RenderWindow &window);
	void updateCheckStatus();
	void hasLegalMoves(bool *gameEnded);
	bool makeMove(t_moveInfo &moveInfo);
	void initUndoMove(undoMove &undo, t_moveInfo &moveInfo, Piece *movedPiece, Piece *capturedPiece);
	void undoLastMove();
	std::vector<t_moveInfo> getAllLegalMoves(bool isWhite);

public:
	Board();
	~Board();

	void gameloop();
};
