// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#ifndef __BODY_HPP
#define __BODY_HPP

#include <cmath>
#include "drawable.hpp"
#include "arm2.hpp"
#include "piece.hpp"
#include "piecedoor.hpp"
#include "rotatevar.hpp"

// -----------------------------------------------------------------------------

class Body : public Drawable{
private:
  static Arm2 arm;
  static Piece top;
  static PieceDoor door;

  double get_alpha() const;

  void draw_arms(DrawMode mode) const;
  void draw_top(DrawMode mode) const;
  void draw_door(DrawMode mode) const;

public:
  Body();

  void draw(DrawMode mode) const;
};

#endif
