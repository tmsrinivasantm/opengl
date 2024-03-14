#include <matrices.hpp>
namespace opengl {
  matrix4f::matrix4f(){
    m11 = 1.0f; m12 = 0.0f; m13 = 0.0f; m14 = 0.0f;
    m21 = 0.0f; m22 = 1.0f; m23 = 0.0f; m24 = 0.0f;
    m31 = 0.0f; m32 = 0.0f; m33 = 1.0f; m34 = 0.0f;
    m41 = 0.0f; m42 = 0.0f; m43 = 0.0f; m44 = 1.0f;
  }

  void matrix4f::initialize() {
    m11 = 1.0f; m12 = 0.0f; m13 = 0.0f; m14 = 0.0f;
    m21 = 0.0f; m22 = 1.0f; m23 = 0.0f; m24 = 0.0f;
    m31 = 0.0f; m32 = 0.0f; m33 = 1.0f; m34 = 0.0f;
    m41 = 0.0f; m42 = 0.0f; m43 = 0.0f; m44 = 1.0f;
  }

void matrix4f::print_matrix() {
  std::cout << m11 << " " << m12 << " " << m13 << " " << m14 << "\n";
  std::cout << m21 << " " << m22 << " " << m23 << " " << m24 << "\n";
  std::cout << m31 << " " << m32 << " " << m33 << " " << m34 << "\n";
  std::cout << m41 << " " << m42 << " " << m43 << " " << m44 << "\n";
}

matrix4f matrix4f::operator*(const matrix4f &mat) {
  matrix4f result;
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      float num = 0.0f;
      for(int k = 0; k < 4; k++) {
        num += values[i][k] * mat.values[k][j];
      }
      result.values[i][j] = num;
    }
  }
  return result;
}

  void matrix4f::operator=(const matrix4f &mat) {
    for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 4; j++) {
        values[i][j] = mat.values[i][j];
      }
    }
  }

void matrix4f::make_matrix4f(const float *floats) {
  int count = 0;
  for(int i = 0; i < 4; i++){
    for(int j = 0;j < 4; j++){
      values[j][i] = floats[count]; // opengl matrix notation
      count++;
    }
  }
}

 void normalize(float vec[3]) {
   float square_sum = (vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2]);

   if ( square_sum == 1 )
     return;
   else{
     square_sum = std::sqrt(square_sum);
     vec[0] = vec[0]/square_sum;
     vec[1] = vec[1]/square_sum;
     vec[2] = vec[2]/square_sum;
   }
 }

  float degrees_to_radians(float angle) {
    return 0.0174533 * angle;
  }

void rotate(matrix4f &mat, float angle, float axis[3]) {
  matrix4f rotation_transform;
  normalize(axis);
  float sin = std::sin(angle);
  float cos = std::cos(angle);

  // rotation computation below
  const float values[] {
  cos  + (axis[0]*axis[0] * (1-cos)),(axis[0] * axis[1] * (1 - cos) - axis[2]*sin), axis[0] * axis[2] * (1 - cos) + (axis[1] * sin),0.0f,
  axis[1] * axis[0] * (1-cos) + (axis[2] * sin), cos + (axis[1] * axis[1] * (1 - cos)), axis[1] * axis[2] * ( 1 - cos ) - (axis[0] * sin), 0.0f,
  (axis[2] * axis[0] * ( 1-cos )) - (axis[1] * sin) , (axis[2] * axis[1] * ( 1 - cos )) + (axis[0] * sin), cos + (axis[2] * axis[2] * ( 1 - cos )), 0.0f,
  0.0f, 0.0f, 0.0f, 1.0f
  };

  rotation_transform.make_matrix4f(values);

  mat = rotation_transform * mat;

}

void translate(matrix4f &mat, const float vec[3]) {

  matrix4f translation_matrix;

  const float values[] = {
  1.0f, 0.0f, 0.0f, vec[0],
  0.0f, 1.0f, 0.0f, vec[1],
  0.0f, 0.0f, 1.0f, vec[2],
  0.0f, 0.0f, 0.0f, 1.0f,
  };

  translation_matrix.make_matrix4f(values);

  mat = translation_matrix * mat;
}

matrix4f perspective(float fov, float aspect_ratio, float near, float far) {
    matrix4f perspective;

    float bottom = near * std::tan(fov / 2.0f);
    float right = near * aspect_ratio * std::tan(fov / 2.0f);

    float pers_values[16] = {
      near/right, 0.0f, 0.0f, 0.0f,
      0.0f, near/bottom, 0.0f, 0.0f,
      0.0f, 0.0f, -(far+near)/(far-near),-2*near*far/(far-near),
      0.0f, 0.0f, -1.0f, 0.0f
    };

    perspective.make_matrix4f(pers_values);

    return perspective;
}

  void matrix4f::transpose() {
    for(int i = 0; i < 4; i++) {
      for(int j = i; j < 4; j++) {
        float temp = values[i][j];
        values[i][j] = values[j][i];
        values[j][i] = temp;
      }
    }
  }
} // namespace opengl
