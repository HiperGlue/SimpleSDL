#include <math.h>

float SSDL_COS(float x){
    return cosf(x);
}
float SSDL_ACOS(float x){
    return acosf(x);
}
float SSDL_SIN(float x){
    return sin(x);
}
float SSDL_ASIN(float x){
    return asin(x);
}
float SSDL_TAN(float x){
    return tan(x);
}
float SSDL_ATAN(float x){
    return atanf(x);
}
float SSDL_ATAN2(float x, float y){
    return atan2f(x,y);
}

float SSDL_DEG2RADS(float degrees){
    return degrees * (M_PI / 180.0f);
}
float SSDL_RADS2DEG(float radians){
    return radians * (180.0f / M_PI);
}

float SSDL_SQRT(float x){
    return sqrtf(x);
}

float SSDL_ABS(float x){
    if (x < 0) return -x;
    return x;
}