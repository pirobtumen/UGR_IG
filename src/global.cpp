#include "global.hpp"

LightMode light_mode = FLAT;
bool active_texture = true;

double rotate_angle = 0;
double speed = MIN_SPEED;

jpg::Imagen * earth_texture = NULL;
jpg::Imagen * chess_texture = NULL;
jpg::Imagen * stars_texture = NULL;
jpg::Imagen * grass_texture = NULL;
jpg::Imagen * can_texture = NULL;
