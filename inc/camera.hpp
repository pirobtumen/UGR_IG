#ifndef __CAMERA_HPP
#define __CAMERA_HPP

#include <GL/glut.h>

class Camera{
public:
  enum ProjectionMode { PARALLEL, PERSPECTIVE };

private:
  ProjectionMode projection_mode;

  double x;
  double y;
  double z;
  double x_angle;
  double y_angle;
  double z_angle;

public:
  Camera();

  void set_position(double ix, double iy, double iz);
  void set_x_angle(double ix_angle);
  void set_y_angle(double iy_angle);
  void set_z_angle(double iz_angle);

  void add_position(double ix, double iy, double iz);
  void add_z(double iz);
  void add_x_angle(double ix_angle);
  void add_y_angle(double iy_angle);
  void add_z_angle(double iz_angle);

  void update_view();
};

#endif
