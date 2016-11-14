// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#ifndef __RWATT_HPP
#define __RWATT_HPP

#include "base.hpp"
#include "body.hpp"
#include "rotatevar.hpp"

// -----------------------------------------------------------------------------

class Watt : public Drawable{
private:
  Base base;
  Body body;

public:
  Watt();

  void draw(DrawMode mode) const;
};

#endif
