#pragma once

#include <iostream>
namespace opengl {
class vec3 {
public:
    vec3();
    vec3(float a, float b, float c);
    vec3 cross(const vec3 &vec);
    float dot(const vec3 &vec);
    vec3 normalize();
    inline void printvector(){
        std::cout << "[" << array[0] << ", " << array[1] << ", " << array[2] << "]" << std::endl;
    }
    float operator[] (int index) const;
    vec3 operator-(const vec3 &vector);
    vec3 operator+(const vec3 &vector);
    vec3 operator* (const vec3 &vector);
    vec3 operator* (float num);
private:
    float array[3];
};
class vec2 {
public:
    vec2();
    vec2(float a, float b);
    vec2 cross(const vec2 &vec);
    float dot(const vec2 &vec);
    vec2 normalize();
    inline void printvector(){
        std::cout << "[" << array[0] << ", " << array[1] << "]" << std::endl;
    }
    float operator[] (int index) const;
    vec2 operator-(const vec2 &vector);
    vec2 operator+(const vec2 &vector);
    vec2 operator* (const vec2 &vector);
    vec2 operator* (float num);
private:
    float array[2];

};
}
