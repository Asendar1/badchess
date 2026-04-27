#include "board.hpp"
#include <SFML/Graphics.hpp>

Board::Board()
{
	std::cout << "Board created" << std::endl;
}

void Board::draw_squares(sf::RenderWindow& window)
{
	sf::RectangleShape square(sf::Vector2f(100.f, 100.f));

	for (int i = 0; i < 8; i++)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j < 8; j++)
			{
				
			}
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
