#ifndef _TRASH_MATH_H
#define _TRASH_MATH_H


/*
    Newton-Raphson method of square root
    code taken from: vs97 on stackoverflow
    Retuns: Float
*/

float v_sqrt(float x)
{
    float y = 1.0;
    while(ABS(x/y - y) > TOL)
    {
        y = (y+x/y)/2.0;
    }
    return y;
}



#endif