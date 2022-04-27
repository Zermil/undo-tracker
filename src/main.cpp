#include <cstdio>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define SDL_main main
#include "./renderer.cpp"

#define Z_KEY 0x5A
#define BUFF_CAP 512
#define CLEAR_COLOR 0, 255, 0, 255

static int global_counter;
static int global_dy;
static const char* user_msg = "Pain inflicted: %d times";
static const char* filename = "undos-counted.txt";

// NOTE(Aiden): For some reason, opacity = 0 would loop back to being 255
//   might be because of TextureBlending(?)
static Uint8 global_hint_opacity = 1;

// TODO(#1): Change font option
// TODO(#2): Custom text option


void update_file()
{
    FILE *file = fopen(filename, "w");
    fprintf(file, user_msg, global_counter);
    fclose(file);
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    switch (wParam) {
        case WM_SYSKEYUP:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_KEYDOWN: {
            if (GetAsyncKeyState(VK_CONTROL) & 0x8000
                && GetAsyncKeyState(Z_KEY) & 0x8000)
            {
                global_hint_opacity = 255;
                global_dy = 0;
                global_counter++;

                update_file();
            }
        } break;
    }
    
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main(int argc, char **argv)
{
    SDL_Event event = {};
    MSG msg = {};
    char buffer[BUFF_CAP];
    Renderer sdl_renderer = {};
    
    int width = 0;
    int height = 0;
    HHOOK kbd_hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);

    update_file();
    
    bool running = sdl_renderer.initialize_sdl();
    while (running) {
        // NOTE(Aiden): if (SDL_WaitEvent(&event)) prevented updating in the background
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    running = false;
                } break;
            }
        }
        
        SDL_SetRenderDrawColor(sdl_renderer.render, CLEAR_COLOR);
        SDL_RenderClear(sdl_renderer.render);

        SDL_GetWindowSize(sdl_renderer.window, &width, &height);
        sprintf(buffer, user_msg, global_counter);

        sdl_renderer.render_text(buffer, width * 0.5f, height * 0.5f);

        SDL_Color hint_color = { 255, 255, 255, global_hint_opacity };
        sdl_renderer.render_text("+1", width * 0.5f, (height * 0.5f) - global_dy, hint_color);
        
        if (global_hint_opacity > 1) {
            global_hint_opacity -= 2;
        }

        if (global_dy < 40) {
            global_dy++;
        }
        
        SDL_RenderPresent(sdl_renderer.render);
    }

    // NOTE(Aiden): This might not be necessary, OS will most likely get
    //   the resources back, either this or some form of cleanup funcion here
    //   in case this grows larger
    UnhookWindowsHookEx(kbd_hook);
    
    SDL_DestroyWindow(sdl_renderer.window);
    SDL_DestroyRenderer(sdl_renderer.render);
    TTF_CloseFont(sdl_renderer.font_outline);
    TTF_CloseFont(sdl_renderer.font);
    TTF_Quit();
    SDL_Quit();
    
    return 0;
}
