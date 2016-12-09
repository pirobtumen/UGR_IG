#include "sphere.hpp"

// -----------------------------------------------------------------------------

Sphere::Sphere(){
  surface_points_number = 50;

  generate_profile();
  spin(50);
}

// -----------------------------------------------------------------------------

Sphere::Sphere(unsigned int profile_points){
  surface_points_number = profile_points;

  generate_profile();
}

// -----------------------------------------------------------------------------

void Sphere::generate_profile(){

  const double radius = 0.5;
  const double angle = -1*PI/surface_points_number;

  point p(0,0.5,0);
  point p2;

  points.push_back(point(0,0.5,0));
  points.push_back(point(0,-0.5,0));

  for( int i = 0; i < surface_points_number; i++ ){

    p2.x = p.x*cos(angle) - p.y*sin(angle);
    p2.y = p.x*sin(angle) + p.y*cos(angle);

    p = p2;

    points.push_back(p2);
  }

}

// -----------------------------------------------------------------------------
