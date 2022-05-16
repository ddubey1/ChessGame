/*
Julian Chow cchow11
Dhruv Dubey ddubey1
Fabio Fernandez ffernan9
*/

#include "Knight.h"
#include "Exceptions.h"
#include <iostream>

namespace Chess
{
  bool Knight::legal_move_shape(const Position& start, const Position& end) const {

    // offset in letters
    const unsigned int ltrOff = abs(end.first - start.first);

    // offset in numbers
    const unsigned int numOff = abs(end.second - start.second);

    // check move is L-shape (legal)
    if (!(ltrOff > 0 && numOff > 0 && ltrOff + numOff == 3)) {
      throw Exception("illegal move shape");
    }

    // if reached, move is legal and in bounds
    return true;
  }

  bool Knight::legal_capture_shape(const Position &start, const Position &end) const {

    // offset in letters
    const unsigned int ltrOff = abs(end.first - start.first);

    // offset in numbers
    const unsigned int numOff = abs(end.second - start.second);

    // check capture is L-shape (legal)
    if (!(ltrOff > 0 && numOff > 0 && ltrOff + numOff == 3)) {
      throw Exception("illegal capture shape");
    }

    // if reached, move is legal and in bounds
    return true;
  }
}
