
#include "003_camera.h"
#include "Camera.h"
#include "Canvas.h"
#include "Color.h"
#include "Shape.h"
#include "Sphere.h"
#include "Light.h"
#include "World.h"
#include <array>
#include <memory>
#include <cmath>
#include "Constants.h"


Canvas Ex003(){
  
  Material floorMat = Material(Color(1, 0.9f, 0.9f));
  floorMat.specular = 0;
  std::shared_ptr<Shape> floor (new Sphere{floorMat});
  floor->setTransform(Matrix::scale(10, 0.1f, 10));

  std::shared_ptr<Shape> leftWall (new Sphere());
  leftWall->setTransforms({
    Matrix::translate(0, 0, 5),
    Matrix::rotationAlongY(M_PI_4_F), 
    Matrix::rotationAlongX(M_PI_2_F),
    Matrix::scale(10, 1, 10), 
  });
  
  std::shared_ptr<Shape> rightWall (new Sphere());
  rightWall->setTransforms({
    Matrix::scale(10.f, .01f, 10.f), 
    Matrix::rotationAlongX(M_PI_F / 2),
    Matrix::rotationAlongY(M_PI_F / 4),
    Matrix::translate(0, 0, 5),
  });

  Material middMat = Material(Color(0.1f, 1, 0.5f));
  middMat.diffuse = 0.7f;
  middMat.specular = 0.3f;
  std::shared_ptr<Shape> middleSphere (new Sphere(middMat));
  middleSphere->setTransform(Matrix::translate(-0.5f, 1, 0.5f));

  Material rightMat = Material(Color(0.5f, 1, 0.1f));
  rightMat.diffuse = 0.7f;
  rightMat.specular = 0.3f;
  std::shared_ptr<Shape> rightSphere (new Sphere(rightMat));
  rightSphere->setTransform(Matrix::scale(0.5f, 0.5f, 0.5f));
  rightSphere->setTransform(Matrix::translate(1.5f, 0.5f, -0.5f));

  Material leftMat = Material(Color(1, 0.8f, 0.1f));
  leftMat.diffuse = 0.7f;
  leftMat.specular = 0.3f;
  std::shared_ptr<Shape> leftSphere (new Sphere(leftMat));
  leftSphere->setTransform(Matrix::scale(0.33f, 0.33f, 0.33f));
  leftSphere->setTransform(Matrix::translate(-1.5f, 0.33f, -0.75f));


  Light l = Light(std::array<float, 3>{-10, 10, -10}, std::array<float, 3>{1, 1, 1});
  
  World w = World({floor, leftWall, middleSphere, rightSphere, leftSphere}, l);

  Camera camera = Camera(100, 50, M_PI_F/3);
  camera.setTransform(Matrix::viewTransform(point(0,1.5,-5), point(0,1,0), vector(0,1,0)));
  
  return render(camera, w);


}

