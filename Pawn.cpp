/*
Julian Chow cchow11
Dhruv Dubey ddubey1
Fabio Fernandez ffernan9
*/

#include "Pawn.h"
#include "Exceptions.h"
#include <iostream>

namespace Chess
{
  bool Pawn::legal_move_shape(const Position& start, const Position& end) const {

    // offset in letters
    const int ltrOff = abs(end.first - start.first);

    // offset in numbers
    const int numOff = end.second - start.second;

    // check move is one space or two space (in bound)
    if (ltrOff == 0) {
      if((numOff == 1 && is_white()) || (numOff == -1 && !is_white())) {
        return true;
      }
      else if ( numOff == 2 || numOff == -2 ) {
        if(is_white() == true && start.second == '2'){
          return true;
        }
        if(is_white() == false && start.second == '7'){
          return true;
        }
      }
    }

    // if not in bound, throw exception
    throw Exception("illegal move shape");
  }

  bool Pawn::legal_capture_shape(const Position &start, const Position &end) const {
    
    // offset in letters
    const unsigned int ltrOff = abs(end.first - start.first);

    // offset in numbers
    const int numOff = end.second - start.second;

    // check move is one space or two space (in bound)
    if (ltrOff == 1) {
      if((numOff == 1 && is_white()) || (numOff == -1 && !is_white())) {
        return true;
      }
    }

    // if not in bound, throw exception
    throw Exception("illegal capture shape");
  }

}
