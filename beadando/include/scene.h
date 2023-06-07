#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include <math.h>
#include "utils.h"

#include <obj/model.h>

typedef struct Scene
{
    Model body;
    Model wheel;
    Model steer;
    Model colos;
    Model plain;
    Model skybox;

    GLuint coltext;
    GLuint plaintext;
    GLuint skytext;

    GLuint motor1_texture_id;
    GLuint motorred_texture_id;
    GLuint motordark_texture_id;
    GLuint motorgray_texture_id;

    GLuint info_texture_id;
    bool info;

    int textureID;

    Material material;
    float motor_rotation;
    float motor_rot_speed;
    float motor_y_speed;
    float motor_x_speed;

    float mx;
    float my;
    float mrot;

    float xpoz;
    float ypoz;
    bool ok;

    float fenyx;
    float fenyy;

    float motor_y_act_speed;
    float motor_x_act_speed;
    float motor_kormany_speed;
    float motor_kormany_rotation;
    float motor_doles_rotation;
    float motor_doles_speed;
    float max_kormany_rotation;

    float light_up;
    float fofenyred;
    float fofenygreen;
    float fofenyblue;
    float skyfeny;

} Scene;


/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(Scene* scene);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, double time);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

void set_motor_rot_speed(Scene* scene, float rot_speed);

void set_motor_y_speed(Scene* scene, float speed);

void set_motor_x_speed(Scene* scene, float speed);

void set_motor_kormany_speed(Scene* scene, float speed);

void set_motor_doles_speed(Scene* scene, float speed);

void set_light_up(Scene* scene, float light);

void texture_change(Scene* scene);

void full_movement(Scene* scene, float elso, float hatso, float degree);




void draw_info_panel(GLuint info_panel);

void set_info(Scene* scene, bool yesno);

void fenyszoro(Scene *scene);

#endif /* SCENE_H */

