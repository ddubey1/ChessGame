/*
Julian Chow cchow11
Dhruv Dubey ddubey1
Fabio Fernandez ffernan9
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <map>
#include <vector>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"
#include "Exceptions.h"

namespace Chess
{
 
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Board::Board(){}

  Board::Board(const Board& brd) {
    char curr_pc;
    for (char c = 'A'; c <= 'H'; c++) {
      for (char r = '1'; r <= '8'; r++) {
        curr_pc = brd({c, r})->to_ascii();
        this->add_piece({c, r}, curr_pc);
      }
    }
  }

  Board::~Board() {
    for (char c = 'A'; c <= 'H'; c++) {
      for (char r = '1'; r <= '8'; r++) {
        delete occ[{c, r}];
      }
    }
  }

  const Piece* Board::operator()(const Position& position) const {
    // returns value at position in occ map
    // value can either be a Piece* or nullptr depending on key
    if (occ.count(position) == 0) return nullptr;
    else return occ.at(position);
  }
  
  void Board::add_piece(const Position& position, const char& piece_designator) {

    // check if position is in bound
    if (!(position.first >= 'A' && position.second >= '1') &&
    		!(position.first <= 'H' && position.second <= '8')) {
				
      throw Exception("invalid position");
    }

    // discard piece from board
    if (piece_designator == '-') {
      occ.erase(position);
      return;
    }

    std::vector<char> valid_desig{'K','k','Q','q','B','b','N','n','R','r','P','p','M','m'};

    if (std::find(valid_desig.begin(), valid_desig.end(), piece_designator) == valid_desig.end()) {
      throw Exception("invalid designator");
    }

    occ[position] = create_piece(piece_designator);
  }

  void Board::display() const {
    // print out first line of A-H
    std::cout << "  ";
    for (char i = 'A'; i <= 'H'; i++) {
      std::cout << i;
    }
    std::cout << std::endl << "  ";

    // print out first line of "-" (dashes)
    for (char i = 'A'; i <= 'H'; i++) {
      std::cout << "-";
    }
    std::cout << std::endl;

    // loop through board and display board/pieces
    for(char r = '8'; r >= '1'; r--) {
      std::cout << r << "|";
      for(char c = 'A'; c <= 'H'; c++) {
        // check colour of tile and piece
        bool tile_is_white = (c+r) % 2;

        // check whether piece exists
        occIterator it = occ.find({c, r});

        // display based on colours of tiles/pieces
	      if (it != occ.cend()) {
	        if (tile_is_white && it->second->is_white()) {
            Terminal::color_all(1, Terminal::WHITE, Terminal::CYAN);
            std::cout << it->second->to_unicode(); 
          } 

          else if (!tile_is_white && it->second->is_white()) {
            Terminal::color_all(1, Terminal::WHITE, Terminal::BLACK);
            std::cout << it->second->to_unicode(); 
          }

          else if (tile_is_white && !it->second->is_white()) {
            Terminal::color_all(1, Terminal::BLACK, Terminal::CYAN);
            std::cout << it->second->to_unicode(); 
          }

          else if (!tile_is_white && !it->second->is_white()) {
            Terminal::color_all(1, Terminal::BLACK, Terminal::BLACK);
            std::cout << it->second->to_unicode(); 
          }

	      } 

        // everything after this displays blank board, and is correct
        else {
          if (tile_is_white) {
            Terminal::color_bg(Terminal::CYAN);
            std::cout << " ";
          }
          else {
            Terminal::color_bg(Terminal::BLACK);
            std::cout << " ";
          }
	      }

        // reset colour
        Terminal::set_default();
      }

      std::cout << "|" << r;
      std::cout << std::endl;
    }

    // print out last line of "-" (dashes)
    std::cout << "  ";
    for (char i = 'A'; i <= 'H'; i++) {
      std::cout << "-";
    }
    std::cout << std::endl;

    // print out last line of A-H
    std::cout << "  ";
    for (char i = 'A'; i <= 'H'; i++) {
      std::cout << i;
    }
    std::cout << std::endl;
    
  }


  bool Board::has_valid_kings() const {
    int white_king_count = 0;
    int black_king_count = 0;
    for (std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.begin();
	 it != occ.end();
	 it++) {
      if (it->second) {
	      switch (it->second->to_ascii()) {
	        case 'K':
	          white_king_count++;
	          break;
	        case 'k':
	          black_king_count++;
	          break;
	      }
      }
    }
    return (white_king_count == 1) && (black_king_count == 1);
  }

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
	const Piece* piece = board(Position(c, r));
	if (piece) {
	  os << piece->to_ascii();
	} else {
	  os << '-';
	}
      }
      os << std::endl;
    }
    return os;
  }
}
