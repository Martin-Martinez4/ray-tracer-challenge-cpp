
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

Canvas Ex003(){
  
  Material floorMat = Material(Color(1, 0.9, 0.9));
  floorMat.specular = 0;
  std::shared_ptr<Shape> floor (new Sphere{floorMat});
  floor->setTransform(Matrix::scale(10, 0.05, 10));

  std::shared_ptr<Shape> leftWall (new Sphere());
  leftWall->setTransforms({
    Matrix::scale(10, .05, 10), 
    Matrix::rotationAlongX(M_PI_2),
    Matrix::rotationAlongY(-M_PI_4), 
    Matrix::translate(0, 0, 5)
  });
  
  std::shared_ptr<Shape> rightWall (new Sphere());
  rightWall->setTransforms({
    Matrix::scale(10, 0.05, 10), 
    Matrix::rotationAlongX(M_PI_2),
    Matrix::rotationAlongY(M_PI_4),
    Matrix::translate(0, 0, 5)
  });


  Light l = Light(std::array<float, 3>{-10, 10, -10}, std::array<float, 3>{1, 1, 1});
  
  World w = World({floor, leftWall, rightWall}, l);

  Camera camera = Camera(300, 150, M_PI/3);
  camera.setTransform(Matrix::viewTransform(point(0,1.5,-5), point(0,1,0), vector(0,1,0)));
  
  return render(camera, w);


}

