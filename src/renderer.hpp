#ifndef RENDERER_H_
#define RENDERER_H_

#include <SDL.h>
#include <SDL_ttf.h>

struct Renderer
{
    SDL_Renderer *render;
    SDL_Window *window;
    TTF_Font *font;
    TTF_Font *font_outline;

    int font_size;
    int outline_size;
    
    bool initialize_sdl();
    void render_text(const char *msg_text, int x, int y, Uint8 opacity = 255);
};

#endif // RENDERER_H_
