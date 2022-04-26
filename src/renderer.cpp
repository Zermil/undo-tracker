#include <cstdio>
#include <cassert>

#include "./renderer.hpp"

bool Renderer::initialize_sdl()
{
    if (TTF_Init() != 0) {
        fprintf(stderr, "[ERROR]: Failed to initialize SDL_ttf\n");
        return false;
    }
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "[ERROR]: Failed to initialize SDL.\n");
        return false;
    }

    window = SDL_CreateWindow(
        "undo-tracker",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (window == nullptr) {
        fprintf(stderr, "[ERROR]: Failed to create SDL window.\n");
        return false;
    }

    render = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (render == nullptr) {
        fprintf(stderr, "[ERROR]: Failed to create SDL renderer.\n");
        return false;
    }

    font_size = 32;
    outline_size = 5;
    
    font = TTF_OpenFont("./assets/FreeSansBold.ttf", font_size);
    font_outline = TTF_OpenFont("./assets/FreeSansBold.ttf", font_size);
    
    TTF_SetFontOutline(font_outline, outline_size);
    
    return true;
}

void Renderer::render_text(const char *msg_text, int x, int y, SDL_Color color)
{
    SDL_Color black = { 0, 0, 0, color.a };
    
    SDL_Surface *font_surface = TTF_RenderText_Blended(font, msg_text, color);
    SDL_Surface *outline_surface = TTF_RenderText_Blended(font_outline, msg_text, black);

    assert((font_surface != nullptr && outline_surface != nullptr) &&
           "[ERROR]: Failed to create SDL_Texture\n");
    
    SDL_Rect outline_rect = {
        outline_size,
        outline_size,
        font_surface->w,
        font_surface->h
    };
    
    SDL_SetSurfaceBlendMode(font_surface, SDL_BLENDMODE_BLEND); 
    SDL_BlitSurface(font_surface, NULL, outline_surface, &outline_rect);
    SDL_FreeSurface(font_surface);
    
    SDL_Texture *font_texture = SDL_CreateTextureFromSurface(render, outline_surface);
    
    assert((font_texture != nullptr) &&
           "[ERROR]: Failed to create SDL_Texture\n");

    SDL_Rect font_rect = {};
    SDL_QueryTexture(font_texture, nullptr, nullptr, &font_rect.w, &font_rect.h);

    font_rect.x = x - (font_rect.w * 0.5f);
    font_rect.y = y - (font_rect.h * 0.5f);

    SDL_RenderCopy(render, font_texture, nullptr, &font_rect);
    SDL_DestroyTexture(font_texture);
}
