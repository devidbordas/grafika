#include "scene.h"
#include "utils.h"
#include "ice_element.h"

#include <obj/load.h>
#include <obj/draw.h>


void init_ice_element(Ice_element* ice_element, float y, float z)
{
    load_model(&(ice_element->model), "assets/models/cube.obj");
    ice_element->ice_element_texture_id = load_texture("assets/textures/ice_texture.jpg");
    
    ice_element->position.x=0.0;
    ice_element->position.y=-y;
    ice_element->position.z=z;

    ice_element->ice_element_material.ambient.red = 1.0f;
    ice_element->ice_element_material.ambient.green = 1.0f;
    ice_element->ice_element_material.ambient.blue = 1.0f;

    ice_element->ice_element_material.diffuse.red = 1.0f;
    ice_element->ice_element_material.diffuse.green = 1.0f;
    ice_element->ice_element_material.diffuse.blue = 1.0f;

    ice_element->ice_element_material.specular.red = 1.0f;
    ice_element->ice_element_material.specular.green = 1.0f;
    ice_element->ice_element_material.specular.blue = 1.0f;

    ice_element->ice_element_material.shininess = 0.0f;
}


void draw_ice_element(Ice_element* ice_element)
{
    glBindTexture(GL_TEXTURE_2D, ice_element->ice_element_texture_id);
    glPushMatrix();
    //set_material(&(ice_element->ice_element_material));
    glTranslatef(ice_element->position.x, ice_element->position.y, ice_element->position.z);
    draw_model(&(ice_element->model));
    glPopMatrix();

}