// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#ifndef __DRAWABLE_HPP
#define __DRAWABLE_HPP

// -----------------------------------------------------------------------------

enum DrawMode {ALL, CHESS, SURFACES, EDGES, POINTS};

class Drawable{
public:

  Drawable(){};

  virtual void draw(DrawMode mode, double r=0, double g=0, double b=0) const=0;

};

#endif
