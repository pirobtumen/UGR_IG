// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#ifndef __PIECE_HPP
#define __PIECE_HPP

#include "drawable.hpp"
#include "cylinder.hpp"

// -----------------------------------------------------------------------------

class Piece : public Drawable{
private:
  // TODO: static
  Cylinder piece;

public:
  Piece();
  void draw(DrawMode mode) const;

};

// -----------------------------------------------------------------------------

#endif
