
#include "004_plane.h"
#include "Camera.h"
#include "Canvas.h"
#include "Color.h"
#include "Plane.h"
#include "Shape.h"
#include "Sphere.h"
#include "Light.h"
#include "World.h"
#include <array>
#include <memory>
#include <cmath>
#include <vector>
#include "Constants.h"


Canvas Ex004(){
  
  std::shared_ptr<Shape> floor (new Plane());
  /*
  Material wallMat = Material(Color(.5, .25, .2));
  std::shared_ptr<Shape> wall (new Plane(wallMat));
  wall->setTransforms({
    Matrix::translate(0, 3, 0),
    Matrix::rotationAlongX(M_PI_2),
  
  });
  */
  Material wallMat = Material(Color(1, 1, .5));
  std::shared_ptr<Shape> wall (new Plane(wallMat));
  wall->setTransforms({
    Matrix::rotationAlongY(M_PI),
    Matrix::rotationAlongZ(M_PI_2),
    Matrix::translate(2.5, 0, 0)
  
  });

  Material wallMat2 = Material(Color(1, 1, .5));
  std::shared_ptr<Shape> wall2 (new Plane(wallMat2));
  wall2->setTransforms({
    Matrix::translate(0, -2, 0),
    Matrix::rotationAlongY(M_PI_2),
    Matrix::rotationAlongX(-M_PI_2),
    Matrix::translate(2, 0, 3)
  
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
  
  World w = World({floor, middleSphere, rightSphere, leftSphere}, l);

  Camera camera = Camera(600, 300, M_PI/1.5);
  camera.setTransform(Matrix::viewTransform(point(0,1.5,-5), point(0,1,0), vector(0,1,0)));
  
  return render(camera, w);


}

