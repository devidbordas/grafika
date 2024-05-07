#ifndef ICE_ELEMENT_H
#define ICE_ELEMENT_H

#include "utils.h"
#include "camera.h"

#include <obj/model.h>


/*Ice element*/
typedef struct Ice_element
{
    Model model;
    GLuint ice_element_texture_id;
    vec3 position;
    Material ice_element_material;
} Ice_element;

void init_ice_element(Ice_element* ice_element, float y, float z);

void draw_ice_element(Ice_element* ice_element);

#endif