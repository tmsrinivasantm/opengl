#pragma once
#include <cmath>
#include <iostream>
namespace opengl {
    class matrix4f {
        public:
            matrix4f();
            void print_matrix();
            void make_matrix4f(const float *values);
            matrix4f operator * (const matrix4f &mat);
            void operator = (const matrix4f &mat);
            inline float* getValue() { return &values[0][0]; }
            void initialize();
            matrix4f transpose();
        private:
            float values[4][4];
            float &m11 = values[0][0], &m12 = values[0][1], &m13 = values[0][2], &m14 = values[0][3];
            float &m21 = values[1][0], &m22 = values[1][1], &m23 = values[1][2], &m24 = values[1][3];
            float &m31 = values[2][0], &m32 = values[2][1], &m33 = values[2][2], &m34 = values[2][3];
            float &m41 = values[3][0], &m42 = values[3][1], &m43 = values[3][2], &m44 = values[3][3];
    };
    float degrees_to_radians(float angle);
    void rotate(matrix4f &mat, float angle,float axis[3]);
    void translate(matrix4f &mat, const float vec[3]);
    matrix4f perspective(float fov, float aspect_ratio, float near, float far);
    void normalize(float vec[3]);
}
