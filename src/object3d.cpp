#include "object3d.hpp"

// -----------------------------------------------------------------------------
// Implementación
// -----------------------------------------------------------------------------

Object3D::Object3D(){}

// -----------------------------------------------------------------------------

void Object3D::clear(){
  points.clear();
}

// -----------------------------------------------------------------------------

void Object3D::set_num_vertex(unsigned int num){
  points.reserve(num);
}

// -----------------------------------------------------------------------------

void Object3D::add_point(coordinate x, coordinate y, coordinate z){
  points.push_back(Object3D::point(x,y,z));
}

// -----------------------------------------------------------------------------

// Prec: pos <= points.size()
void Object3D::set_point(index pos, const point & point){
  points[pos] = point;
}

// -----------------------------------------------------------------------------

const Object3D::vector_points & Object3D::get_points() const{
  return points;
}

// -----------------------------------------------------------------------------

int Object3D::get_num_points() const {
  return points.size();
}

// -----------------------------------------------------------------------------

void Object3D::draw_points(double r, double g, double b) const{
	/*
	 * Dibuja los puntos (vértices) del modelo.
	 */

	int num_points = get_num_points();

	glBegin(GL_POINTS);
  glColor3f(r,g,b);
	for( int i = 0; i < num_points; i++ )
		glVertex3fv( (GLfloat *) &points[i] );

	glEnd();
}
