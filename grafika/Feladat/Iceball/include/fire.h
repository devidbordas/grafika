#ifndef FIRE_H
#define FIRE_H

#include "camera.h"
#include "utils.h"
#include <obj/model.h>
#include <obj/draw.h>
#include "texture.h"


typedef struct  Fire
{
    Model model;
    vec3 position;
    //Material fire_material;
    GLuint texture;
}Fire;


/*Initialize the fire object*/

void init_fire(Fire* fire, float y, float z);


/*Draw the fire object*/

void draw_fire(Fire* fire);

#endif