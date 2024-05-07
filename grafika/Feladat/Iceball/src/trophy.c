#include "scene.h"
#include "utils.h"
#include "trophy.h"
#include "scene.h"
#include "iceball.h"
#include "texture.h"
#include "camera.h"
#include "app.h"


#include <obj/load.h>
#include <obj/draw.h>

void init_trophy(Trophy* trophy)
{
    load_model(&(trophy->model), "assets/models/trophy.obj");
    trophy->texture=load_texture("assets/textures/trophy_texture.jpg");

    
    trophy->position.x=0.05;
    trophy->position.y=-10.8;
    trophy->position.z=-1.1;

/*
    trophy->trophy_material.ambient.red = 0.4759412f;
    trophy->trophy_material.ambient.green = 0.56529f;
    trophy->trophy_material.ambient.blue = 0.11691f;

    trophy->trophy_material.diffuse.red = 0.362392f;
    trophy->trophy_material.diffuse.green = 0.12238627f;
    trophy->trophy_material.diffuse.blue = 0.4585f;

    trophy->trophy_material.specular.red = 0.1117f;
    trophy->trophy_material.specular.green = 0.11161176f;
    trophy->trophy_material.specular.blue = 0.4822843f;
    trophy->trophy_material.shininess = 18.0f;
 */

    
}

void draw_trophy(Trophy* trophy)
{
    glBindTexture(GL_TEXTURE_2D, trophy->texture);
    glPushMatrix();
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //set_material(&(trophy->trophy_material));
    glTranslatef(trophy->position.x, trophy->position.y, trophy->position.z);
    glRotatef(90.0, 1, 0, 0);
    glRotatef(90.0, 0, 1, 0);
    draw_model(&(trophy->model));
    //glDisable(GL_BLEND);
    glPopMatrix();

}
