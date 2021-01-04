/*
 * Rayman2 Mod Loader.
 * Rayman2 structures
 */

#ifndef RAYMAN2MODLOADER_STRUCTS_H
#define RAYMAN2MODLOADER_STRUCTS_H

#include <math.h>

struct Matrix {
    Sint32 transformationType;
    float x;
    float y;
    float z;
    float scaleX;
    float skewY1;
    float skewZ1;
    float skewX1;
    float scaleY;
    float skewZ2;
    float skewX2;
    float skewY2;
    float scaleZ;
    float t4_scaleX;
    float t4_skewY1;
    float t4_skewZ1;
    float t4_skewX1;
    float t4_scaleY;
    float t4_skewZ2;
    float t4_skewX2;
    float t4_skewY2;
};

struct Text2D
{
    const char* text;
    float positionX;
    float positionY;
    float size;
    __byte alpha__byte;
    __byte gap11;
    __byte highlight;
    __byte options; // bit 4 = highlighting color
    int dword14;
    __byte flag3;
};

struct TextureData
{
    Uint32 field0;
    Uint16 field4;
    Uint16 field6;
    void* tempBuffer;
    Uint32 fieldC;
    Uint32 field10;
    Uint32 flags;
    Uint16 height_;
    Uint16 width_;
    Uint16 height;
    Uint16 width;
    Uint32 currentScrollX;
    Uint32 currentScrollY;
    Uint32 textureScrollingEnabled;
    Uint32 alphaMask;
    Uint32 field30;
    Uint32 field34;
    Uint32 field38;
    Uint32 field3C;
    Uint32 field40;
    __byte field44;
    __byte flags__byte;
};

struct Vector2
{
    float x;
    float y;

    Vector2() : x(0), y(0) { }
    Vector2(float _x, float _y) : x(_x), y(_y) { }
    Vector2(const Vector2& v) : x(v.x), y(v.y) { }

    Vector2 operator + (const Vector2& v) {
        return Vector2(this->x + v.x, this->y + v.y);
    }

    Vector2 operator - (const Vector2& v) {
        return Vector2(this->x - v.x, this->y - v.y);
    }

    float& operator [] (std::size_t i) {
        return *((float*)this + i);
    }

    float length() {
        return sqrtf(this->x * this->x + this->y * this->y);
    }
};

struct Vector3 
{
    float x;
    float y;
    float z;

    Vector3() : x(0), y(0), z(0) { }
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) { }

    Vector3 operator + (const Vector3& v) {
        return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
    }

    Vector3 operator - (const Vector3& v) {
        return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
    }

    float& operator [] (std::size_t i) { 
        return *((float*)this + i); 
    }

    float length() {
        return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
    }
};

#endif