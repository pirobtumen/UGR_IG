
#include "camera.hpp"

Camera::Camera(){
  set_position(0,0,-2);
}

void Camera::set_position(double ix, double iy, double iz){
  x = ix;
  y = iy;
  z = iz;
}

void Camera::add_position(double ix, double iy, double iz){
  x += ix;
  y += iy;
  z += iz;
}

void Camera::add_z(double iz){
  z += iz;
}

void Camera::set_x_angle(double ix_angle){
  x_angle = ix_angle;
}

void Camera::set_y_angle(double iy_angle){
  y_angle = iy_angle;
}

void Camera::set_z_angle(double iz_angle){
  z_angle = iz_angle;
}

void Camera::add_x_angle(double ix_angle){
  x_angle += ix_angle;
}

void Camera::add_y_angle(double iy_angle){
  y_angle += iy_angle;
}

void Camera::add_z_angle(double iz_angle){
  z_angle += iz_angle;
}

void Camera::update_view(){
  glTranslatef(x,y,z);
  glRotatef(x_angle,1,0,0);
  glRotatef(y_angle,0,1,0);
  glRotatef(z_angle,0,0,1);
}
