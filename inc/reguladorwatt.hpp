// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#ifndef __RWATT_HPP
#define __RWATT_HPP

#include "base.hpp"
#include "polyhedron.hpp"

// -----------------------------------------------------------------------------

class Watt : public Drawable{
private:
  Base base;

public:
  Watt();

  void draw_points(double r=0, double g=0, double b=0) const;
  void draw_edges(double r=0, double g=0, double b=0) const;
	void draw_surfaces(double r=0, double g=0, double b=0) const;
	void draw_chess() const;
	void draw_all() const;
};

#endif
