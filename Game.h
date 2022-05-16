/*
Julian Chow cchow11
Dhruv Dubey ddubey1
Fabio Fernandez ffernan9
*/

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Piece.h"
#include "Board.h"
#include "Exceptions.h"

namespace Chess
{

	class Game {

	public:
		// This default constructor initializes a board with the standard
		// piece positions, and sets the state to white's turn
		Game();

		// This copy constructor performs a deep copy of the current game state
		Game( const Game& game );

		// Returns true if it is white's turn
		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		bool turn_white() const { return is_white_turn; }
    
    	/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
    	// Displays the game by printing it to stdout
		void display() const { board.display(); }
    
    	/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
    	// Checks if the game is valid
		bool is_valid_game() const { return board.has_valid_kings(); }

		// Attempts to make a move. If successful, the move is made and
		// the turn is switched white <-> black. Otherwise, an exception is thrown
		void make_move(const Position& start, const Position& end);

		// helper function to check for make_move errors
		void make_move_errors(const Position& start, const Position& end) const;

		// Returns true if the designated player is in check
		bool in_check(const bool& white) const;

		// Returns true if the designated player is in mate
		bool in_mate(const bool& white) const;

		// Returns true if any move by piece in cur position can remove player from check
		bool stop_mate(const Position& cur, const bool& white) const;

		// Returns true if the designated player has no legal moves left
		bool in_stalemate(const bool& white) const;

		// Returns true if the piece in cur position can make any legal move
		bool stop_stale(const Position& cur, const bool& white) const;

		// helper to find the designated player's king on the board
		Position find_king(const bool& white) const;

        // Return the total material point value of the designated player
        int point_value(const bool& white) const;

		// Helper function checking whether start/end positions are on the board
		// Takes in start and end positions as input; returns 1 if start position
		// not on board, 2 if end position not on board, and 0 if in bounds.
		int in_bounds(const Position& start, const Position& end) const;


	private:
		// The board
		Board board;

		// Is it white's turn?
		bool is_white_turn;

        // Writes the board out to a stream
        friend std::ostream& operator<< (std::ostream& os, const Game& game);

        // Reads the board in from a stream
        friend std::istream& operator>> (std::istream& is, Game& game);
	};
}
#endif // GAME_H
