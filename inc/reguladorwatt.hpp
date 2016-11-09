// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#ifndef __RWATT_HPP
#define __RWATT_HPP

#include "base.hpp"

// -----------------------------------------------------------------------------

class Watt : public Drawable{
private:
  Base base;

public:
  Watt();

  void draw(DrawMode mode) const;
};

#endif
