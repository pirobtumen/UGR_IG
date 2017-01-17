#include "sphere.hpp"

// -----------------------------------------------------------------------------

Sphere::Sphere(){
  profile_length = 50;

  generate_profile();
  spin(profile_length);
}

// -----------------------------------------------------------------------------

Sphere::Sphere(unsigned int profile_points){
  profile_length = profile_points;

  generate_profile();
  spin(profile_length);
}

// -----------------------------------------------------------------------------

void Sphere::generate_profile(){

  const double radius = 0.5;
  const double angle = -1*PI/(profile_length-1);

  point p(0,0.5,0);
  point p2(p);

  // TODO: remove clear
  points.clear();
  points.push_back(p);

  for( int i = 0; i < profile_length; i++ ){
    p2.x = p.x*cos(angle) - p.y*sin(angle);
    p2.y = p.x*sin(angle) + p.y*cos(angle);

    p = p2;

    points.push_back(p2);
  }

}

// -----------------------------------------------------------------------------
