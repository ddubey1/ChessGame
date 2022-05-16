/*
Julian Chow cchow11
Dhruv Dubey ddubey1
Fabio Fernandez ffernan9
*/

#include <algorithm>
#include <cassert>
#include "Board.h"
#include "Exceptions.h"
#include "Game.h"
#include "Piece.h"
#include <cctype>
#include <ostream>

namespace Chess
{
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Game::Game() : is_white_turn(true) {
		// Add the pawns
		for (int i = 0; i < 8; i++) {
			board.add_piece(Position('A' + i, '1' + 1), 'P');
			board.add_piece(Position('A' + i, '1' + 6), 'p');
		}

		// Add the rooks
		board.add_piece(Position( 'A'+0 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+7 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+0 , '1'+7 ) , 'r' );
		board.add_piece(Position( 'A'+7 , '1'+7 ) , 'r' );

		// Add the knights
		board.add_piece(Position( 'A'+1 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+6 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+1 , '1'+7 ) , 'n' );
		board.add_piece(Position( 'A'+6 , '1'+7 ) , 'n' );

		// Add the bishops
		board.add_piece(Position( 'A'+2 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+5 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+2 , '1'+7 ) , 'b' );
		board.add_piece(Position( 'A'+5 , '1'+7 ) , 'b' );

		// Add the kings and queens
		board.add_piece(Position( 'A'+3 , '1'+0 ) , 'Q' );
		board.add_piece(Position( 'A'+4 , '1'+0 ) , 'K' );
		board.add_piece(Position( 'A'+3 , '1'+7 ) , 'q' );
		board.add_piece(Position( 'A'+4 , '1'+7 ) , 'k' );
	}


	Game::Game( const Game& game ) {

		this->is_white_turn = game.turn_white();
		char curr_pc;
    	for (char c = 'A'; c <= 'H'; c++) {
    	  	for (char r = '1'; r <= '8'; r++) {
				if (game.board({c, r}) == nullptr) continue;
    	  	  	curr_pc = game.board({c, r})->to_ascii();
    	  	  	this->board.add_piece({c, r}, curr_pc);
    	  	}
    	}
	}
	
	
	int Game::in_bounds(const Position& start, const Position& end) const {
		
		// check start position in bounds
		if (!(start.first >= 'A' && start.second >= '1') &&
			!(start.first <= 'H' && start.second <= '8')) {
			
			return 1;
		}

		// check end position in bounds
		if (!(end.first >= 'A' && end.second >= '1') &&
			!(end.first <= 'H' && end.second <= '8')) {
			
			return 2;
		}

		// if reached, in bounds
		return 0;
	}


	void Game::make_move(const Position& start, const Position& end) {
		// use helper function
		make_move_errors(start, end);

		// checks if white piece is moving on black turn or vice-versa
		if( (is_white_turn && !board(start)->is_white()) || (!is_white_turn && board(start)->is_white()) ) {
			throw Exception("piece color and turn do not match");
		}

		// check if move causes own king to be in check
		Game tmp( *this );
		delete tmp.board(end);
		tmp.board.add_piece(end, tmp.board(start)->to_ascii());
		delete tmp.board(start);
		tmp.board.add_piece(start, '-');
		if (tmp.in_check(tmp.turn_white()))	throw Exception("move exposes check");

		// white pawn
		if((board(start)->to_ascii() == 'P') && (end.second == '8')) {
			delete board(start);
			board.add_piece(start, 'Q');
		}
		// black pawn
		if((board(start)->to_ascii() == 'p') && (end.second == '1')) {
			delete board(start);			
			board.add_piece(start, 'q');
		}

		// make move or capture
		delete board(end);
		board.add_piece(end, board(start)->to_ascii());
		delete board(start);
		board.add_piece(start, '-');

		// switching player from black to white
		is_white_turn = !is_white_turn;
	}


	void Game::make_move_errors(const Position& start, const Position& end) const {
		// checks if start/end position not on board
		int check = in_bounds(start, end);

    	// check start position in bounds
    	if (check == 1) {
      		throw Exception("start position is not on board");
    	}

    	// check end position in bounds
    	else if (check == 2) {
      		throw Exception("end position is not on board");
    	}
		
		const Piece* curr_pc = board(start);
		const Piece* end_pc = board(end);

		// check start has a piece
		if (curr_pc == nullptr) throw Exception("no piece at start position");

		// move is capture another piece
		if (end_pc != nullptr) {
			if (curr_pc->is_white() == end_pc->is_white() || !curr_pc->is_white() == !end_pc->is_white()) {
				throw Exception("cannot capture own piece");
			}
			// checks if legal capture shape
			curr_pc->legal_capture_shape(start, end);
		}

		// move is moving the piece to empty tile
		else {
			curr_pc->legal_move_shape(start, end);
		}

		// checking paths 
		int col_offset = end.first - start.first;
		int row_offset = end.second - start.second;
		int unit_col = col_offset;
		(unit_col != 0) ? (unit_col /= abs(col_offset)) : 0 ;
		int unit_row = row_offset;
		(unit_row != 0) ? (unit_row /= abs(row_offset)) : 0 ;


		Position c_pos = start; // current position 

		// check paths for moves in a straight line
		if (col_offset == row_offset || col_offset == -row_offset || col_offset == 0 || row_offset == 0) {
			while (c_pos.first != end.first || c_pos.second != end.second) {
				c_pos.first += unit_col;
				c_pos.second += unit_row;
				
				// if we are at the end position, break
				if (c_pos.first == end.first && c_pos.second == end.second) break;

				// if there is a piece at the position along the path, but we are not capturing, throw Exception
				if (board(c_pos) != nullptr) {
					throw Exception("path is not clear");
					break;
				}
			}
		}
	}


	bool Game::in_check(const bool& white) const {
		
		// look for own king
		Position king = find_king(white);

		// look for opponent's pieces and see if they can reach the king 
		for(char r = '8'; r >= '1'; r--) {
      		for(char c = 'A'; c <= 'H'; c++) {
				if (board({c,r}) == nullptr) {
					continue;
				}

				else if (board({c,r})->is_white() != white) {
					try {
						make_move_errors({c,r}, king);
						return true;
					}
					catch (Exception& e) {
						continue;
					}	
					
				}
				
			}
		}
		return false;
		
	}	


	bool Game::in_mate(const bool& white) const {

		if (!in_check(white)) return false;

		// loop through board and run stop_mate helper function
		for (char c = 'A'; c <= 'H'; c++) {
			for (char r = '8'; r >= '1'; r--) {
				if (stop_mate({c, r}, white)) return false;
			}
		}

		return true;
	}


	bool Game::stop_mate(const Position& cur, const bool& white) const {

		// return if cur position has no piece
		if (board(cur) == nullptr) return false;
		// return if cur piece is not yours
		if (board(cur)->is_white() != white) return false;

		for (char c = 'A'; c <= 'H'; c++) {
			for (char r = '8'; r >= '1'; r--) {
				try {
					Game tmp( *this );
					tmp.make_move(cur, {c, r});
					if (!tmp.in_check(white)) {
						return true;
					}
				} catch (Exception& e) {
					continue;
				}
			}
		}
		// if reached, piece at cur cannot get player out of check
		return false;
	}


	bool Game::in_stalemate(const bool& white) const {
		
		// check if any one of a player's pieces can make a legal move
		for (char c = 'A'; c <= 'H'; c++) {
			for (char r = '8'; r >= '1'; r--) {
				if (stop_stale({c, r}, white)) return false;
			}
		}
		return true;
	}


	bool Game::stop_stale(const Position& cur, const bool& white) const {

		// return if cur position has no piece
		if (board(cur) == nullptr) return false;
		// return if cur piece is not yours
		if (board(cur)->is_white() != white) return false;

		for (char c = 'A'; c <= 'H'; c++) {
			for (char r = '8'; r >= '1'; r--) {
				try {
					Game tmp( *this );
					tmp.make_move(cur, {c, r});
					// if reached, there is a legal move
					return true;
				} catch (Exception& e) {
					continue;
				}
			}
		}
		// if reached, piece at cur cannot get player out of check
		return false;
	}


	Position Game::find_king(const bool& white) const {
		Position king = {'A', '8'};
		for (char r = '8'; r >= '1'; r--) {
      		for (char c = 'A'; c <= 'H'; c++) {
				if (board({c, r}) == nullptr) continue;
				char curr = board({c, r})->to_ascii();
				if (std::toupper(curr) == 'K' && board({c, r})->is_white() == white) {
					king = {c,r};
				}
			}
		}
		return king;
	}

    
    int Game::point_value(const bool& white) const {
		int total = 0;
		
		for (char c ='A'; c <= 'H'; c++) {
			for (char i = '1'; i <= '8'; i++) {
				const Piece* curr_pc = board({c, i});
				// for each piece, add its point_value to the total.
				if(white) {
					if (curr_pc != nullptr && curr_pc->is_white()) {
						total += curr_pc->point_value();
					}
				}
				else {
					if (curr_pc != nullptr && !curr_pc->is_white()) {
						total += curr_pc->point_value();
					}
				}
			}
		}


        return total;
    }


    std::istream& operator>> (std::istream& is, Game& game) {
		char cur;
		for (char r = '8'; r >= '1'; r--) {
			for (char c = 'A'; c <= 'H'; c++) {
				// throw exception if stream ends before covering entire board
				if (!is.get(cur)) throw Chess::Exception("Cannot load the game!");

				if (game.board({c, r}) != nullptr) delete game.board({c, r});
				game.board.add_piece({c, r}, cur);
			}
			// take in newline
			if(is.get(cur) && cur == '\n') continue;
			else throw Exception("Cannot load the game!");
		}

		// check last character exists to set player turn
		if(!is.get(cur)) throw Chess::Exception("Cannot load the game!");

		else {
			switch (cur) {
				case 'w': game.is_white_turn = true; break;
				case 'b': game.is_white_turn = false; break;
				
				// invalid player turn character
				default : throw Chess::Exception("Cannot load the game!");
			}
		}
		
		return is;
	}

    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
	std::ostream& operator<< (std::ostream& os, const Game& game) {
		// Write the board out and then either the character 'w' or the character 'b',
		// depending on whose turn it is
		return os << game.board << (game.turn_white() ? 'w' : 'b');
	}
}
