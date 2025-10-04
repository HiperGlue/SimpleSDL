#include <math.h>

float SSDL_COS(const float x){
    return cosf(x);
}
float SSDL_ACOS(const float x){
    return acosf(x);
}
float SSDL_SIN(const float x){
    return sin(x);
}
float SSDL_ASIN(const float x){
    return asin(x);
}
float SSDL_TAN(const float x){
    return tan(x);
}
float SSDL_ATAN(const float x){
    return atanf(x);
}
float SSDL_ATAN2(const float x, const float y){
    return atan2f(x,y);
}

float SSDL_DEG2RADS(const float degrees){
    return degrees * (M_PI / 180.0f);
}
float SSDL_RADS2DEG(const float radians){
    return radians * (180.0f / M_PI);
}

float SSDL_SQRT(const float x){
    return sqrtf(x);
}

float SSDL_ABS(const float x){
    if (x < 0) return -x;
    return x;
}

float SSDL_MIN(const float x1, const float x2){
    if (x1 <= x2) return x1;
    return x2;
}
float SSDL_MAX(const float x1, const float x2){
    if (x1 >= x2) return x1;
    return x2;
}
