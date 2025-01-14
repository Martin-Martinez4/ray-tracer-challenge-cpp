#ifndef WORLD_CAMERA_H_
#define WORLD_CAMERA_H_

#include "Matrix.h"
#include "Ray.h"

class Camera{
public:
  
  Camera(float hSize, float vSize, float fieldOfView);

  float hSize;
  float vSize;
  float fieldOfView;
  float halfWidth;
  float halfHeight;
  float pixelSize;

  Matrix getTransform();
  void setTransform(Matrix transform);
  void setTransforms(std::vector<Matrix> transforms);
  Matrix getInverseTransform();

  Ray rayForPixel(float px, float py);
  

private:
  Matrix transform;
  Matrix inverseTransform;
  void setupPixelSize();
};



#endif // !WORLD_CAMERA_H_



