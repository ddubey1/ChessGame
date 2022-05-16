/*
Julian Chow cchow11
Dhruv Dubey ddubey1
Fabio Fernandez ffernan9
*/

#include "King.h"
#include "Exceptions.h"

namespace Chess
{
  bool King::legal_move_shape(const Position& start, const Position& end) const {
    
    // max offset in any direction must be 1
    const unsigned int maxOff = std::max(abs(end.first - start.first), abs(end.second - start.second));

    // check move is 1 in any direction (legal)
    if (maxOff != 1) {
      throw Exception("illegal move shape");
    }

    // if reached, move is legal and in bounds
    return true;
  }

  bool King::legal_capture_shape(const Position &start, const Position &end) const {
    
    // max offset in any direction must be 1
    const unsigned int maxOff = std::max(abs(end.first - start.first), abs(end.second - start.second));

    // check move is 1 in any direction (legal)
    if (maxOff != 1) {
      throw Exception("illegal capture shape");
    }

    // if reached, move is legal and in bounds
    return true;
  }
}
