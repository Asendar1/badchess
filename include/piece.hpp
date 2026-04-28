#include <SFML/Graphics.hpp>
#include <iostream>

class Piece
{
	protected:
		sf::Sprite	image;
		bool		isWhite;

	public:
		Piece(bool isWhite) : isWhite(isWhite) {}
		virtual ~Piece() = default;
		void drawPiece(float x, float y, sf::RenderWindow &window);
};

class Pawn : public Piece
{
	private:
		bool hasMoved;
		sf::Texture tex;

	public:
		Pawn(bool isWhite) : Piece(isWhite), hasMoved(false)
		{

			if(!tex.loadFromFile("sprites/black_pawn.png") && !isWhite)
			{
				std::cerr << "Failed to load pawn image" << std::endl;
			}
			image.setTexture(tex);
		}
		~Pawn() = default;
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
	public:
		Knight(bool isWhite) : Piece(isWhite) {}
		~Knight() = default;
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
