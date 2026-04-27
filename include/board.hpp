#include <iostream>

class sf::RenderWindow;

class Board
{
	private:
		void draw_squares(sf::RenderWindow& window);
	public:
		Board();
		~Board() = default;

		void gameloop();
};
