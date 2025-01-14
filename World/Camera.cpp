
#include "Camera.h"
#include "Matrix.h"
#include "Tuple.h"
#include <cmath>

Camera::Camera(float hSize, float vSize, float fieldOfView):hSize{hSize}, vSize{vSize}, fieldOfView{fieldOfView}, transform{Matrix::identityMatrix(4)}, inverseTransform(Matrix::identityMatrix(4)){
 setupPixelSize(); 
}
 

Matrix Camera::getTransform(){
  return transform;
}
void Camera::setTransform(Matrix transform){
  this->transform = transform * this->transform;
  this->inverseTransform = this->transform.inverse();
}
void Camera::setTransforms(std::vector<Matrix> transforms){
  Matrix transformation = Matrix::identityMatrix(4);

  size_t size = transforms.size();
  for(size_t t = 0; t < size; ++t){
    transformation = transforms[t] * transformation;
  }

  this->setTransform(transformation);
};
Matrix Camera::getInverseTransform(){
  return inverseTransform;
}

Ray Camera::rayForPixel(float px, float py){
  float xOffset = (px + 0.5f) * pixelSize;
  float yOffset = (py + 0.5f) * pixelSize;

  float worldX = halfWidth - xOffset;
  float worldY = halfHeight - yOffset;

  Tuple pixel = tupleMultiply(getInverseTransform(), point(worldX, worldY, -1));
  Tuple origin = tupleMultiply(getInverseTransform(), point(0, 0, 0));
  Tuple pSO = pixel.subtractTuple(origin);
  Tuple direction = normalize(pSO);

  return Ray(origin, direction);
}
  

void Camera::setupPixelSize(){
  float halfView = std::tan(fieldOfView/2);
  float aspect = hSize/vSize;

  if(aspect >= 1){
    halfWidth = halfView;
    halfHeight = halfView / aspect;
  }else{
    halfWidth = halfView * aspect;
    halfHeight = halfView;
  }

  pixelSize = (halfWidth * 2.0f) / hSize;
}
