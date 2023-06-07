#include "app.h"

#include <SDL2/SDL_image.h>

void init_app(App* app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "F58KQ8!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    //glClearColor(0.1, 0.1, 0.1, 1.0);
    //glClearColor(0.4, 0.5, 0.6, 1.0);
    glClearColor(0.15, 0.2, 0.3, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        //.1, 10
        .1, 300
    );
}

void handle_app_events(App* app)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
            
            case SDL_SCANCODE_R:
                set_camera_pos(&(app->camera),-2.5,-3.2,0.0,360.0,0.0,48.0);
                break;
            case SDL_SCANCODE_T:
                texture_change(&(app->scene));
                //printf("x: %f, y: %f, z: %f - rx: %f, rz: %f\n",app->camera.position.x,app->camera.position.y,app->camera.position.z,app->camera.rotation.x,app->camera.rotation.z);
                break;

            case SDL_SCANCODE_F1:
                set_info(&(app->scene), true);
                break;

            case SDL_SCANCODE_1:
            case SDL_SCANCODE_KP_PLUS:
                set_light_up(&(app->scene), 0.1);
                break;
            case SDL_SCANCODE_2:
            case SDL_SCANCODE_KP_MINUS:
                set_light_up(&(app->scene), -0.1);
                break;
            case SDL_SCANCODE_UP:
                set_motor_rot_speed(&(app->scene), 200.0);
                set_motor_y_speed(&(app->scene), -0.07*5);
                break;
            case SDL_SCANCODE_DOWN:
                set_motor_rot_speed(&(app->scene), -200.0);
                set_motor_y_speed(&(app->scene), 0.07*5);
                break;
            case SDL_SCANCODE_LEFT:
                set_motor_kormany_speed(&(app->scene), 90);
                set_motor_doles_speed(&(app->scene), 90);
                break;
            
            case SDL_SCANCODE_RIGHT:
                set_motor_kormany_speed(&(app->scene), -90);
                set_motor_doles_speed(&(app->scene), 90);
                break;
            

            
            case SDL_SCANCODE_Q:
                set_camera_vert_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_E:
                set_camera_vert_speed(&(app->camera), -1);
                break;

            case SDL_SCANCODE_W:
                set_camera_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), -1);
                break;
            case SDL_SCANCODE_A:
                set_camera_side_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), -1);
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_1:
            case SDL_SCANCODE_2:
            case SDL_SCANCODE_KP_PLUS:
            case SDL_SCANCODE_KP_MINUS:
                set_light_up(&(app->scene), 0.0);
                break;
            case SDL_SCANCODE_F1:
                set_info(&(app->scene), false);
                break;
            case SDL_SCANCODE_LEFT:
            case SDL_SCANCODE_RIGHT:
                set_motor_kormany_speed(&(app->scene), 0.0);
                set_motor_doles_speed(&(app->scene), 0.0);
                break;
            case SDL_SCANCODE_UP:
            case SDL_SCANCODE_DOWN:
                set_motor_rot_speed(&(app->scene), 0.0);
                set_motor_y_speed(&(app->scene), 0.0);
                break;
            case SDL_SCANCODE_Q:
            case SDL_SCANCODE_E:
                set_camera_vert_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), 0);
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if (is_mouse_down) {
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
            }
            mouse_x = x;
            mouse_y = y;
            break;
        case SDL_MOUSEBUTTONUP:
            is_mouse_down = false;
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_app(App* app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    update_scene(&(app->scene), elapsed_time);
    
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene));
    glPopMatrix();

    if (app->camera.is_preview_visible) {
        show_texture_preview();
    }

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App* app)
{
    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}
