// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#ifndef __BASE_HPP
#define __BASE_HPP

#include "drawable.hpp"
#include "cube.hpp"
#include "cylinder.hpp"

// -----------------------------------------------------------------------------

class Base : public Drawable{
private:
  static Cube cube;
  static Cylinder cylinder;

  void draw_cube(DrawMode mode) const;
  void draw_cylinder(DrawMode mode) const;

public:
  Base();

  void draw(DrawMode mode) const;
};

#endif
