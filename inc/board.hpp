// -----------------------------------------------------------------------------

#ifndef __BOARD_HPP
#define __BOARD_HPP

// -----------------------------------------------------------------------------

#include "polyhedron.hpp"

// -----------------------------------------------------------------------------

class Board : public Polyhedron{
protected:
  void generate_vertex(int num_squares);
  void generate_faces(int num_squares);
  void calc_texture_vertex(int num_squares);

public:
  Board();

  void generate_board(int num_squares);
};

// -----------------------------------------------------------------------------

#endif
