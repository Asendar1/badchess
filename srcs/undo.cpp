#include "board.hpp"
#include "piece.hpp"

int isKingCheck(int king_row, int king_col, bool isWhite, std::array<std::array<Piece *, 8>, 8> &grid);

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

std::vector<t_moveInfo> Board::getAllLegalMoves(bool isWhite)
{
	std::vector<t_moveInfo> moveList;

	for (int s_row = 0; s_row < 8; s_row++)
	{
		for (int s_col = 0; s_col < 8; s_col++)
		{
			if (grid[s_row][s_col] != nullptr && grid[s_row][s_col]->getIsWhite() == isWhite)
			{
				for (int e_row = 0; e_row < 8; e_row++)
				{
					for (int e_col = 0; e_col < 8; e_col++)
					{
						t_moveInfo info = {s_row, s_col, e_col, e_row};

						if (grid[s_row][s_col]->checkValidAndMove(info, grid))
						{
							Piece *temp = grid[e_row][e_col];
							grid[e_row][e_col] = grid[s_row][s_col];
							grid[s_row][s_col] = nullptr;

							int k_row = -1, k_col = -1;
							for (int i = 0; i < 8; i++)
							{
								for (int j = 0; j < 8; j++)
								{
									if (grid[i][j] != nullptr && grid[i][j]->getIsWhite() == isWhite)
									{
										if (dynamic_cast<King *>(grid[i][j]) != nullptr)
										{
											k_row = i;
											k_col = j;
											break;
										}
									}
									if (k_row != -1)
										break;
								}
								if (k_row != -1)
									break;
							}

							if (!isKingCheck(k_row, k_col, isWhite, grid))
								moveList.push_back(info);

							grid[s_row][s_col] = grid[e_row][e_col];
							grid[e_row][e_col] = temp;
						}
					}
				}
			}
		}
	}
	return moveList;
}
