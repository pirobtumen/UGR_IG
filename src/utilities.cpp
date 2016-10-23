#include "utilities.hpp"

// -----------------------------------------------------------------------------

double heron_formula( _vertex3<float> p1, _vertex3<float> p2, _vertex3<float> p3 ){

  double a = (p3-p1).module();
  double b = (p2-p1).module();
  double c = (p3-p2).module();
  double s = (a+b+c)/2;

  return sqrt(s*(s-a)*(s-b)*(s-c));
}
