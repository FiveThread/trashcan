#ifndef _VECTORS_H
#define _VECTORS_H

#define ABS(n) (((n) < 0) ? -(n) : (n)) /* Absolute function */
#define TOL 0.001 /* Tolerance */

#include "t_math.h"

typedef struct
{
    float x;
    float y;
}Vector2D;



/*
    Get length of 2D vector
    return: Float
*/
float GetVector2DLength(Vector2D a)
{
    float v_length = v_sqrt(a.x*a.x+a.y*a.y);
    return v_length;
}

/*
    Get unit of 2D vector
    return: Vector2D
*/
Vector2D UnitVector2D(Vector2D a)
{
    float v_length = GetVector2DLength(a);

    float new_x = a.x / v_length;
    float new_y = a.y / v_length;

    Vector2D n_Vector = {new_x, new_y};

    return n_Vector;
}

Vector2D Vector2DSubtract(Vector2D a, Vector2D b)
{
    Vector2D v;
    v.x = a.x - b.x;
    v.y = a.y - b.y;
    return v;
}

float Vector2D_DotProduct(Vector2D a, Vector2D b)
{
    float dp = a.x*b.x+a.y*b.y;
    return dp;
}


#endif


