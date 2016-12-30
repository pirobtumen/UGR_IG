#include "cylinder.hpp"

Cylinder::Cylinder(){

  vector<point> outline;

  outline.push_back(point(0,0.5,0));
  outline.push_back(point(0.5,0.5,0));
  outline.push_back(point(0.5,-0.5,0));
  outline.push_back(point(0,-0.5,0));

  set_points(outline,25);
}
