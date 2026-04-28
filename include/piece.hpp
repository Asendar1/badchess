#include <SFML/Graphics.hpp>
#include <iostream>

class Piece
{
protected:
	sf::Sprite image;
	bool isWhite;

public:
	Piece(bool isWhite) : isWhite(isWhite) {}
	virtual ~Piece() = default;
	void virtual drawPiece(float x, float y, sf::RenderWindow &window);
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
};

class Rook : public Piece
{
private:
	bool hasMoved;

public:
	Rook(bool isWhite) : Piece(isWhite), hasMoved(false) {}
	~Rook() = default;
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
};

class Bishop : public Piece
{
public:
	Bishop(bool isWhite) : Piece(isWhite) {}
	~Bishop() = default;
};

class Queen : public Piece
{
public:
	Queen(bool isWhite) : Piece(isWhite) {}
	~Queen() = default;
};

class King : public Piece
{
private:
	bool hasMoved;

public:
	King(bool isWhite) : Piece(isWhite), hasMoved(false) {}
	~King() = default;
};
