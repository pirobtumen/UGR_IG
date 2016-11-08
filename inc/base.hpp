// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#ifndef __BASE_HPP
#define __BASE_HPP

#include "polyhedron.hpp"
#include "cube.hpp"

// -----------------------------------------------------------------------------

class Base : public Drawable{
private:
  // TODO: static
  Cube cube;

public:
  Base();

  void draw_points(double r=0, double g=0, double b=0) const;
  void draw_edges(double r=0, double g=0, double b=0) const;
	void draw_surfaces(double r=0, double g=0, double b=0) const;
	void draw_chess() const;
	void draw_all() const;
};

#endif
