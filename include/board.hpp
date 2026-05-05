#pragma once

#include "piece.hpp"

#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

class Board
{
private:
	Piece *selected_piece;
	int start_col;
	int start_row;
	int end_col;
	int end_row;
	bool isWhiteKingInCheck;
	bool isBlackKingInCheck;

private:
	std::array<std::array<Piece *, 8>, 8> grid{};

	void draw_squares(sf::RenderWindow &window);
	void updateCheckStatus();

public:
	Board();
	~Board();

	void gameloop();
};
