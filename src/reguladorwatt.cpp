// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#include "reguladorwatt.hpp"

// -----------------------------------------------------------------------------
// Implementación
// -----------------------------------------------------------------------------

Watt::Watt(){
  draw_all();
}

// -----------------------------------------------------------------------------

void Watt::draw_points(double r, double g, double b) const{
  base.draw_points(r,g,b);
}

// -----------------------------------------------------------------------------

void Watt::draw_edges(double r, double g, double b) const{
  base.draw_edges(r,g,b);
}

// -----------------------------------------------------------------------------

void Watt::draw_surfaces(double r, double g, double b) const{
  base.draw_surfaces(r,g,b);
}

// -----------------------------------------------------------------------------

void Watt::draw_chess() const{
  base.draw_chess();
}

// -----------------------------------------------------------------------------

void Watt::draw_all() const{
  draw_points(0,0,0);
  draw_edges(0,0,1);
  draw_surfaces(1,0,1);
}

// -----------------------------------------------------------------------------

void Watt::draw(DrawMode mode, double r, double g, double b) const{

  switch (mode) {
		case ALL:
			draw_all();
			break;
		case CHESS:
			draw_chess();
			break;
		case SURFACES:
			draw_surfaces(r,g,b);
			break;
		case EDGES:
			draw_edges(r,g,b);
			break;
		case POINTS:
			draw_points(r,g,b);
			break;
	}
  
}

// -----------------------------------------------------------------------------
