#include "board.hpp"

int isKingCheck(int king_row, int king_col, bool isWhite, std::array<std::array<Piece *, 8>, 8> &grid);

#define hasPiece selected_piece != nullptr

void Board::hasLegalMoves(bool *gameEnded)
{
	// find both kings
	// see if they have any legal moves
	// if they don't and are checked then checkmate, otherwise stalemate
	int white_king_row = -1, white_king_col = -1;
	int black_king_row = -1, black_king_col = -1;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (grid[i][j] != nullptr)
			{
				if (King *temp = dynamic_cast<King *>(grid[i][j]))
				{
					if (temp->getIsWhite())
					{
						white_king_row = i;
						white_king_col = j;
					}
					else
					{
						black_king_row = i;
						black_king_col = j;
					}
				}
			}
			if (white_king_row != -1 && black_king_row != -1)
				break;
		}
	}

	// see if white or black can move
	bool whiteHasMoves = false, blackHasMoves = false;
	for (int s_row = 0; s_row < 8; s_row++)
	{
		for (int s_col = 0; s_col < 8; s_col++)
		{
			if (grid[s_row][s_col] != nullptr)
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

							if (grid[e_row][e_col]->getIsWhite())
							{
								int check_row = (dynamic_cast<King *>(grid[e_row][e_col]) != nullptr) ? e_row : white_king_row;
								int check_col = (dynamic_cast<King *>(grid[e_row][e_col]) != nullptr) ? e_col : white_king_col;
								if (!isKingCheck(check_row, check_col, true, grid))
									whiteHasMoves = true;
							}
							else
							{
								int check_row = (dynamic_cast<King *>(grid[e_row][e_col]) != nullptr) ? e_row : black_king_row;
								int check_col = (dynamic_cast<King *>(grid[e_row][e_col]) != nullptr) ? e_col : black_king_col;
								if (!isKingCheck(check_row, check_col, false, grid))
									blackHasMoves = true;
							}
							grid[s_row][s_col] = grid[e_row][e_col];
							grid[e_row][e_col] = temp;
						}
					}
				}
			}
		}
	}
	if (!whiteHasMoves)
	{
		if (isWhiteKingInCheck)
			std::cout << "Black wins by checkmate!" << std::endl;
		else
			std::cout << "Stalemate! It's a draw!" << std::endl;
		*gameEnded = true;
	}
	else if (!blackHasMoves)
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
	{
		std::cerr << "failed to load the board" << std::endl;
	}
	boardSprite.setTexture(boardTex);

	bool isWhiteTurn = true;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

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
						if (selected_piece->checkValidAndMove(info, grid))
						{
							Piece *temp = grid[info.row][info.col];
							grid[row][col] = selected_piece;
							grid[start_row][start_col] = nullptr;

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
								grid[row][col] = temp;
								grid[start_row][start_col] = selected_piece;
							}
							else
							{
								// legal
								delete temp;
								start_col = 0;
								start_row = 0;
								isWhiteTurn = !isWhiteTurn;

								// set has move
								if (Pawn *pawn = dynamic_cast<Pawn *>(selected_piece))
								{
									pawn->hasMoved = true;
								}
								else if (Rook *rook = dynamic_cast<Rook *>(selected_piece))
								{
									rook->hasMoved = true;
								}
								else if (King *king = dynamic_cast<King *>(selected_piece))
								{
									king->hasMoved = true;
								}

								// check pawn promotion
								if (dynamic_cast<Pawn *>(selected_piece) != nullptr)
								{
									if (selected_piece->getIsWhite() && row == 0)
									{
										delete selected_piece;
										grid[row][col] = new Queen(true);
									}
									else if (!selected_piece->getIsWhite() && row == 7)
									{
										delete selected_piece;
										grid[row][col] = new Queen(false);
									}
								}
								selected_piece = nullptr;

								updateCheckStatus();
								hasLegalMoves(&gameEnded);
							}
							break;
						}
					}
				}

				selected_piece = grid[row][col];
				if (selected_piece == nullptr)
				{
					std::cout << "Nothing seleceted" << std::endl;
				} // user pressed on an empty square
				else
				{
					start_col = col;
					start_row = row;
				}
			}
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

		if (gameEnded)
		{
			window.close();
			std::cout << "Game ended" << std::endl;
		}
	}
}
