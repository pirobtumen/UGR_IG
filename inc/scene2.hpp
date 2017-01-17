#ifndef __SCENE2_HPP
#define __SCENE2_HPP

#include <GL/glut.h>
#include "drawable.hpp"
#include "polyhedron.hpp"
#include "global.hpp"

class Scene2 : public Drawable{
private:
  int selected_element;
  Polyhedron beethoven;

public:
  Scene2();

  void draw(DrawMode mode) const;
  void set_selected(int selected);
};

#endif
