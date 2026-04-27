#pragma once

#include "piece.hpp"

#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

class Board
{
	private:
		std::array<std::array<Piece *, 8>, 8> grid;

		void draw_squares(sf::RenderWindow& window);
	public:
		Board();
		~Board();

		void gameloop();
};
