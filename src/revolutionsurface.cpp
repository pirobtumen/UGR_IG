// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#include "revolutionsurface.hpp"

// -----------------------------------------------------------------------------

RevolutionSurface::RevolutionSurface(){
  surface_points_number = 0;
}

// -----------------------------------------------------------------------------

RevolutionSurface::RevolutionSurface( const vector_points & points ){

  set_points(points);
  generate_points(10);

}

// -----------------------------------------------------------------------------

RevolutionSurface::RevolutionSurface( const vector_points & points, unsigned int num_surfaces ){

  set_points(points);
  spin(num_surfaces);

}

// -----------------------------------------------------------------------------

void RevolutionSurface::set_points( const vector_points & surface_points ){
  /*
    Rota los puntos iniciales para que estén situados en el plano que forma
    0º respecto al eje de rotación(Y).
  */
  point rotated_point;
  unsigned int index = 0;
  double radius;

  surface_points_number = surface_points.size();

  // Suponemos Y como eje de rotación
  while( surface_points[index].x == 0 && surface_points[index].z == 0 ){
    points.push_back(surface_points[index]);
    index++;
  }

  for(int i = index; i < surface_points_number; i++){

    radius = sqrt(surface_points[i].x*surface_points[i].x +
                  surface_points[i].z*surface_points[i].z);

    rotated_point.x = radius;
    rotated_point.y = surface_points[i].y;
    rotated_point.z = 0;

    points.push_back(rotated_point);
  }
}

// -----------------------------------------------------------------------------

void RevolutionSurface::spin( unsigned int num_surfaces ){
  generate_points(num_surfaces);
  generate_surfaces(num_surfaces);
  generate_covers(num_surfaces);
}

// -----------------------------------------------------------------------------

void RevolutionSurface::generate_points( unsigned int num_surfaces ){

  unsigned int index = 0;
  unsigned int new_point_index = 0;
  point new_point;
  double jump = 2*PI/num_surfaces; // MODIFICAR PARA NO TENER LOS 360º
  double angle = jump;
  double radius;

  // Suponemos Y como eje de rotación
  while( points[index].x == 0 && points[index].z == 0 )
    index++;

  // Index = Número de tapas (puntos en el eje)
  points.resize((surface_points_number-index)*num_surfaces + index);
  new_point_index = surface_points_number;

  for( int i = index; i < surface_points_number; i++ ){

    angle = jump;
    radius = sqrt(points[i].x*points[i].x +
                  points[i].z*points[i].z);

    for( int j = 1; j < num_surfaces; j++ ){

      new_point.x = cos(angle)*radius;
      new_point.y = points[i].y;
      new_point.z = sin(angle)*radius;

      points[new_point_index] = new_point;

      angle += jump;
      new_point_index += 1;
    }
  }

}

// -----------------------------------------------------------------------------

void RevolutionSurface::generate_surfaces( unsigned int num_surfaces ){
  /*
    Debido a cómo se almacenan los puntos, primero se almacenan los puntos,
    primero se generan las caras que involucran al primer perfil.

    Se pueden optimizar algunas operaciones.
  */
  unsigned int offset = 0;
  unsigned int stop = surface_points_number - 1;;
  unsigned int stop2;
  unsigned int stop3;

  faces.clear();

  while( points[offset].x == 0 && points[offset].z == 0 )
    offset++;

  // Dibuja las caras que implican los puntos del perfil definido
  for( int i = offset; i < stop; i++ ){

    faces.push_back( RevolutionSurface::face(
      i,
      surface_points_number+(num_surfaces-1)*(i-offset),
      i+1
    ));

    faces.push_back( RevolutionSurface::face(
      i+1,
      surface_points_number+(num_surfaces-1)*(i-offset),
      surface_points_number+(num_surfaces-1)*(i-offset+1)
    ));

    // Opuestas
    faces.push_back( RevolutionSurface::face(
      i,
      surface_points_number+(num_surfaces-1)*(i-offset)+num_surfaces-2,
      surface_points_number+(num_surfaces-1)*(i-offset+1)+num_surfaces-2
    ));

    faces.push_back( RevolutionSurface::face(
      i,
      surface_points_number+(num_surfaces-1)*(i-offset+1)+num_surfaces-2,
      i+1
    ));

  }

  stop2 = surface_points_number - offset - 1;

  // Dibuja el resto de caras de los puntos generados
  for( int i = 0; i < stop2; i++ ){
    stop3 = surface_points_number+(num_surfaces-1)*i + num_surfaces -2;

    for( int j = surface_points_number+(num_surfaces-1)*i; j < stop3; j++ ){

        faces.push_back( RevolutionSurface::face(
          j,
          j+1,
          j+num_surfaces-1) );

        faces.push_back( RevolutionSurface::face(
          j+1,
          j+num_surfaces-1,
          j+num_surfaces) );
    }

  }

}

// -----------------------------------------------------------------------------

void RevolutionSurface::generate_covers( unsigned int num_surfaces ){
  /*
    Conecta el primer punto que encuentre en el eje, con el primer punto del
    perfil.
    Si hay un segundo punto en el eje, lo conecta con el último punto del
    perfil.
  */
  unsigned int offset = 0;
  int stop;

  while( points[offset].x == 0 && points[offset].z == 0 )
    offset++;

  if(offset > 0 ){

    faces.push_back( RevolutionSurface::face(
      0,    // Primer punto en el eje
      surface_points_number+num_surfaces-2,
      offset) );

    faces.push_back( RevolutionSurface::face(
      0,    // Primer punto en el eje
      surface_points_number,
      offset) );

    stop = surface_points_number + num_surfaces-2;

    for( int i = surface_points_number; i < stop; i++){
      faces.push_back( RevolutionSurface::face(
        0,    // Primer punto en el eje
        i,
        i+1) );
    }

  }

  if(offset == 2){
    faces.push_back( RevolutionSurface::face(
      1,    // Primer punto en el eje
      surface_points_number+num_surfaces-2+(surface_points_number-offset-1)*(num_surfaces-1),
      surface_points_number-1) );

    faces.push_back( RevolutionSurface::face(
      1,    // Primer punto en el eje
      surface_points_number+(surface_points_number-offset-1)*(num_surfaces-1),
      surface_points_number-1) );

    stop = surface_points_number+(surface_points_number-offset-1)*(num_surfaces-1) + num_surfaces-2;

    for( int i = surface_points_number+(surface_points_number-offset-1)*(num_surfaces-1); i < stop; i++){
      faces.push_back( RevolutionSurface::face(
        1,    // Primer punto en el eje
        i,
        i+1) );
    }
  }

}

// -----------------------------------------------------------------------------
