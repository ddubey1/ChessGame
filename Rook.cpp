/*
Julian Chow cchow11
Dhruv Dubey ddubey1
Fabio Fernandez ffernan9
*/

#include "Rook.h"
#include "Exceptions.h"

namespace Chess
{
  bool Rook::legal_move_shape(const Position& start, const Position& end) const {

    // offset in letters
    const unsigned int ltrOff = abs(end.first - start.first);

    // offset in numbers
    const unsigned int numOff = abs(end.second - start.second);

    // check move is along diagonals (legal)
    if(!(numOff == 0 || ltrOff == 0)) {
      throw Exception("illegal move shape");
    }

    // if reached, move is legal and in bounds
    return true;
  }

  bool Rook::legal_capture_shape(const Position &start, const Position &end) const {
    
    // offset in letters
    const unsigned int ltrOff = abs(end.first - start.first);

    // offset in numbers
    const unsigned int numOff = abs(end.second - start.second);

    // check move is along diagonals (legal)
    if(!(numOff == 0 || ltrOff == 0)) {
      throw Exception("illegal capture shape");
    }

    // if reached, move is legal and in bounds
    return true;
  }
}
