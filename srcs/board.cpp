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
			for (auto &cell: grid[i])
			{
				cell = new Pawn(false);
			}
		}
	}

	for (int i = 6; i < 8; i++)
	{
		if (i == 6)
		{
			for (auto &cell: grid[i])
			{
				cell = new Pawn(false);
			}
		}
		else
		{
			grid[i][0] = new Rook(false);
			grid[i][1] = new Knight(false);
			grid[i][2] = new Bishop(false);
			grid[i][3] = new King(false);
			grid[i][4] = new Queen(false);
			grid[i][5] = new Bishop(false);
			grid[i][6] = new Knight(false);
			grid[i][7] = new Rook(false);
		}
	}
	std::cout << "Board created" << std::endl;
}

Board::~Board()
{
	for (auto &row: grid)
	{
		for (auto &cell: row)
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
	sf::RectangleShape square(sf::Vector2f(100.f, 100.f));

	// brown rgb(222,184,135)
	sf::Color brownColor(222, 184, 135);
	square.setFillColor(brownColor);

	for (int i = 0; i < 8; i++)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j * 100 < 800; j++)
			{
				if (j % 2 == 0)
				{
					square.setPosition(j * 100.f, i * 100.f);
					window.draw(square);
				}
			}
		}
		else
		{
			for (int j = 0; j * 100 < 800; j++)
			{
				if (j % 2 == 1)
				{
					square.setPosition(j * 100.f, i * 100.f);
					window.draw(square);
				}
			}
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (grid[i][j] == nullptr) continue;
			grid[i][j]->drawPiece(j * 100, i * 100, window);
		}
	}
}

void Board::gameloop()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "BadChess");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			window.clear(sf::Color::Black);

			draw_squares(window);

			window.display();
		}
	}
}
