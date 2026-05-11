#include "board.hpp"
#include "piece.hpp"

void Board::initUndoMove(undoMove &undo, t_moveInfo &moveInfo, Piece *movedPiece, Piece *capturedPiece)
{
	undo.moveInfo = moveInfo;
	undo.movedPiece = movedPiece;
	undo.capturedPiece = capturedPiece;
	undo.wasFirstMove = false;
	undo.wasEnPassant = false;
	undo.wasCastling = false;
	undo.castlingRook = nullptr;
	undo.promotedPiece = nullptr;
	undo.enPassantdPawn = nullptr;
}

void Board::undoLastMove()
{
	if (undoStack.empty())
		return;

	undoMove last = undoStack.back();
	undoStack.pop_back();

	t_moveInfo info = last.moveInfo;

	if (last.promotedPiece)
	{
		delete grid[info.row][info.col];
		grid[info.row][info.col] = nullptr;
	}

	grid[info.old_row][info.old_col] = last.movedPiece;
	grid[info.row][info.col] = nullptr;

	if (last.capturedPiece != nullptr)
	{
		if (last.wasEnPassant)
			grid[info.old_row][info.col] = last.capturedPiece;
		else
			grid[info.row][info.col] = last.capturedPiece;
	}
	if (last.wasFirstMove)
	{
		if (Pawn *p = dynamic_cast<Pawn *>(last.movedPiece))
			p->hasMoved = false;
		else if (Rook *r = dynamic_cast<Rook *>(last.movedPiece))
			r->hasMoved = false;
		else if (King *k = dynamic_cast<King *>(last.movedPiece))
			k->hasMoved = false;
	}
	if (last.wasCastling)
	{
		int rook_col = info.old_col > info.col ? 0 : 7;
		int curr_rook_col = info.old_col > info.col ? info.col + 1 : info.col - 1;

		grid[info.old_row][rook_col] = last.castlingRook;
		grid[info.old_row][curr_rook_col] = nullptr;
		last.castlingRook->hasMoved = false;
	}
	if (Pawn *pawn = dynamic_cast<Pawn *>(last.movedPiece))
		pawn->hasEnPassant = false;

	if (last.enPassantdPawn)
		last.enPassantdPawn->hasEnPassant = true;
	updateCheckStatus();
}
