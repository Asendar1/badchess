#include "board.hpp"

int isKingCheck(int king_row, int king_col, bool isWhite, std::array<std::array<Piece *, 8>, 8> &grid);

#define hasPiece selected_piece != nullptr

int Board::evaluateBoard()
{
	int score = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (grid[i][j] != nullptr)
			{
				int pieceValue = 0;

				if (dynamic_cast<Pawn *>(grid[i][j]))
					pieceValue = 10;
				else if (dynamic_cast<Knight *>(grid[i][j]))
					pieceValue = 30;
				else if (dynamic_cast<Bishop *>(grid[i][j]))
					pieceValue = 30;
				else if (dynamic_cast<Rook *>(grid[i][j]))
					pieceValue = 50;
				else if (dynamic_cast<Queen *>(grid[i][j]))
					pieceValue = 90;

				// * poistive score means whites winning, vice versa
				if (grid[i][j]->getIsWhite())
				{
					score += pieceValue;
				}
				else
				{
					score -= pieceValue;
				}
			}
		}
	}

	return score;
}

bool Board::makeMove(t_moveInfo &moveInfo)
{
	if (selected_piece && selected_piece->checkValidAndMove(moveInfo, grid))
	{
		Piece *temp = grid[moveInfo.row][moveInfo.col];
		grid[moveInfo.row][moveInfo.col] = selected_piece;
		grid[moveInfo.old_row][moveInfo.old_col] = nullptr;

		int king_row = -1, king_col = -1;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (grid[i][j] != nullptr && grid[i][j]->getIsWhite() == selected_piece->getIsWhite())
				{
					King *king = dynamic_cast<King *>(grid[i][j]);
					if (king != nullptr)
					{
						king_row = i;
						king_col = j;
						break;
					}
				}
			}
			if (king_row != -1)
				break;
		}

		if (isKingCheck(king_row, king_col, selected_piece->getIsWhite(), grid))
		{
			// illegal move
			grid[moveInfo.row][moveInfo.col] = temp;
			grid[moveInfo.old_row][moveInfo.old_col] = selected_piece;
			return false;
		}
		else
		{
			// legal
			// save the moveInfo
			undoMove undo;
			initUndoMove(undo, moveInfo, selected_piece, temp);

			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (grid[i][j] != nullptr)
					{
						if (Pawn *pawn = dynamic_cast<Pawn *>(grid[i][j]))
						{
							if (pawn->hasEnPassant)
								undo.enPassantdPawn = pawn;
							pawn->hasEnPassant = false;
						}
					}
				}
			}

			// set has move
			if (Pawn *pawn = dynamic_cast<Pawn *>(selected_piece))
			{
				if (!pawn->hasMoved)
				{
					pawn->hasMoved = true;
					undo.wasFirstMove = true;
				}
				// set en passant flag
				if (std::abs(moveInfo.row - moveInfo.old_row) == 2)
				{
					pawn->hasEnPassant = true;
				}
				if (moveInfo.col != moveInfo.old_col && temp == nullptr)
				{
					undo.wasEnPassant = true;
					undo.capturedPiece = grid[moveInfo.old_row][moveInfo.col];
					grid[moveInfo.old_row][moveInfo.col] = nullptr;
				}
			}
			else if (Rook *rook = dynamic_cast<Rook *>(selected_piece))
			{
				if (!rook->hasMoved)
				{
					rook->hasMoved = true;
					undo.wasFirstMove = true;
				}
			}
			else if (King *king = dynamic_cast<King *>(selected_piece))
			{
				if (!king->hasMoved)
				{
					king->hasMoved = true;
					undo.wasFirstMove = true;
				}
				// check if we castled
				if (std::abs(moveInfo.col - moveInfo.old_col) == 2)
				{
					int rook_col = (moveInfo.col > moveInfo.old_col) ? 7 : 0;
					int new_rook_col = (moveInfo.col > moveInfo.old_col) ? moveInfo.col - 1 : moveInfo.col + 1;
					Rook *rook = dynamic_cast<Rook *>(grid[moveInfo.old_row][rook_col]);
					grid[moveInfo.old_row][new_rook_col] = rook;
					grid[moveInfo.old_row][rook_col] = nullptr;
					rook->hasMoved = true;
					undo.wasCastling = true;
					undo.castlingRook = rook;
				}
			}

			// check pawn promotion
			if (dynamic_cast<Pawn *>(selected_piece) != nullptr)
			{
				if (selected_piece->getIsWhite() && moveInfo.row == 0)
				{
					grid[moveInfo.row][moveInfo.col] = new Queen(true);
					undo.promotedPiece = grid[moveInfo.row][moveInfo.col];
				}
				else if (!selected_piece->getIsWhite() && moveInfo.row == 7)
				{
					grid[moveInfo.row][moveInfo.col] = new Queen(false);
					undo.promotedPiece = grid[moveInfo.row][moveInfo.col];
				}
			}

			selected_piece = nullptr;

			undoStack.push_back(undo);
			updateCheckStatus();
			return true;
		}
	}
	return false;
}
void Board::hasLegalMoves(bool *gameEnded)
{
	std::vector<t_moveInfo> whiteMoves = getAllLegalMoves(true);
	std::vector<t_moveInfo> blackMoves = getAllLegalMoves(false);

	if (whiteMoves.empty())
	{
		if (isWhiteKingInCheck)
			std::cout << "Black wins by checkmate!" << std::endl;
		else
			std::cout << "Stalemate! It's a draw!" << std::endl;
		*gameEnded = true;
	}
	else if (blackMoves.empty())
	{
		if (isBlackKingInCheck)
			std::cout << "White wins by checkmate!" << std::endl;
		else
			std::cout << "Stalemate! It's a draw!" << std::endl;
		*gameEnded = true;
	}
}

void Board::updateCheckStatus()
{
	// Find white king
	int white_king_row = -1, white_king_col = -1;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (grid[i][j] != nullptr && grid[i][j]->getIsWhite())
			{
				King *king = dynamic_cast<King *>(grid[i][j]);
				if (king != nullptr)
				{
					white_king_row = i;
					white_king_col = j;
					break;
				}
			}
		}
		if (white_king_row != -1)
			break;
	}

	// Find black king
	int black_king_row = -1, black_king_col = -1;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (grid[i][j] != nullptr && !grid[i][j]->getIsWhite())
			{
				King *king = dynamic_cast<King *>(grid[i][j]);
				if (king != nullptr)
				{
					black_king_row = i;
					black_king_col = j;
					break;
				}
			}
		}
		if (black_king_row != -1)
			break;
	}

	isWhiteKingInCheck = isKingCheck(white_king_row, white_king_col, true, grid);
	isBlackKingInCheck = isKingCheck(black_king_row, black_king_col, false, grid);
}

Board::Board()
{
	selected_piece = nullptr;
	start_col = -1;
	start_row = -1;
	end_col = -1;
	end_row = -1;

	// White pieces
	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			grid[0][0] = new Rook(false);
			grid[0][1] = new Knight(false);
			grid[0][2] = new Bishop(false);
			grid[0][3] = new King(false);
			grid[0][4] = new Queen(false);
			grid[0][5] = new Bishop(false);
			grid[0][6] = new Knight(false);
			grid[0][7] = new Rook(false);
		}
		if (i == 1)
		{
			for (auto &cell : grid[i])
			{
				cell = new Pawn(false);
			}
		}
	}

	for (int i = 6; i < 8; i++)
	{
		if (i == 6)
		{
			for (auto &cell : grid[i])
			{
				cell = new Pawn(true);
			}
		}
		else
		{
			grid[i][0] = new Rook(true);
			grid[i][1] = new Knight(true);
			grid[i][2] = new Bishop(true);
			grid[i][3] = new King(true);
			grid[i][4] = new Queen(true);
			grid[i][5] = new Bishop(true);
			grid[i][6] = new Knight(true);
			grid[i][7] = new Rook(true);
		}
	}
	std::cout << "Board created" << std::endl;
}

Board::~Board()
{
	for (auto &row : grid)
	{
		for (auto &cell : row)
		{
			delete cell;
		}
	}
	std::cout << "Board destroyed" << std::endl;
}

// This can be way more performant by just drawing a picture of a chess board.
// Reducing calls from 64 to 1 but idc
void Board::draw_squares(sf::RenderWindow &window)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (grid[i][j] == nullptr)
				continue;
			// if iam the king and in check draw a red square
			if (dynamic_cast<King *>(grid[i][j]) != nullptr)
			{
				if ((grid[i][j]->getIsWhite() && isWhiteKingInCheck) || (!grid[i][j]->getIsWhite() && isBlackKingInCheck))
				{
					sf::RectangleShape redSquare(sf::Vector2f(120, 120));
					redSquare.setFillColor(sf::Color(255, 0, 0, 100)); // Red with some transparency
					redSquare.setPosition(j * 120.f, i * 120.f);
					window.draw(redSquare);
				}
			}
			grid[i][j]->drawPiece(j, i, window);
		}
	}
}

void Board::gameloop()
{
	sf::RenderWindow window(sf::VideoMode(BOARD_SIZE, BOARD_SIZE), "BadChess");

	sf::Texture boardTex;
	sf::Sprite boardSprite;

	bool gameEnded = false;

	if (!boardTex.loadFromFile("sprites/board.png"))
		std::cerr << "failed to load the board" << std::endl;
	boardSprite.setTexture(boardTex);

	bool isWhiteTurn = true;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
			{
				undoLastMove();
				isWhiteTurn = !isWhiteTurn;
				break;
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				int col = event.mouseButton.x / 120.f;
				int row = event.mouseButton.y / 120.f;

				std::cout << col << " " << row << std::endl;

				// cancel the selectment
				if (selected_piece != nullptr && event.mouseButton.button == sf::Mouse::Right)
				{
					selected_piece = nullptr;
					break;
				}

				// if a piece is selected
				if (selected_piece != nullptr && selected_piece->getIsWhite() == isWhiteTurn)
				{
					if (col >= 0 && col < 8 && row >= 0 && row < 8)
					{
						t_moveInfo info = {start_row, start_col, col, row};
						if (makeMove(info))
						{
							isWhiteTurn = !isWhiteTurn;
							hasLegalMoves(&gameEnded);
						}
						break;
					}
				}
				selected_piece = grid[row][col];
				if (selected_piece == nullptr) // user pressed on an empty square
					break;
				else
				{
					start_col = col;
					start_row = row;
				}
			}
		}

		if (!isWhiteTurn && !gameEnded)
		{
			std::cout << "AI is thinking..." << std::endl;

			t_moveInfo bestMove = findBestMove(3, false);

			selected_piece = grid[bestMove.old_row][bestMove.old_col];
			makeMove(bestMove);
			isWhiteTurn = !isWhiteTurn;
			hasLegalMoves(&gameEnded);

			std::cout << "AI has made its move" << std::endl;
		}

		if (gameEnded)
		{
			window.close();
			std::cout << "Game ended" << std::endl;
		}

		window.clear(sf::Color::Black);

		// draw the piece we have (if we do)
		window.draw(boardSprite);
		draw_squares(window);
		if (hasPiece)
		{
			auto mousePos = sf::Mouse::getPosition(window);
			selected_piece->drawPiece(mousePos.x / 120.f, mousePos.y / 120.f, window);
		}
		window.display();
	}
}
