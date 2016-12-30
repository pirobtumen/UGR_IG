#ifndef __LIGHTVAR_HPP
#define __LIGHTVAR_HPP

#include "jpg_imagen.hpp"

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

#endif
