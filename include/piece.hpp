#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

typedef struct s_moveInfo
{
	int old_row;
	int old_col;
	int col;
	int row;
} t_moveInfo;

class Piece
{

protected:
	sf::Sprite image;
	bool isWhite;

public:
	Piece(bool isWhite) : isWhite(isWhite) {}
	virtual ~Piece() = default;
	void virtual drawPiece(float x, float y, sf::RenderWindow &window);
	int virtual checkValidAndMove(t_moveInfo &moveInfo, std::array<std::array<Piece *, 8>, 8> &grid);

	bool getIsWhite() { return isWhite; }
};

class Pawn : public Piece
{
private:
	bool hasMoved;
	sf::Texture tex;

public:
	Pawn(bool isWhite) : Piece(isWhite), hasMoved(false)
	{

		if (!isWhite)
		{
			if (!tex.loadFromFile("sprites/black_pawn.png"))
			{
				std::cerr << "Failed to load pawn image" << std::endl;
			}
			image.setTexture(tex);
		}
		else
		{
			if (!tex.loadFromFile("sprites/white_pawn.png"))
			{
				std::cerr << "Failed to load pawn image" << std::endl;
			}
			image.setTexture(tex);
		}
	}
	~Pawn() = default;
	void virtual drawPiece(float x, float y, sf::RenderWindow &window) override;
	int virtual checkValidAndMove(t_moveInfo &moveInfo, std::array<std::array<Piece *, 8>, 8> &grid) override;
};

class Rook : public Piece
{
private:
	bool hasMoved;
	sf::Texture tex;

public:
	Rook(bool isWhite) : Piece(isWhite), hasMoved(false)
	{
		if (!isWhite)
		{
			if (!tex.loadFromFile("sprites/black_rook.png"))
			{
				std::cerr << "Failed to load rook image" << std::endl;
			}
			image.setTexture(tex);
		}
		else
		{
			if (!tex.loadFromFile("sprites/white_rook.png"))
			{
				std::cerr << "Failed to load rook image" << std::endl;
			}
			image.setTexture(tex);
		}
	}
	~Rook() = default;
	void virtual drawPiece(float x, float y, sf::RenderWindow &window) override;
	int virtual checkValidAndMove(t_moveInfo &moveInfo, std::array<std::array<Piece *, 8>, 8> &grid) override;
};

class Knight : public Piece
{
private:
	sf::Texture tex;

public:
	Knight(bool isWhite) : Piece(isWhite)
	{
		if (!isWhite)
		{
			if (!tex.loadFromFile("sprites/black_knight.png"))
			{
				std::cerr << "Failed to load knight image" << std::endl;
			}
			image.setTexture(tex);
		}
		else
		{
			if (!tex.loadFromFile("sprites/white_knight.png"))
			{
				std::cerr << "Failed to load knight image" << std::endl;
			}
			image.setTexture(tex);
		}
	}
	~Knight() = default;

	void virtual drawPiece(float x, float y, sf::RenderWindow &window) override;
	int virtual checkValidAndMove(t_moveInfo &moveInfo, std::array<std::array<Piece *, 8>, 8> &grid) override;
};

class Bishop : public Piece
{
private:
	sf::Texture tex;

public:
	Bishop(bool isWhite) : Piece(isWhite)
	{
		if (!isWhite)
		{
			if (!tex.loadFromFile("sprites/black_bishop.png"))
			{
				std::cerr << "Failed to load bishop image" << std::endl;
			}
			image.setTexture(tex);
		}
		else
		{
			if (!tex.loadFromFile("sprites/white_bishop.png"))
			{
				std::cerr << "Failed to load bishop image" << std::endl;
			}
			image.setTexture(tex);
		}
	}
	~Bishop() = default;
	void virtual drawPiece(float x, float y, sf::RenderWindow &window) override;
	int virtual checkValidAndMove(t_moveInfo &moveInfo, std::array<std::array<Piece *, 8>, 8> &grid) override;
};

class Queen : public Piece
{
private:
	sf::Texture tex;

public:
	Queen(bool isWhite) : Piece(isWhite)
	{
		if (!isWhite)
		{
			if (!tex.loadFromFile("sprites/black_queen.png"))
			{
				std::cerr << "Failed to load queen image" << std::endl;
			}
			image.setTexture(tex);
		}
		else
		{
			if (!tex.loadFromFile("sprites/white_queen.png"))
			{
				std::cerr << "Failed to load queen image" << std::endl;
			}
			image.setTexture(tex);
		}
	}
	~Queen() = default;
	void virtual drawPiece(float x, float y, sf::RenderWindow &window) override;
	int virtual checkValidAndMove(t_moveInfo &moveInfo, std::array<std::array<Piece *, 8>, 8> &grid) override;
};

class King : public Piece
{
private:
	bool hasMoved;
	sf::Texture tex;

public:
	King(bool isWhite) : Piece(isWhite), hasMoved(false)
	{
		if (!isWhite)
		{
			if (!tex.loadFromFile("sprites/black_king.png"))
			{
				std::cerr << "Failed to load king image" << std::endl;
			}
			image.setTexture(tex);
		}
		else
		{
			if (!tex.loadFromFile("sprites/white_king.png"))
			{
				std::cerr << "Failed to load king image" << std::endl;
			}
			image.setTexture(tex);
		}
	}
	~King() = default;
	void virtual drawPiece(float x, float y, sf::RenderWindow &window) override;
	int virtual checkValidAndMove(t_moveInfo &moveInfo, std::array<std::array<Piece *, 8>, 8> &grid) override;
};
