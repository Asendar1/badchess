#include "board.hpp"

Board::Board()
{
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
			grid[i][j]->drawPiece(j ,i , window);
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

			window.clear(sf::Color::Black);

			window.draw(boardSprite);
			draw_squares(window);

			window.display();
		}
	}
}
