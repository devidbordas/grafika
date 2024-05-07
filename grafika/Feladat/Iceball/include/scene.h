#ifndef SCENE_H
#define SCENE_H


#include "camera.h"
#include "texture.h"
#include "map.h"
#include "ice_element.h"
#include "fire.h"
#include "iceball.h"
#include "skybox.h"
#include "trophy.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>



typedef struct Scene
{
    Map map;
    Iceball iceball;
    Ice_element ice_element1;
    Ice_element ice_element2;
    Ice_element ice_element3;
    Skybox skybox;
    Material material;
    Trophy trophy;
    Fire fire1;
    Fire fire2;
    Fire fire3;
    GLuint guide_id;
    GLuint lose_id; 
    GLuint win_id;
    float lighting_changer;
    float fog_density;
   //bool is_lose_visible;
    //bool is_win_visible;

    //GLuint iceball_texture_id; 

}Scene;


/*To measure the light changing*/


/*Initialize the scene by loading models*/
void init_scene(Scene* scene);


/*Change the lighting of the scene*/
void set_lighting(float light);


/*Set the lighting of the scene*/
//void set_lighting_changer(float light);


/*Set the current material*/
void set_material(Material* material); //const Material


/*Draw the scene objects*/
void draw_scene(Scene* scene); //const Scene


void update_scene(Scene* scene);


/*Reset the brightness of the screen*/
void reset_lights();

//void reset_fog();


/*Draw the origin of the world coordinate system*/
void draw_origin();




#endif