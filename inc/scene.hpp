// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#ifndef __SCENE_HPP
#define __SCENE_HPP

#include "global.hpp"
#include "drawable.hpp"
#include "board.hpp"
#include "polyhedron.hpp"
#include "revolutionsurface2.hpp"
#include "sphere.hpp"
#include <cmath>
#include <vector>

// -----------------------------------------------------------------------------

class Scene : public Drawable{

private:
  RevolutionSurface2 pawn;
  RevolutionSurface2 can_sup;
  RevolutionSurface2 can_mid;
  Polyhedron can_inf;
  Board board;
  Sphere sphere;
  unsigned int selected_element;

  void init();

public:
  Scene();

  void set_selected(unsigned int ielement);
  void draw(DrawMode mode) const;

};

// -----------------------------------------------------------------------------

#endif
