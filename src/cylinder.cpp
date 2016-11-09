#include "cylinder.hpp"

Cylinder::Cylinder(){

  vector<RevolutionSurface::point> outline;

  outline.push_back(RevolutionSurface::point(0,0.5,0));
  outline.push_back(RevolutionSurface::point(0,-0.5,0));
  outline.push_back(RevolutionSurface::point(0.5,0.5,0));
  outline.push_back(RevolutionSurface::point(0.5,-0.5,0));

  set_points(outline);
  spin(50);
}
