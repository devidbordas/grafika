#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "camera.h"
#include "scene.h"
#include "fire.h"

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0


typedef struct App
{
    SDL_Window* window;
    SDL_GLContext gl_context;
    bool is_running;
    double uptime;
    Camera camera;
    Scene scene;
    Fire fire;
    Trophy trophy;
    //még ha vmi szükséges az includenál akkor az itt is kell pl #iclude fire.h akkor itt Fire fire;
} App;


Camera camera;
Scene scene;


struct {
    int x;
    int y;
} mouse_position;

/* Call when need to display the graphical content.   App*app-beletettem a displaybe*/
void display(App*app);

/*Initialize the application*/
void init_app(App* app, int width, int height);


/*Initialize the OpenGL context*/
void init_opengl();


/*Reshape the window*/
void reshape(GLsizei width, GLsizei height);

/*Handle the events of the app*/
void handle_app_events(App* app);

/*Update the app*/
void update_app(App* app);

/*Render the app*/
void render_app(App* app);

/*Destroy the app*/
void destroy_app(App* app);

#endif