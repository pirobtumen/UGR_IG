#include "piece.hpp"

// -----------------------------------------------------------------------------

Piece::Piece(){
  draw(DrawMode::ALL);
}

// -----------------------------------------------------------------------------

void Piece::draw(DrawMode mode) const{
  double sx = 0.5;
  double sy = 0.3;
  double sz = sx;

  glPushMatrix();
  glScaled(sx,sy,sz);
  piece.draw(mode);
  glPopMatrix();
}

// -----------------------------------------------------------------------------
