/*
Julian Chow cchow11
Dhruv Dubey ddubey1
Fabio Fernandez ffernan9
*/

#include "Bishop.h"
#include "Exceptions.h"
#include <algorithm>
#include <string>

namespace Chess
{
  bool Bishop::legal_move_shape(const Position& start, const Position& end) const {

    // offset in letters
    const unsigned int ltrOff = abs(end.first - start.first);

    // offset in numbers
    const unsigned int numOff = abs(end.second - start.second);

    // check move is along diagonals (legal)
    if (ltrOff != numOff) {
      throw Exception("illegal move shape");
    }

    // if reached, move is legal and in bounds
    return true;
  }

  bool Bishop::legal_capture_shape(const Position &start, const Position &end) const {

    // offset in letters
    const unsigned int ltrOff = abs(end.first - start.first);

    // offset in numbers
    const unsigned int numOff = abs(end.second - start.second);

    // check move is along diagonals (legal)
    if (ltrOff != numOff) {
      throw Exception("illegal capture shape");
    }

    // if reached, move is legal and in bounds
    return true;
  }


}
