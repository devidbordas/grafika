#include "scene.h"
#include "utils.h"

#include <obj/load.h>
#include <obj/draw.h>
#include <math.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->body), "assets/models/motor_test.obj");
    load_model(&(scene->steer), "assets/models/motor_kormany.obj");
    load_model(&(scene->wheel), "assets/models/motor_kerek.obj");
    scene->motordark_texture_id = load_texture("assets/textures/motordark.jpg");
    scene->motorgray_texture_id = load_texture("assets/textures/motorgray.jpg");
    scene->motorred_texture_id = load_texture("assets/textures/red.jpg");

    scene->textureID=0;

    scene->info_texture_id = load_texture("assets/textures/info2.jpg");

    load_model(&(scene->colos), "assets/models/colos2.obj");
    scene->coltext = load_texture("assets/textures/coltext.jpg");

    load_model(&(scene->plain), "assets/models/plain.obj");
    scene->plaintext = load_texture("assets/textures/plain4.jpg");

    load_model(&(scene->skybox), "assets/models/sky.obj");
    scene->skytext = load_texture("assets/textures/skytext4.jpg");

    glBindTexture(GL_TEXTURE_2D, scene->motor1_texture_id);
    scene->info=false;

    //mozgásokhoz
    scene->motor_rotation = 0.0;
    scene->motor_rot_speed = 0.0; //szög
    scene->motor_y_act_speed = 0.0;
    scene->motor_x_act_speed = 0.0;

    scene->motor_x_speed = 0.0;
    scene->motor_y_speed = 0.0;
    scene->motor_kormany_speed = 0.0;
    scene->motor_kormany_rotation = 0.0;

    scene->max_kormany_rotation = 0.0;

    scene->motor_doles_rotation = 0.0;
    scene->motor_doles_speed = 0.0;
    //---------------------------------
    //végső mozgások:
    scene->mx = 0.0;
    scene->my = 0.0;
    scene->mrot = 00.0;

    scene->xpoz=0.0;
    scene->ypoz=0.0;

    scene->ok=true;

    //---------------------------------
    //extra fény változók
    scene->light_up = 0.0;
    scene->fofenyred = 0.1;
    scene->fofenygreen = 0.1;
    scene->fofenyblue = 0.1;
    scene->skyfeny = 1.0;

    scene->fenyx=0.0;
    scene->fenyy=-1.0;
 
    //---------------------------------

    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 128.0;

}

void set_lighting(Scene* scene)
{

    float ambient_light[] = { scene->fofenyred, scene->fofenygreen, scene->fofenyblue, 1.0f };
    float diffuse_light[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    float position[] = { -10.0f, 0.0f, 8.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    
    float ambient_light2[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float diffuse_light2[] = { 1.0f, 0.8f, 0.6f, 1.0f };
    float specular_light2[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    float position2[] = { -10.0f, 0.0f, 3.0f};

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light2);
    glLightfv(GL_LIGHT1, GL_POSITION, position2);
    
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene, double time)
{
    scene->motor_rotation+=scene->motor_rot_speed * time;

    scene->motor_y_act_speed+=scene->motor_y_speed;
    
    scene->material.ambient.red = scene->material.ambient.red;
    scene->material.ambient.green = scene->material.ambient.green;
    scene->material.ambient.blue = scene->material.ambient.blue;

    scene->fofenyred += scene->light_up;
    scene->fofenygreen += scene->light_up;
    scene->fofenyblue += scene->light_up;

    scene->skyfeny += scene->light_up;

    //kormány kerekének max elfordulása:
    float kormany_hatar = 40.0;
    
    if (scene->motor_kormany_rotation>kormany_hatar) {
        scene->motor_kormany_rotation=kormany_hatar;
    }
    else if (scene->motor_kormany_rotation<(-1*kormany_hatar)) {
        scene->motor_kormany_rotation=(-1*kormany_hatar);
    }
    else {
        scene->motor_kormany_rotation+=scene->motor_kormany_speed * time;
    }

    if (scene->motor_doles_rotation>kormany_hatar) {
        if (scene->motor_y_speed!=0){
            scene->motor_doles_rotation=kormany_hatar;
        }
    }
    else if (scene->motor_doles_rotation<(-1*kormany_hatar)) {
        if (scene->motor_y_speed!=0){
            scene->motor_doles_rotation=(-1*kormany_hatar);
        }
    }
    else {
        if (scene->motor_y_speed!=0){
            scene->motor_doles_rotation+=scene->motor_kormany_speed * time;
        }
    }

    scene->ypoz += cos(degree_to_radian(-1*scene->mrot)) * scene->motor_y_speed * 80 * time;
    scene->xpoz += sin(degree_to_radian(-1*scene->mrot)) * scene->motor_y_speed * 80 * time;
    
    //ellipszis barikád számolása:
    //b**2*(x-u)**2+a**2*(y-v)**2<b**2*a**2
    if ( (((scene->xpoz+9)*(scene->xpoz+9))*1100+((scene->ypoz-6)*(scene->ypoz-6))*2809)<1100*2809) {
        scene->mx=scene->xpoz;
        scene->my=scene->ypoz;
    }
    else {
        scene->xpoz=scene->mx;
        scene->ypoz=scene->my;
    }

    if (scene->motor_y_speed!=0){
        scene->mrot += scene->motor_kormany_speed * 1.6 * time;
    }

    scene->fenyy = cos(degree_to_radian(-scene->mrot));
    scene->fenyx = sin(degree_to_radian(-scene->mrot));
}

void render_scene(const Scene* scene)
{
    
    set_lighting(scene);
    draw_origin();

    set_material(&(scene->material));
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

    fenyszoro(scene);

    glPushMatrix();

        glDisable(GL_LIGHTING);
        glColor3f(scene->skyfeny,scene->skyfeny,scene->skyfeny);

        glRotatef(-90,1, 0, 0);
        glTranslatef(0, 0, 40);
        glScaled(40,40,40);
        glBindTexture(GL_TEXTURE_2D, scene->skytext);
        draw_model(&(scene->skybox));
        glEnable(GL_LIGHTING);

    glPopMatrix();
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->coltext);
        glScaled(1.5,1.5,1.5);
        glTranslatef(0, -25, 13.55);
        draw_model(&(scene->colos));
    glPopMatrix();
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->plaintext);
        glTranslatef(0, -100, -2.8);
        glScaled(1.5,1.5,1.5);
        draw_model(&(scene->plain));
    glPopMatrix();
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->motor1_texture_id);

        if (scene->info==true) {
            draw_info_panel(scene->info_texture_id);
        }
        
        
        glTranslatef(scene->mx,scene->my,  0);
        
        
        glRotatef(scene->mrot,0, 0, 1);
        glRotatef((scene->motor_doles_rotation)/2,0,1,0);
       
                

        //kormány - forog vízszintesen
        glPushMatrix();
            glRotatef((scene->motor_kormany_rotation)/2,0,0,1);

            glBindTexture(GL_TEXTURE_2D, scene->motorgray_texture_id);
            draw_model(&(scene->steer));
        
        //első kerék - forog előre hátra a kormánnyal
        glPushMatrix();
            glTranslatef(0, -1.2, -2.3);
            glRotatef(scene->motor_rotation*6,1,0,0);
             
       
            glBindTexture(GL_TEXTURE_2D, scene->motordark_texture_id);
            draw_model(&(scene->wheel));
        glPopMatrix();
        glPopMatrix();

        //hátsó kerék - forog előre hátra
        glPushMatrix();
            glTranslatef(0, 3.5, -2.3);
            glRotatef(scene->motor_rotation*6,1,0,0);

            draw_model(&(scene->wheel));
        glPopMatrix();
        

        //test
        glPushMatrix();
            glTranslatef(0, 1.8, -1.5);
            glBindTexture(GL_TEXTURE_2D, scene->motorred_texture_id);
            
            draw_model(&(scene->body));
        glPopMatrix();
       
    glPopMatrix();

    
}

void draw_origin()
{
    
    
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
}


void set_motor_rot_speed(Scene* scene, float rot_speed) {
    scene->motor_rot_speed=rot_speed;
}

void set_motor_y_speed(Scene* scene, float speed) {
    scene->motor_y_speed=speed;
}
void set_motor_x_speed(Scene* scene, float speed) {
    scene->motor_x_speed=speed;
}

void set_motor_kormany_speed(Scene* scene, float speed) {
    scene->motor_kormany_speed=speed;
}

void set_motor_doles_speed(Scene* scene, float speed) {
    scene->motor_doles_speed=speed;
}

void set_light_up(Scene* scene, float light) {
    scene->light_up=light;
}

void texture_change(Scene* scene) {
    if (scene->textureID < 4) {
        scene->textureID = scene->textureID+1;
    }
    else scene->textureID=0;
    
    switch (scene->textureID) {
    case 0:
        scene->motorred_texture_id = load_texture("assets/textures/red.jpg");
        break;
    case 1:
        scene->motorred_texture_id = load_texture("assets/textures/green.jpg");
        break;
    case 2:
        scene->motorred_texture_id = load_texture("assets/textures/lightblue.jpg");
        break;
    case 3:
        scene->motorred_texture_id = load_texture("assets/textures/darkblue.jpg");
        break;
    case 4:
        scene->motorred_texture_id = load_texture("assets/textures/orange.jpg");
        break;
    }
    glBindTexture(GL_TEXTURE_2D, scene->motor1_texture_id);
    
}

void set_info(Scene* scene, bool yesno) {
    scene->info=yesno;
}

/*
void update_motor(Motor* motor, float time){
    x += cos(rot) * speed * time;
    y += sin(rot) * speed * time;
    rot += rot_speed * time;
    //kormany szögből hátsó kerék szög számítása
}

void render_motor(Motor* motor) {
    glPushMatrix
    translate
    //motorxy
    rotate
    //rot
    glPopMatrix
}
*/

void draw_info_panel(GLuint info_panel) {
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, info_panel);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-4, 3, -5);

    glTexCoord2f(1, 0);
    glVertex3d(4, 3, -5);

    glTexCoord2f(1, 1);
    glVertex3d(4, -3, -5);

    glTexCoord2f(0, 1);
    glVertex3d(-4, -3, -5);
    glEnd();
    glTranslatef(0, 0, 30);


    glEnable(GL_LIGHTING);
}

void fenyszoro(Scene *scene){
    
    glEnable(GL_LIGHT3);
    GLfloat ambient_light[] = {0, 0, 0, 0};
    GLfloat diffuse_light[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat specular_light[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat position[] = {scene->mx, scene->my-0.6, 0.0f, 1.0f};
    GLfloat spot_direction[] = {-scene->fenyx, -scene->fenyy, 0};

    glLightfv(GL_LIGHT3, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);

    glPushMatrix();
        glLightfv(GL_LIGHT3, GL_POSITION, position);
        glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 4);
        glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction);
    glPopMatrix();
}
