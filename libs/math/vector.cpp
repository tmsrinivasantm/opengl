#include<math/vector.hpp>
#include <cmath>
namespace opengl {
vec3::vec3(){
    array[0] = 0.0;
    array[1] = 0.0;
    array[2] = 0.0;
}
vec3::vec3(float a, float b, float c){
    array[0] = a;
    array[1] = b;
    array[2] = c;
}
vec3 vec3::cross(const vec3 &vec) {
    vec3 result;
    result.array[0] = array[1]*vec.array[2] - array[2] * vec.array[1];
    result.array[1] = array[0]*vec.array[2] - array[2] * vec.array[0];
    result.array[2] = array[0]*vec.array[1] - array[1] * vec.array[0];

    return result;
}
float vec3::dot(const vec3 &vec) {
    return array[0]*vec.array[0] + array[1]*vec.array[1] + array[2]*vec.array[2];
}
vec3 vec3::normalize() {
    float sum = 0;
    float square_sum = (array[0] * array[0]) + (array[1] * array[1]) + (array[2] * array[2]);
    if ( square_sum == 1 )
        return *this;
    else{
        square_sum = std::sqrt(square_sum);
        array[0] = array[0]/square_sum;
        array[1] = array[1]/square_sum;
        array[2] = array[2]/square_sum;
    }

    return *this;
}
float vec3::operator[] (int index) const {
    return array[index];
}

vec3 vec3::operator-(const vec3 &vector) {
    vec3 result;
    for(int i = 0; i < 3; i++)
        result.array[i] = array[i] - vector[i];
    return result;
}
vec3 vec3::operator+(const vec3 &vector) {
    vec3 result;
    for(int i = 0; i < 3; i++)
        result.array[i] = array[i] + vector[i];
    return result;
}
vec3 vec3::operator* (const vec3 &vector) {
    vec3 result;
    for(int i = 0; i < 3; i++ ){
        result.array[i] = array[i] * vector[i];
    }

    return result;
}
vec3 vec3::operator* (float num) {
    vec3 result;
    for(int i = 0; i < 3; i++ ){
        result.array[i] = array[i] * num;
    }

    return result;
}

vec2::vec2(){
    array[0] = 0.0;
    array[1] = 0.0;
    array[2] = 0.0;
}
vec2::vec2(float a, float b) {
    array[0] = a;
    array[1] = b;
}
vec2 vec2::cross(const vec2 &vec) {
    vec2 result;
    result.array[0] = array[1]*vec.array[2] - array[2] * vec.array[1];
    result.array[1] = array[0]*vec.array[2] - array[2] * vec.array[0];

    return result;
}
float vec2::dot(const vec2 &vec) {
    return array[0]*vec.array[0] + array[1]*vec.array[1];
}
vec2 vec2::normalize() {
    float sum = 0;
    float square_sum = (array[0] * array[0]) + (array[1] * array[1]);
    if ( square_sum == 1 )
        return *this;
    else{
        square_sum = std::sqrt(square_sum);
        array[0] = array[0]/square_sum;
        array[1] = array[1]/square_sum;
    }

    return *this;
}
float vec2::operator[] (int index) const {
    return array[index];
}

vec2 vec2::operator-(const vec2 &vector) {
    vec2 result;
    for(int i = 0; i < 2; i++)
        result.array[i] = array[i] - vector[i];
    return result;
}
vec2 vec2::operator+(const vec2 &vector) {
    vec2 result;
    for(int i = 0; i < 2; i++)
        result.array[i] = array[i] + vector[i];
    return result;
}
vec2 vec2::operator* (const vec2 &vector) {
    vec2 result;
    for(int i = 0; i < 2; i++ ){
        result.array[i] = array[i] * vector[i];
    }

    return result;
}
vec2 vec2::operator* (float num) {
    vec2 result;
    for(int i = 0; i < 2; i++ ){
        result.array[i] = array[i] * num;
    }

    return result;
}
}
