/*
Julian Chow cchow11
Dhruv Dubey ddubey1
Fabio Fernandez ffernan9
*/

#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

namespace Chess
{
	class Pawn : public Piece {

	public:
		bool legal_move_shape(const Position& start, const Position& end) const override;
    
		bool legal_capture_shape(const Position& start, const Position& end) const override;

		// return the points for this piece
		int point_value() const override { return 1; }

		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		char to_ascii() const override { return is_white() ? 'P' : 'p';	}
    
		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		std::string to_unicode() const override { return is_white() ? "\u2659" : "\u265F"; }

	private:
		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		Pawn(bool is_white) : Piece(is_white) {}

		friend Piece* create_piece(const char& piece_designator);
	};
}
#endif // PAWN_H
