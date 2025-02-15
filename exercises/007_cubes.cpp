#include "007_cubes.h"
#include "Camera.h"
#include "Canvas.h"
#include "Color.h"
#include "Cube.h"
#include "Shape.h"
#include "Sphere.h"
#include "Light.h"
#include "World.h"
#include <array>
#include <memory>
#include <cmath>
#include "Constants.h"


Canvas Ex007(){
  
  Material floorMat = Material(Color(1, 0.9f, 0.9f));
  floorMat.specular = 0;
  std::shared_ptr<Shape> floor (new Sphere{floorMat});
  floor->setTransform(Matrix::scale(10, 0.01f, 10));

  std::shared_ptr<Shape> leftWall (new Sphere());
  leftWall->setTransforms({
    Matrix::scale(10, .15f, 10), 
    Matrix::rotationAlongX(M_PI_2_F),
    Matrix::rotationAlongY(-M_PI_4_F), 
    Matrix::translate(0, 0, 5),
  });
  
  
  std::shared_ptr<Shape> rightWall (new Sphere());
  rightWall->setTransforms({
    Matrix::scale(10.f, .15f, 10.f), 
    Matrix::rotationAlongX(M_PI_F / 2),
    Matrix::rotationAlongY(M_PI_F / 4),
    Matrix::translate(0, 0, 5),
  });

  Material middMat = Material(Color(0.1f, 1, 0.5f));
  middMat.diffuse = 0.7f;
  middMat.specular = 0.3f;
  std::shared_ptr<Shape> middleSphere (new Cube(middMat));
  middleSphere->setTransform(Matrix::translate(-0.5f, 1, 0.5f));

  Material rightMat = Material(Color(0.5f, 1, 0.1f));
  rightMat.diffuse = 0.7f;
  rightMat.specular = 0.3f;
  std::shared_ptr<Shape> rightSphere (new Cube(rightMat));
  rightSphere->setTransform(Matrix::scale(0.5f, 0.5f, 0.5f));
  rightSphere->setTransform(Matrix::translate(1.5f, 0.5f, -0.5f));

  Material leftMat = Material(Color(1, 0.8f, 0.1f));
  leftMat.diffuse = 0.7f;
  leftMat.specular = 0.3f;
  std::shared_ptr<Shape> leftSphere (new Cube(leftMat));
  leftSphere->setTransform(Matrix::scale(0.33f, 0.33f, 0.33f));
  leftSphere->setTransform(Matrix::translate(-1.5f, 0.33f, -0.75f));


  Light l = Light(std::array<float, 3>{-10, 10, -10}, std::array<float, 3>{1, 1, 1});
  
  World w = World({floor, leftWall, rightWall, middleSphere, rightSphere, leftSphere}, l);

  Camera camera = Camera(600, 300, M_PI_F/3);
  camera.setTransform(Matrix::viewTransform(point(0,1.5,-5), point(0,1,0), vector(0,1,0)));
  
  return render(camera, w);


}
