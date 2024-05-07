#include "scene.h"
#include "iceball.h"
#include "texture.h"
#include "utils.h"
#include "camera.h"
#include "app.h"
#include "trophy.h"

#include <obj/load.h>
#include <obj/draw.h>
#include <math.h>


void init_iceball(Iceball* iceball)
{

    load_model(&(iceball->model), "assets/models/iceball.obj");
    iceball->iceball_texture_id = load_texture("assets/textures/iceball_texture.jpg");
    
    iceball->is_win_visible=FALSE;
    iceball->is_lose_visible=FALSE;


    iceball->radius = 0.4;
    iceball->position.x = 0.0;
    iceball->position.y = 0.0;
    iceball->position.z = 0.0;
    iceball->rotation.x = 0.0;
    iceball->moving_speed = 1000.0;
    iceball->rotation_speed = 0.0;
    
    iceball->gravity = -20.0;
    iceball->upward_speed = 0.0;
    iceball->in_the_air = FALSE;
    iceball->bouncing = 0;

    iceball->iceball_material.ambient.red = 1.0f;
    iceball->iceball_material.ambient.green = 1.0f;
    iceball->iceball_material.ambient.blue = 1.0f;

    iceball->iceball_material.diffuse.red = 1.0f;
    iceball->iceball_material.diffuse.green = 1.0f;
    iceball->iceball_material.diffuse.blue = 1.0f;

    iceball->iceball_material.specular.red = 1.0f;
    iceball->iceball_material.specular.green = 1.0f;
    iceball->iceball_material.specular.blue = 1.0f;

    iceball->iceball_material.shininess = 100.0f;
}

void draw_iceball(Iceball* iceball)
{
    glBindTexture(GL_TEXTURE_2D, iceball->iceball_texture_id); //pushon belül volt
    glPushMatrix();
    glTranslatef(iceball->position.x, iceball->position.y, iceball->position.z);
    set_material(&(iceball->iceball_material));
    glRotatef(iceball->rotation.x, 1, 0, 0);
    glVertex3f(iceball->position.x, iceball->position.y, iceball->position.z);
    draw_model(&(iceball->model));
    glPopMatrix();
}


void reset_iceball(Iceball* iceball)
{
    iceball->bouncing = 0;
    iceball->position.x = 0.0;
    iceball->position.y = 0.0;
    iceball->position.z = 0.0;
    iceball->moving_speed = 0.0;
    iceball->rotation.z = 0.0;
    iceball->rotation_speed = 0.0;
    iceball->upward_speed = 0.0;
}
    

void update_iceball(Iceball* iceball, Map* map, Ice_element* ice_element, Fire* fire, Trophy* trophy)
{
    //double angle;
    //double side_angle;

    //angle = degree_to_radian(iceball->rotation.z);
    //side_angle = degree_to_radian(iceball->rotation.z + 90.0);

    static int last_frame_time = 0;
    int current_time;
    double elapsed_time;
   

    current_time = (double)SDL_GetTicks() ;   //HIÁNYZIK () belőle??
    elapsed_time = (double)(current_time - last_frame_time)/1000;
    last_frame_time = current_time;
    


    //Left and right movement.

    iceball->position.y +=iceball->moving_speed * elapsed_time;
    iceball->rotation.x +=iceball->rotation_speed * elapsed_time;
 

    if(iceball->position.y > 0.0){
        iceball->position.y = 0.0;
        iceball->rotation.x -=iceball->rotation_speed * elapsed_time;
        set_camera_speed(&camera, 0.0);
        set_camera_side_speed(&camera, 0.0);
    }

    if(iceball->position.y < -11.0){
        iceball->position.y = -11.0;
        iceball->rotation.x -=iceball->rotation_speed * elapsed_time;
        set_camera_speed(&camera, 0.0);
        set_camera_side_speed(&camera, 0.0);
    }
    

    //Jump movement.

    iceball->upward_speed += iceball->gravity * elapsed_time;
    iceball->position.z += iceball->upward_speed * elapsed_time;

    float map_h = map->position.z + 0.9;

    
    if(iceball->position.z < map_h)
    {
        iceball->upward_speed = 0.0;
        iceball->position.z = map_h;
        iceball->in_the_air = FALSE;
    }
    

    //Bounding box.

    float iceball_r = iceball->position.y - iceball->radius;
    float iceball_l = iceball->position.y + iceball->radius;
    float iceball_b = iceball->position.z - iceball->radius;

    //Bounding box. (ice_element)

    float ice_element_l = ice_element->position.y+0.5;
    float ice_element_r = ice_element->position.y-0.5;
    float ice_element_h = ice_element->position.z + 0.9;


    if(iceball_r <= ice_element_l && iceball_l >= ice_element_r && iceball->position.z < ice_element_h)
    {
        if(iceball_r <= ice_element_l && iceball_r >= ice_element_l-0.1)
        {
            iceball->position.y += 0.05;
            set_camera_speed(&camera, 0.0);
            set_camera_side_speed(&camera, 0.0);
        }
        
        if(iceball->position.z <= ice_element_h && iceball_r <= ice_element_l - 0.1 && iceball_l >= ice_element_r + 0.1){
            iceball->upward_speed = 0.0;
            iceball->position.z = ice_element_h;
            iceball->in_the_air = FALSE;
        }
        
        if(iceball_l >= ice_element_r && iceball_l <= ice_element_r + 0.1){
            iceball->position.y -= 0.05;
            set_camera_speed(&camera, 0.0);
            set_camera_side_speed(&camera, 0.0);
        }
        
    }



    //Bounding box.   FIRE 

    float fire_l = ice_element->position.y +1.2;
    float fire_r = ice_element->position.y - 0.4;
    float fire_h = ice_element->position.z + 0.05;
    
/*
if(iceball->position.y-iceball->radius>=fire->position.y +1.5 || iceball->position.y-iceball->radius<=fire->position.y -1.5 )
{
    iceball->is_lose_visible=TRUE;
}
*/


    if(iceball_r <= fire_l && iceball_l >= fire_r && iceball_b <= fire_h)
    {
       iceball->is_lose_visible=TRUE;
    }


    //Bounding box. (trophy)

    float trophy_l = trophy->position.y+ 0.45;
    float trophy_h = trophy->position.z + 2.7;

    if(iceball_r <= trophy_l && iceball_b <= trophy_h)
    {
        iceball->is_win_visible=TRUE;
    }


    //Bouncing

    if(!iceball->in_the_air && iceball->bouncing == 4)
    {
        iceball->upward_speed = 8;
        iceball->in_the_air = TRUE;
        iceball->bouncing = 3;
    }


    if(!iceball->in_the_air && iceball->bouncing == 3)
    {
        iceball->upward_speed = 5;
        iceball->in_the_air = TRUE;
        iceball->bouncing = 2;
    }

    if(!iceball->in_the_air && iceball->bouncing == 2)
    {
        iceball->upward_speed = 3;
        iceball->in_the_air = TRUE;
        iceball->bouncing = 1;
    }

    if(!iceball->in_the_air && iceball->bouncing == 1)
    {
        iceball->upward_speed = 1;
        iceball->in_the_air = TRUE;
        iceball->bouncing = 0;
    }


}

void setting_iceball_moving_speed(Iceball* iceball, float speed)
{
    iceball->moving_speed = speed;
}


void setting_iceball_rotation(Iceball* iceball, float speed)

{
    iceball->rotation_speed = speed;
}

void setting_upward_speed(Iceball* iceball, float jumping_power)
{
    if(!iceball->in_the_air)
    {
        iceball->upward_speed=jumping_power;
        iceball->in_the_air=TRUE;
        iceball->bouncing=4;
    }
}