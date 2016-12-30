// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#ifndef __SCENE_HPP
#define __SCENE_HPP

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

  void init();

public:
  Scene();

  void draw(DrawMode mode) const;

};

// -----------------------------------------------------------------------------

#endif
