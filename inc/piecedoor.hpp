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
  // TODO: static
  Piece piece;
  Cube door;

public:
  PieceDoor();
  void draw(DrawMode mode) const;
};

// -----------------------------------------------------------------------------

#endif
