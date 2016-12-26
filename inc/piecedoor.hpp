// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#ifndef __PIECEDOOR_HPP
#define __PIECEDOOR_HPP

#include "drawable.hpp"
#include "piece.hpp"
#include "cube.hpp"

// -----------------------------------------------------------------------------

class PieceDoor : public Drawable{
private:
  static Piece piece;
  static Cube door;

public:
  PieceDoor();
  void draw(DrawMode mode) const;
};

// -----------------------------------------------------------------------------

#endif
