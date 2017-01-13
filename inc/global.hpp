#ifndef __GLOBAL_HPP
#define __GLOBAL_HPP

#include <GL/glut.h>
#include "jpg_imagen.hpp"
#include "vertex.h"

// LIGTING
// -----------------------------------------------------------------------------
enum LightMode { NONE, FLAT, SMOOTH };

extern LightMode light_mode;

// ROTATION - Watt
// -----------------------------------------------------------------------------
const double max_rotate = 360;
const double MAX_SPEED = 25;
const double MIN_SPEED = 0;
const double SPEED_INC = 0.5;

extern double rotate_angle;
extern double speed;

// TEXTURES
// -----------------------------------------------------------------------------

extern bool active_texture;

extern jpg::Imagen * earth_texture;
extern jpg::Imagen * chess_texture;
extern jpg::Imagen * stars_texture;
extern jpg::Imagen * grass_texture;
extern jpg::Imagen * can_texture;
extern jpg::Imagen * gold_texture;

void set_texture(jpg::Imagen * texture);

// MATERIAL
// -----------------------------------------------------------------------------

const _vertex4<float> material_texture_ambient(0.3,0.3,0.3,1);
const _vertex4<float> material_texture_diffuse(0.8,0.8,0.8,1);
const _vertex4<float> material_texture_specular(0.2,0.2,0.2,1);

void set_texture_material();

#endif
