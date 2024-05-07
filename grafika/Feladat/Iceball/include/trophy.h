#ifndef TROPHY_H
#define TROPHY_H

#include "utils.h"
#include "camera.h"
#include "scene.h"

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <obj/model.h>

/**
 * trophy
 */
typedef struct Trophy
{
    Model model;
    vec3 position;
    Material trophy_material;
    GLuint texture;
} Trophy;

/**
 * Initialize the trophy object.
 */
void init_trophy(Trophy* trophy);

/**
 * Draw the trophy object.
 */
void draw_trophy(Trophy* trophy);

#endif /* TROPHY_H */