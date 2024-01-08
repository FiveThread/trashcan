#include <stdio.h>
#include <stdlib.h>

#include "mem.h"

#include "trashcan.h"

#define TARGET_FPS 60


u32 *bitmemory;
int bitwidth;
int bitheight;
int bytperpixel = 4;

const unsigned char *inkeys = 0;


static void pixel_draw(int x, int y, u32 colour)
{
    if(x >= 0 && x < bitwidth && y >= 0 && y < bitheight) bitmemory[y * bitwidth + x] = colour;
}

static void resize_texture(SDL_Renderer *renderer, int width, int height)
{
    if(bitmemory) free(bitmemory);
    if(state.texture) SDL_DestroyTexture(state.texture);

    state.texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    bitheight = height;
    bitwidth = width;
    bitmemory = malloc(width*height*bytperpixel);
}

static void window_update(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_UpdateTexture(state.texture, 0, bitmemory, bitwidth * bytperpixel);
    SDL_RenderCopy(renderer, state.texture, 0, 0);
    SDL_RenderPresent(renderer);
}

static void event_handler(SDL_Event *ev)
{
    switch(ev->type)
    {
        case SDL_WINDOWEVENT:
        {
            switch(ev->window.event)
            {
                case SDL_WINDOWEVENT_RESIZED:
                {
                    SDL_Window *window = SDL_GetWindowFromID(ev->window.windowID);
                    SDL_Renderer *renderer = SDL_GetRenderer(window);
                    resize_texture(renderer, ev->window.data1, ev->window.data2);
                }break;

                case SDL_WINDOWEVENT_EXPOSED:
                {
                    SDL_Window *window = SDL_GetWindowFromID(ev->window.windowID);
                    SDL_Renderer *renderer = SDL_GetRenderer(window);
                    window_update(window, renderer);
                }break;
            }
        }break;
    }
}

void window_create(int width, int height, const char *title)
{
    SDL_Init(SDL_INIT_VIDEO);
    state.window = SDL_CreateWindow(title,  SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_RESIZABLE);

    if(state.window)
    {
        state.renderer = SDL_CreateRenderer(state.window, -1, 0);

        if(state.renderer)
        {
            int width, height;
            SDL_GetWindowSize(state.window, &width, &height);
            resize_texture(state.renderer, width, height);
        }
    }
}


void eg_update(void(*draw)(), void(*update)(double))
{
    u64 now = SDL_GetPerformanceCounter();
    u64 last = 0; 
    double dt = 0;
    while(1)
    {
        SDL_Event ev;
        while(SDL_PollEvent(&ev))
        {
            if(ev.type == SDL_QUIT) exit(0);
            event_handler(&ev);
        }


        memset(bitmemory, 0, bitwidth * bitheight * bytperpixel);

        last = now;
        now = SDL_GetPerformanceCounter();
        dt = (double)((now - last)*1000 / (double)SDL_GetPerformanceFrequency() ) * 0.001;
        
        update(dt);
        draw();
        
        window_update(state.window, state.renderer);
    }
    SDL_Quit();
}

void draw_line(int x0, int y0, int x1, int y1, u32 colour)
{
    int dx, dy;
    int sx, sy;
    int accum;

    dx = x1 - x0;
    dy = y1 - y0;

    sx = SGN(dx);
    sy = SGN(dy);

    dx = abs(dx);
    dy = abs(dy);

    x1 += sx;
    y1 += sy;

    if(dx > dy)
    {
        accum = dx >> 1;
        do
        {
            pixel_draw(x0, y0, colour);
            accum -= dy;

            if(accum < 0)
            {
                accum += dx;
                y0 += sy;
            }
            x0 += sx;
        }while(x0 != x1);
    }else
    {
        accum = dy >> 1;

        do
        {
            pixel_draw(x0, y0, colour);
            accum -= dx;
            if(accum < 0)
            {
                accum += dy;
                x0 += sx;
            }
            y0 += sy;
        }while(y0 != y1);
    }
}

void draw_wire_rect(int posx, int posy, int width, int height, u32 colour)
{
    int x = posx, y = posy;
    int w = width, h = height;
  
    draw_line(x,y,x+w,y,colour);
    draw_line(x+w,y,x+w,y+h,colour);
    draw_line(x+w,y+h,x,y+h,colour);
    draw_line(x,y+h,x,y,colour);
}

void draw_filled_rect(int posx, int posy, int width, int height, u32 colour)
{  
    int xmin = posx, ymin = posy;
    int xmax = posx + width, ymax = posy + height;

    for(int hy=ymin;hy<=ymax;hy++)
    {
        for(int hx=xmin;hx<=xmax;hx++)
        {
            if(hx >= xmin && hx <= xmax && hy >= ymin && hy <= ymax)
            {
                pixel_draw(hx,hy,colour);
            }
        }
    }
}