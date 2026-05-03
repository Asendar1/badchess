#include "board.hpp"

#define hasPiece selected_piece != nullptr

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
			grid[i][j]->drawPiece(j, i, window);
		}
	}
}

void Board::gameloop()
{
	sf::RenderWindow window(sf::VideoMode(960, 960), "BadChess");

	sf::Texture boardTex;
	sf::Sprite boardSprite;

	if (!boardTex.loadFromFile("sprites/board.png"))
	{
		std::cerr << "failed to load the board" << std::endl;
	}
	boardSprite.setTexture(boardTex);

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
				if (selected_piece != nullptr)
				{
					if (col >= 0 && col < 8 && row >= 0 && row < 8)
					{
						t_moveInfo info = {start_row, start_col, col, row};
						if (selected_piece->checkValidAndMove(info, grid))
						{
							grid[row][col] = selected_piece;
							selected_piece = nullptr;
							grid[start_row][start_col] = nullptr;
							start_col = 0;
							start_row = 0;
						}
						break;
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

		// draw the peice we have (if we do)
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
