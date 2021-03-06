#include "prefix.h"
#include "gameobjects.h"

int main(int argc, char *argv[]) {
    argc = (int)argc;
    argv = (char **)argv;

    Engine *engine = NULL;
    SDL_Surface *screen = NULL;
    Scene *scene = NULL;
    World *world = NULL;

    check(Engine_bootstrap(&engine, (void *)&screen), "Init SDL and OpenGL");

    scene = Scene_create(engine);
    world = Scene_create_world(scene, engine->physics);

    GameEntity_assign_controller(scene->entities->first->value,
            engine->input->controllers[0]);

    while (engine->input->game_quit == 0) {
        Engine_regulate(engine);
        Input_poll(engine->input);

        if (engine->frame_now) {
            Scene_control(scene, engine->input);

            World_solve(engine->physics, world, scene->tile_map,
                    engine->frame_ticks);
            Scene_update(scene, engine);
            Scene_render(scene, engine);
#ifdef DEBUG
            Graphics_draw_debug_text(engine->graphics, engine->frame_ticks);
#endif
            SDL_GL_SwapBuffers();

            if (engine->input->game_quit) break;
            Input_reset(engine->input);
        }
    }

    Scene_destroy(scene);
    engine->_(destroy)(engine);
    SDL_FreeSurface(screen);

    return 0;
error:
    if (scene) Scene_destroy(scene);
    if (world) World_destroy(world);
    if (engine) engine->_(destroy)(engine);
    SDL_FreeSurface(screen);
    return 1;
}
