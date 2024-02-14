#include <stdio.h>

#include "vectors.h"
#include "trashcan.h"

typedef struct
{
    Vector2D pos;
    u32 colour;
}entity;

entity test1_entity;
entity test2_entity;



void draw()
{
    draw_wire_rect(test1_entity.pos.x, test1_entity.pos.y, 10, 10, test1_entity.colour);
    draw_wire_rect(test2_entity.pos.x, test2_entity.pos.y, 10, 10, test2_entity.colour);
}

void update(double dt)
{
    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN]) {test1_entity.pos.y += 10 * dt;}
    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP]) {test1_entity.pos.y -= 10 * dt;}
    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]) {test1_entity.pos.x -= 10 * dt;}
    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]) {test1_entity.pos.x += 10 * dt;}


    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S]) {test2_entity.pos.y += 10 * dt;}
    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W]) {test2_entity.pos.y -= 10 * dt;}
    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A]) {test2_entity.pos.x -= 10 * dt;}
    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D]) {test2_entity.pos.x += 10 * dt;}

    Vector2D br = Vector2DSubtract(test1_entity.pos, test2_entity.pos);
    Vector2D e1_uVector = UnitVector2D(test1_entity.pos);
    Vector2D br_uVector = UnitVector2D(br);

    float dot = Vector2D_DotProduct(e1_uVector, br_uVector);
    printf("dot: %.6f \n", dot);

    if(dot < -0.4)
    {
        test2_entity.colour = 0x008000;
    }else{ test2_entity.colour = 0xFFFFFFF; }

}


void init()
{
    test1_entity.pos.x = 1;
    test1_entity.pos.y = 2;
    test1_entity.colour = 0x000080;

    test2_entity.pos.x = 5;
    test2_entity.pos.y = 5;
    test2_entity.colour = 0xFFFFFFF;
}

int main(int argc, char **argv)
{
    init();

    /*
    Vector2D test = {1, 2};
    Vector2D n_test = {4, 2};
    
    const Vector2D u_vector = UnitVector2D(test);
    const Vector2D n_vec = UnitVector2D(n_test);

    const float length = GetVector2DLength(u_vector);
    const float dot = Vector2D_DotProduct(u_vector, n_vec);

    printf("x unit vector: %.6f y unit vector: %.6f \n", u_vector.x, u_vector.y);
    printf("dot: %.6f \n", dot); */

    window_create(650, 350, "test");
    eg_update(draw, update);

    return 0;
}