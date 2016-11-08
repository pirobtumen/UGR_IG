// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#ifndef __DRAWABLE_HPP
#define __DRAWABLE_HPP

// -----------------------------------------------------------------------------

class Drawable{
public:
  Drawable(){};

  virtual void draw_points(double r=0, double g=0, double b=0) const=0;
  virtual void draw_edges(double r=0, double g=0, double b=0) const=0;
	virtual void draw_surfaces(double r=0, double g=0, double b=0) const=0;
	virtual void draw_chess() const=0;
	virtual void draw_all() const=0;
};

#endif
