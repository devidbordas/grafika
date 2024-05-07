#include "fire.h"
#include "scene.h"
#include "utils.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <obj/load.h>
#include <obj/draw.h>

void init_fire(Fire* fire, float y, float z)
{

load_model(&(fire->model), "assets/models/fire.obj");
fire->texture=load_texture("assets/textures/fire_texture.jpg");


fire->position.x=0.0;
fire->position.y=-y;
fire->position.z=z;

/*
fire->fire_material.ambient.red= 0.1222f;
fire->fire_material.ambient.green= 0.1111f;
fire->fire_material.ambient.blue= 0.1111f;

fire->fire_material.diffuse.red= 0.3355f;
fire->fire_material.diffuse.green= 0.3333f;
fire->fire_material.diffuse.blue= 0.3333f;

fire->fire_material.specular.red= 0.5888f;
fire->fire_material.specular.green= 0.6666f;
fire->fire_material.specular.blue= 0.6666f;

fire->fire_material.shininess=80.5f;
*/

}

void draw_fire(Fire* fire)
{

glBindTexture(GL_TEXTURE_2D, fire->texture);
glPushMatrix();
glRotatef(90.0, 1, 0, 0);
//set_material(&(fire->fire_material));
glTranslatef(fire->position.x, fire->position.y, fire->position.z );
draw_model(&(fire->model));
glPopMatrix();

}