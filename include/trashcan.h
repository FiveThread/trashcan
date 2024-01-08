//An  Utter rubbish sdl engine thing

#ifndef _TRASHCAN_H
#define _TRASHCAN_H

#include <stdint.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#define SGN(_x) ((_x) < 0 ? -1 : ((_x) > 0 ? 1 : 0))


typedef uint64_t u64;
typedef uint32_t u32;
typedef int32_t  i32;
typedef uint8_t  u8;


static struct
{
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_Texture     *texture;
    u32             *pixels;
}state;

//Window functions
extern void window_create(int width, int height, const char *title);

//Engine functions
extern void eg_update(void(*draw)(), void(*update)(double));


//Draw functions
extern void draw_line(int x0, int y0, int x1, int y1, u32 colour);
extern void draw_wire_rect(int posx, int posy, int width, int height, u32 colour);
extern void draw_filled_rect(int posx, int posy, int width, int height, u32 colour);



#endif